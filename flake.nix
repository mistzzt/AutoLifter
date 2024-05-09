{
  description = "AutoLifter";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/release-23.11";
  };

  outputs = {
    self,
    nixpkgs,
  }: let
    systems = [
      "x86_64-linux"
    ];

    forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f system);
  in {
    packages = forAllSystems (system: let
      pkgs = import nixpkgs {
        system = system;
        config.allowUnfree = true;
      };

      gurobiFixed = pkgs.gurobi.override {
        python3 = pkgs.python310;
      };
      inherit (pkgs) stdenv callPackage;
    in {
      gurobiFixed = gurobiFixed;

      autolifter = stdenv.mkDerivation {
        name = "autolifter";
        src = ./.;
        nativeBuildInputs = with pkgs; [
          cmake
          pkg-config
          wget
          jsoncpp
          glog
          cbmc
          makeWrapper
          gurobiFixed
        ];

        patchPhase = ''
          substituteInPlace basic/config.cpp run/run run/run_exp \
            --replace 'SOURCEPATH' $out

          substituteInPlace exp/paradigms/paradigm_util.cpp \
            --replace 'command = "cbmc "' 'command = "${pkgs.cbmc}/bin/cbmc "'

          substituteInPlace run/run run/run_exp \
            --replace 'build/main' 'bin/autolifter_main'
        '';
        cmakeBuildType = " ";

        installPhase = ''
          mkdir -p $out/bin
          cp main $out/bin/autolifter_main
          cp -r ../run $out
          cp -r ../resource $out

          makeWrapper $out/run/run $out/bin/autolifter_run --argv0 "run"
          makeWrapper $out/run/run_exp $out/bin/autolifter_run_exp --argv0 "run"
        '';
      };

      default = self.packages.${system}.autolifter;
    });
  };
}

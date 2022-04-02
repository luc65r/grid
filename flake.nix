{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShell = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          gdb
          wayland
          wayland-scanner
        ];
      };

      defaultPackage = pkgs.stdenv.mkDerivation {
        pname = "grid";
        version = "0.1.0";
        src = ./.;

        nativeBuildInputs = with pkgs; [
          wayland-scanner
        ];

        buildInputs = with pkgs; [
          wayland
        ];

        makeFlags = [ "DESTDIR=" "PREFIX=${placeholder "out"}" ];
      };
    });
}

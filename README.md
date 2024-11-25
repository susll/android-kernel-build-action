# Android Kernel Build Action

This GitHub Action is designed to automate the building of Android kernel modules out of the kernel source. It supports both aarch64 and x86_64 architectures, and can build kernels for different Android versions (GKI 2.0).

[https://source.android.com/docs/core/architecture/kernel/gki-release-builds](https://source.android.com/docs/core/architecture/kernel/gki-release-builds)

## Overview

The Android Kernel Build Action allows users to easily build kernels for Android devices by specifying a few parameters such as kernel source, branch, and configuration. The action automates the download of compilers, setting up necessary paths, and builds the kernel for the specified architecture.

## Supported Architectures

- aarch64

- x86_64

## Supported Android Versions

- Android 12 (Kernel: 5.10)

- Android 13 (Kernel: 5.10, 5.15)

- Android 14 (Kernel: 5.15, 6.1)

- Android 15 (Kernel: 6.6)

- Android 16 (Kernel: 6.12)

## Inputs

### Required Inputs

- arch:

    - Description: Target architecture for the kernel build.

    - Required: true

    - Default: arm64

- tag:

    - Description: Android GKI version.

    - Required: true

    - Default: 'android13-5.15'

- module-name:

    - Description: module name of the ko.

    - Required: true

- module-path

    - Description: module name of the github action artifact.

    - Required: true

## Usage

Here is a workflow that uses this action to build an Android kernel module for different versions and architectures.

### .github/workflows/ci.yml

```bash
name: GKI Kernel Module Build

on:
  workflow_dispatch:

jobs:
  build:
    name: GKI Kernel Module Build
    runs-on: ubuntu-22.04
    needs: upload-artifact
    strategy:
      matrix:
        tag:
          - android12-5.10
          - android13-5.10
          - android13-5.15
          - android14-5.15
          - android14-6.1
          - android15-6.6
          - android16-6.12
        arch:
          - aarch64
          - x86_64

    steps:
      - name: Maximize build space
        uses: easimon/maximize-build-space@master
        with:
          root-reserve-mb: 8192
          temp-reserve-mb: 2048
          remove-dotnet: 'true'
          remove-android: 'true'
          remove-haskell: 'true'
          remove-codeql: 'true'

      - name: Checkout Repository
        uses: actions/checkout@v4

      - name: Run GKI Kernel Build Action
        uses: ./
        with:
          arch: ${{ matrix.arch }}
          tag: ${{ matrix.tag }}
          module-name: hello-ko
          module-path: hello-ko

  upload-artifact:
    name: Upload LKM Source Code
    runs-on: ubuntu-22.04
    steps:
      - name: Checkout Repository
        uses: actions/checkout@v4

      - name: Upload LKM Source Code
        uses: actions/upload-artifact@v4
        with:
          name: hello-ko
          path: .github/hello-ko
```

### Outputs

The action will upload the compiled kernel and module ko file.

## License

[GPL-3.0-or-later](https://www.gnu.org/licenses/gpl-3.0.html).

## Credits

[https://github.com/tiann/KernelSU](https://github.com/tiann/KernelSU)

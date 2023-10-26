# Feature-stripped version of [DualTachyon's uv-k5-firmware](https://github.com/DualTachyon/uv-k5-firmware)

A fork of uv-k5-firmware that has many features stripped out and disabled, increasing available flash storage.

---
Base .bin size: 60192 bytes
Stripped .bin size: 
| Binary file        | Size (Bytes)          |
| ------------- |:-------------:|
| Base      | 60192 |
| Stripped      | 55260 |


| Feature        | Method          | Bytes removed  |
| ------------- |:-------------:| -----:|
| NOAA      | Disabled in Makefile | 1072 |
| Overlay      | Disabled in Makefile | 876 |
| Aircopy      | Disabled in Makefile | 1600 |
| Alarm      | Disabled in Makefile | 528 |
| Voice      | Empty functions      |   860 |


---


# Compiler

arm-none-eabi GCC version 10.3.1 is recommended, which is the current version on Ubuntu 22.04.03 LTS.
Other versions may generate a flash file that is too big.
You can get an appropriate version from: https://developer.arm.com/downloads/-/gnu-rm

# Building

To build the firmware, you need to fetch the submodules and then run make:
```
git submodule update --init --recursive --depth=1
make
```

# Flashing with the official updater

* Use the firmware.packed.bin file

# Flashing with [k5prog](https://github.com/piotr022/k5prog)

* ./k5prog -F -YYY -b firmware.bin

# Flashing with SWD

* If you own a JLink or compatible device and want to use the Segger software, you can find a flash loader [here](https://github.com/DualTachyon/dp32g030-flash-loader)
* If you want to use OpenOCD instead, you can use run "make flash" off this repo.
* The DP32G030 has flash masking to move the bootloader out of the way. Do not try to flash your own way outside of the above methods or risk losing your bootloader.

# Support

* If you like my work, you can support me through https://ko-fi.com/DualTachyon

# Credits

Many thanks to various people on Telegram for putting up with me during this effort and helping:

* [Mikhail](https://github.com/fagci/)
* [Andrej](https://github.com/Tunas1337)
* [Manuel](https://github.com/manujedi)
* @wagner
* @Lohtse Shar
* [@Matoz](https://github.com/spm81)
* @Davide
* @Ismo OH2FTG
* [OneOfEleven](https://github.com/OneOfEleven)
* and others I forget

# License

Copyright 2023 Dual Tachyon
https://github.com/DualTachyon

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.


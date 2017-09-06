![NexMon logo](https://github.com/seemoo-lab/nexmon/raw/master/gfx/nexmon.png)

# WiNTECH 2017 Ping Offloading Firmware
At the 11th ACM International Workshop on Wireless Network Testbeds, Experimental Evaluation & 
Characterization (WiNTECH 2017) we publish a paper on "Massive Reactive Smartphone-Based Jamming 
using Arbitrary Waveforms and Adaptive Power Control". This repository contains source code 
required to repeat the experiments we did for our paper. Additionally, it allows fellow researches 
to base their own research on our results.

# Extract from our License

Any use of the Software which results in an academic publication or
other publication which includes a bibliography must include
citations to the nexmon project (1) and the paper cited under (2):

1. "Matthias Schulz, Daniel Wegemer and Matthias Hollick. Nexmon:
    The C-based Firmware Patching Framework. https://nexmon.org"

2. "Matthias Schulz, Daniel Wegemer, Matthias Hollick. Nexmon: Build 
    Your Own Wi-Fi Testbeds With Low-Level MAC and PHY-Access Using 
    Firmware Patches on Off-the-Shelf Mobile Devices, In Proceedings 
    of the 11th ACM International Workshop on Wireless Network 
    Testbeds, Experimental Evaluation & Characterization (WiNTECH 
    2017), October 2017."

# Getting Started

To compile the source code, you are required to first checkout a copy of the original nexmon
repository that contains our C-based patching framework for Wi-Fi firmwares. That you checkout
this repository as one of the sub-projects in the corresponding patches sub-directory. This 
allows you to build and compile all the firmware patches required to repeat our experiments.
The following steps will get you started on Xubuntu 16.04 LTS:

1. Install some dependencies: `sudo apt-get install git gawk qpdf adb`
2. **Only necessary for x86_64 systems**, install i386 libs: 

  ```
  sudo dpkg --add-architecture i386
  sudo apt-get update
  sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
  ```
3. Clone the nexmon base repository: `git clone https://github.com/seemoo-lab/nexmon.git`.
4. Download and extract Android NDK r11c (use exactly this version!).
5. Export the NDK_ROOT environment variable pointing to the location where you extracted the ndk so that it can be found by our build environment.
6. Navigate to the previously cloned nexmon directory and execute `source setup_env.sh` to set a couple of environment variables.
7. Run `make` to extract ucode, templateram and flashpatches from the original firmwares.
8. Navigate to utilities and run `make` to build all utilities such as nexmon.
9. Attach your rooted Nexus 5 smartphone running stock firmware version 6.0.1 (M4B30Z, Dec 2016).
10. Run `make install` to install all the built utilities on your phone.
11. Navigate to patches/bcm4339/6_37_34_43/ and clone this repository: `git clone https://github.com/seemoo-lab/wisec2017_nexmon_jammer.git`
12. Enter the created subdirectory wisec2017_nexmon_jammer and run `make install-firmware` to compile our firmware patch and install it on the attached Nexus 5 smartphone.

# References

* Matthias Schulz, Daniel Wegemer, Matthias Hollick. **Nexmon: Build Your Own Wi-Fi Testbeds With Low-Level MAC and PHY-Access Using Firmware Patches on Off-the-Shelf Mobile Devices**, Accepted for publication in *Proceedings of the 11th ACM International Workshop on Wireless Network Testbeds, Experimental Evaluation & Characterization (WiNTECH 2017)*, October 2017.
* Matthias Schulz, Daniel Wegemer and Matthias Hollick. **Nexmon: The C-based Firmware Patching Framework**. https://nexmon.org

[Get references as bibtex file](https://nexmon.org/bib)

# Contact

* [Matthias Schulz](https://seemoo.tu-darmstadt.de/mschulz) <mschulz@seemoo.tu-darmstadt.de>

# Powered By

## Secure Mobile Networking Lab (SEEMOO)
<a href="https://www.seemoo.tu-darmstadt.de">![SEEMOO logo](https://github.com/seemoo-lab/nexmon/raw/master/gfx/seemoo.png)</a>
## Networked Infrastructureless Cooperation for Emergency Response (NICER)
<a href="https://www.nicer.tu-darmstadt.de">![NICER logo](https://github.com/seemoo-lab/nexmon/raw/master/gfx/nicer.png)</a>
## Multi-Mechanisms Adaptation for the Future Internet (MAKI)
<a href="http://www.maki.tu-darmstadt.de/">![MAKI logo](https://github.com/seemoo-lab/nexmon/raw/master/gfx/maki.png)</a>
## Technische Universität Darmstadt
<a href="https://www.tu-darmstadt.de/index.en.jsp">![TU Darmstadt logo](https://github.com/seemoo-lab/nexmon/raw/master/gfx/tudarmstadt.png)</a>

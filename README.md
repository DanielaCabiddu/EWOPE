# EWoPe: a light Embeddable WOrkflow PErsistence tool for geoscientific pipeline reproducibility

EWoPe: _Embeddable WOrkflow PErsistence_ is a flexible, multi-platform software framework implemented in C++ and designed to document and preserve a wide range of geoscientific computational workflows. It enables users and developers for managing, serializing, and inspecting workflow metadata and data descriptors.
The architecture supports two modes of use, such as:
- an embeddable library that can be integrated directly into user-developed C++ software;
- a standalone executable to work with third-party software.

The code is tested on different Operating Systems (MacOS, Linux and Windows).

Referring to examples, execution script and data are related to synthetical scenarios or real case studies.

## Clone
We provide the commands to install EWoPe. 
The repository includes some submodules necessary to make the code work. Please, clone it recursively:

- Clone recursively the repository into your local machine:
```
git clone --recursive https://github.com/DanielaCabiddu/EWOPE.git
```
- If some submodules are not clone/update, please use git command in the root directory ROOT (where this README lies):
```
cd ${ROOT}
git submodule update --init --recursive
```

## Usage
EWoPe code has some mandatory dependences included in _${ROOT}/external_:

- to manage command line arguments and options (tclap);
- to metadata the computational process (cereal).

## Building
To build EWoPe source code, use the `build.sh` script available, located in the root directory ROOT (where this README lies). 

## Examples
To guarantee replicability, data of our examples are provided in the _example_ folder. 
If you wish to replicate them, please run bash script file (_10_test_MUSE_example_name.sh_), as follows:

```
cd ${ROOT}/examples/example_name/script
./10_test_MUSE_example_name.sh
```


## Authors contact
- Daniela Cabiddu (CNR-IMATI, Genova, Italy), email: daniela.cabiddu@cnr.it
- Marianna Miola (CNR-IMATI, Genova, Italy), email: marianna.miola@cnr.it


## Citing us

## Acknowledgment
The work is developed under the Ph.D. Research Project in Earth and Environmental Science and Technology, supported by PON "Ricerca e Innovazione" 2014-2020, Asse IV "Istruzione e ricerca per il recupero", Azione IV.5 "Dottorati su tematiche Green" DM 1061/2021. 

Marianna Miola acknowledges the Italian National Biodiversity Future Center (NBFC) - National Recovery and Resilience Plan (NRRP) funded by the European Union - NextGenerationEU (project code CN 00000033).

Daniela Cabiddu, Simone Pittaluga and Marino Vetuschi Zuccolini are members of the RAISE Innovation Ecosystem, funded by the European Union - NextGenerationEU and by the Ministry of University and Research (MUR), National Recovery and Resilience Plan (NRRP), Mission 4, Component 2, Investment 1.5, project ``RAISE - Robotics and AI for Socio-economic Empowerment'' (ECS00000035).

This research was partially funded by the projects and initiatives mentioned above.
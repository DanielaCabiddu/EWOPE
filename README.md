# EWoPe: a light Embeddable WOrkflow PErsistence tool for geoscientific pipeline reproducibility

EWoPe: _Embeddable WOrkflow PErsistence_ is a flexible, multi-platform software framework implemented in C++ and designed to document and preserve a wide range of geoscientific computational workflows. It enables users and developers for managing, serializing, and inspecting workflow metadata and data descriptors.
The architecture supports two modes of use, such as:
- an embeddable library that can be integrated directly into user-developed C++ software;
- a standalone executable to work with third-party software.

The code is tested on different Operating Systems (MacOS, Linux and Windows).

## Clone
We provide the commands to install EWoPe. 
The repository includes a submodule necessary to make the code work. Please, clone it recursively:

- Clone recursively the repository into your local machine:
```
git clone --recursive https://github.com/DanielaCabiddu/EWOPE.git
```

## Content of the repository
- `src`: source code for the two main applications
    - `main_core`: to create and customize metadata following EWoPe base structure
    - `main_history`: to build computational histories
- `include`: functionalities library to support source codes
- `external`: external libraries
- `examples`: application data (input data and output metadata)
- `CMakeLists.txt`: build configuration file

## Usage
EWoPe code has some mandatory dependences:

- to manage command line arguments and options: `tclap` (to clone and include in _${ROOT}/external_);
- to metadata the computational process: `cereal` (included as a submodule in _${ROOT}/external_).

## Building
To build EWoPe source code, use the following pipeline:

```
cd ${ROOT}
mkdir build
cd build
cmake --DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

Executables will be made available in _${ROOT}/bin_ folder.

## Application
Our application is described in the paper (see Section 5). 
To replicate paper results testing history functionality (see Section 6.3), please run the executable ```_EWOPE_history_```, as described in the README located in the _${ROOT}/example_ folder. Input data and metadata are provided in the same location.


## Contributors
- Daniela Cabiddu (CNR-IMATI, Genova, Italy), email: daniela.cabiddu@cnr.it
- Marianna Miola (CNR-IMATI, Genova, Italy), email: marianna.miola@cnr.it

## Citing us
```bibtex
@unpublished{miola2025ewoPe,
  author       = {Marianna Miola and Daniela Cabiddu and Simone Pittaluga and Micaela Raviola and Marino Vetuschi Zuccolini},
  title        = {{EWoPe: a light Embeddable WOrkflow PErsistence tool for geoscientific pipeline reproducibility}},
  year         = {2025},
  note         = {Manuscript under review in *Computers \& Geosciences*},
  url          = {https://github.com/DanielaCabiddu/EWOPE}
}
```

## Acknowledgment
The work is developed under the Ph.D. Research Project in Earth and Environmental Science and Technology, supported by PON "Ricerca e Innovazione" 2014-2020, Asse IV "Istruzione e ricerca per il recupero", Azione IV.5 "Dottorati su tematiche Green" DM 1061/2021. 

Marianna Miola acknowledges the Italian National Biodiversity Future Center (NBFC) - National Recovery and Resilience Plan (NRRP) funded by the European Union - NextGenerationEU (project code CN 00000033).

Daniela Cabiddu, Simone Pittaluga and Marino Vetuschi Zuccolini are members of the RAISE Innovation Ecosystem, funded by the European Union - NextGenerationEU and by the Ministry of University and Research (MUR), National Recovery and Resilience Plan (NRRP), Mission 4, Component 2, Investment 1.5, project ``RAISE - Robotics and AI for Socio-economic Empowerment'' (ECS00000035).

This research was partially funded by the projects and initiatives mentioned above.

# EWoPe: a light Embeddable WOrkflow PErsistence tool for geoscientific pipeline reproducibility

## Application
Our application is described in the paper (see Section 5). 
The _${ROOT}/example_ contains all input data and output metadata used in our case study. It includes a main workflow directory _${ ROOT}/examples/W_, organized into three subdirectories, each corresponding to a different workflow:
- W1: starting from porosity data sampled along a borehole, a spatial distribution is computed over an unstructured mesh;
- W2: following a similar approach using hydrofacies, a best guess is computed over the same mesh;
- W3: hydrofacies are converted into permeability, and coupled with porosity distribution, the geochemical model is performed.

We used a synthetic scenario representing a vertical section of 100 m x 15 m. The input data includes:
- a bounding box defining the geometry, stored in text file (_${ROOT}/examples/W/W1/in/geometry/sec\_xz.xyz_);
- borehole sampling data from n. 11 cores, stored in a CSV file (_${ROOT}/examples/W/W1/in/data/samples\_sec4000.csv_);

To replicate the results presented in the paper (see Section 6.3), especially for testing the history functionality, run the executable _EWOPE_history_ as described below.

## How to use
After building the application as described, you can run the executable EWOPE_history using the following command-line structure:

```
cd ${ROOT}/bin
./EWOPE_history [-bfhm] [--version] [-w <string>] -j <string>
```

where:
- `-j <string>`, ` --json <string>` --  (required) Set JSON file to reproduce the computational history
- `-w <string>`, ` --workflow <string>` -- Set workflow directory
- `-b`, ` --back` -- Set history mode (recursively - back)
- `-f`,  `--forward` -- Set history mode (recursively - forward)
-  `-m`,  `--more` -- Set history mode (recursively - forward) and commands
-  `--`,  `--ignore_rest` -- Ignores the rest of the labeled arguments following this flag.
-  `--version` -- Displays version information and exits.
- `-h`,  `--help` -- Displays usage information and exits.

##Example
To reproduce the results described in the paper, specifically for testing the history functionality, use the following command:

```
cd ${ROOT}/bin
./EWOPE_history -w  ${ROOT}/examples/W -j ${ROOT}/examples/W/W1/out/compute/phi_DIR2D_sec_xz/_varspace/_stats/phi_mean.json -f
```
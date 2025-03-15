# PRNGine: Massively Parallel Pseudo-Random Number Generation and Probability Distribution Approximations on AMD AI Engines [CGRA4HPC, IPDPS'25].

This project enables porting PRNGs to AMD Versal AIEs by analyzing the algorithmic requirements of three PRNGs: XORWOW, XOROSHIRO, and SFMT. Two execution models are proposed: a co-processor model (M1), where AIEs generate random numbers and send them to the host processor, and a standalone dataflow accelerator model (M2), where random number generation is pipelined with computation within a dataflow overlay on AIEs. M2 uses the Acklam's ICDF approximation as a subsequent computation step in the dataflow to random number generation.

## Installation

To run PRNGine, clone the repository:

```bash
git clone https://github.com/medbzkst/PRNGine
cd PRNGine
```

Then depending on which execution model: co-processor model (M1) or standalone dataflow accelerator (M2), locate within the corresponding directory:

```bash
cd M1 # Co-processor model
```

Each model employs 3 PRNGs: SFMT, XORWOW, XOROSHIRO128. Locate in the corresponding directory and launch the build (this may take a few hours). 

```bash
cd SFMT # SFMT PRNG
make all
```

M2 under the directory ``M2`` runs the Acklam's ICDF approximation as a subsequent computation step in the dataflow to random number generation.``M2_template`` can be used as a template to M2 to incorporate a subsequent computation step to the random number generation. This can be done by coding the computation kernel under ``M2_template/PRNG_name/aie/src/subsequent.cpp``. 


## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. Make sure to follow the coding standards and include tests for any new features.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For any questions or suggestions, please open an issue or contact at [mohamed.bouaziz@kaust.edu.sa](mailto:mohamed.bouaziz@kaust.edu.sa).


## Reference

M. Bouaziz and S. A. Fahmy, "PRNGine: Massively Parallel Pseudo-Random Number Generation and Probability Distribution Approximations on AMD AI Engines," 2025 IEEE International Parallel and Distributed Processing Symposium Workshops (IPDPSW), 2025.


```
@INPROCEEDINGS{PRNGine,
  author={Bouaziz, Mohamed and Fahmy, Suhaib A.},
  booktitle={2025 IEEE International Parallel and Distributed Processing Symposium Workshops (IPDPSW)}, 
  title={PRNGine: Massively Parallel Pseudo-Random Number Generation and Probability Distribution Approximations on AMD AI Engines}, 
  year={2025}
}
```

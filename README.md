![EGTtools](docs/images/logo-full.png)

# Toolbox for Evolutionary Game Theory

[![DOI](https://zenodo.org/badge/242180332.svg)](https://zenodo.org/badge/latestdoi/242180332)
[![Documentation Status](https://readthedocs.org/projects/egttools/badge/?version=latest)](https://egttools.readthedocs.io/en/latest/?badge=latest)
![build](https://github.com/Socrats/EGTTools/workflows/build/badge.svg)

**EGTtools** provides a centralized repository with analytical and numerical methods to study/model game theoretical
problems under the Evolutionary Game Theory (EGT) framework.

This library is composed of two parts:

- a set of analytical methods implemented in Python 3
- a set of computational methods implemented in C++ with (Python 3 bindings)

The second typed is used in cases where the state space is too big to solve analytically, and thus require estimating
the model parameters through monte-carlo simulations. The C++ implementation provides optimized computational methods
that can run in parallel in a reasonable time, while Python bindings make the methods easily accecible to a larger range
of researchers.

---
## Table of Contents

1. [Requirements](#requirements)
2. [Downloading sources](#downloading-sources)
3. [Examples of usage](#examples-of-usage)
4. [Documentation](#documentation)
5. [Caveats](#caveats)
6. [Citing](#citing)
---
## Requirements

To be able to install EGTtools, you must have:

* A recent version of Linux (only tested on Ubuntu), MacOSX (Mojave or above) or Windows
* [**CMake**](https://cmake.org) version 3.17 or higher
* [**C++ 17**](https://en.cppreference.com/w/cpp/17)
* [**Eigen**](https://eigen.tuxfamily.org/index.php?title=Main_Page) 3.3.*
* **Python** 3.5 or higher
* If you want support for parallel operations you should install [**OpenMP**](https://www.openmp.org)
* Ideally, you should also install [**OpenBLAS**](https://www.openblas.net), which offers optimized implementations of
  linear algebra kernels for several processor architectures, and install numpy and scipy versions that use it.

---
## Downloading sources

When cloning the repository you should also clone the submodules so that pybind11 is downloaded. You can do that by
running:

```bash
git clone --recurse-submodules -j8 https://github.com/Socrats/EGTTools.git
```

---
<a name="installation"/>

## Installation

Currently, the only way to install EGTtools is by compiling the source code.

To **install all required packages** run:

```bash
python -m venv egttools-env
source egttools-env/bin/activate
pip install -r requirements.txt
```

Or with anaconda:

```bash
conda env create -f environment.yml
conda activate egttools-env
```

Also, to make your virtual environment visible to jupyter:

```bash
conda install ipykernel # or pip install ipykernel
python -m ipykernel install --user --name=egttools-env
```

Finally, you can **install EGTtools** in your virtual environment by running:

```bash
python -m pip install <path>
```

Where ```<path>``` represents the path to the EGTtools folder. If you are running this while inside the EGTtools folder,
then ```<path>``` is simply ```./```.

If you wish, you may also install EGTtools in **development** mode, this will allow the installation to update with new
modifications to the package:

```bash
python -m pip install -e <path>
```

---
<a name="examples"/>

## Examples of usage

The [Analytical example](docs/examples/hawk_dove_dynamics.ipynb) is a jupyter notebook which analyses analytically the
evolutionary dynamics in a (2-person, 2-actions, one-shot) Hawk-Dove game.

The [Numerical example](docs/examples/normal_form_game_mc_simulations.ipynb) is a jupyter notebook which analyses
through numerical simulations the evolutionary dynamics in a (2-person, 2-actions, one-shot) Hawk-Dove game.

For example, assuming the following payoff matrix:

![A=\begin{pmatrix} -0.5 & 2 \\ 0 & 0 \end{pmatrix}](https://latex.codecogs.com/gif.latex?A=\begin{pmatrix}&space;-0.5&space;&&space;2&space;\\\\&space;0&space;&&space;0&space;\end{pmatrix})



You can plot the gradient of selection in a finite population of \(Z=100\) individuals and assuming and intensity of
selection ![\beta=1](https://latex.codecogs.com/gif.latex?\beta=1) in the following way:

```python
import numpy as np
import matplotlib.pyplot as plt
from egttools.analytical import StochDynamics

pop_states = np.arange(0, Z + 1, 1)

# Instantiate evolver and calculate gradient
evolver = StochDynamics(2, A, Z)
gradients = np.array([evolver.gradient_selection(x, 0, 1, beta)
                      for x in pop_states])
```

Afterwards, you can plot the results with:

```python
from egttools.utils import find_saddle_type_and_gradient_direction

# Find saddle points (where the gradient is 0)
epsilon = 1e-3
saddle_points_idx = np.where((gradients <= epsilon) & (gradients >= -epsilon))[0]
saddle_points = saddle_points_idx / Z

saddle_type, gradient_direction = find_saddle_type_and_gradient_direction(gradients,
                                                                          saddle_points_idx)

strategy_i = np.linspace(0, 1, num=Z + 1, dtype=np.float64)

ax = plot_gradient(strategy_i, gradients, saddle_points, saddle_type,
                   gradient_direction, 'Hawk-Dove game on Finite populations', xlabel='$k/Z$')
plt.show()
```

![Gradient of selection](docs/images/hawk_dove_analytical_gradient.png)

And you can plot the stationary distribution for a mutation rate ![\mu=1eˆ{-3}](https://latex.codecogs.com/gif.latex?\mu=1e-3) with:

```python
evolver.mu = 1e-3
stationary_with_mu = evolver.calculate_stationary_distribution(beta)
fig, ax = plt.subplots(figsize=(5, 4))
fig.patch.set_facecolor('white')
lines = ax.plot(np.arange(0, Z + 1) / Z, stationary_with_mu)
plt.setp(lines, linewidth=2.0)
ax.set_ylabel('stationary distribution', size=16)
ax.set_xlabel('$k/Z$', size=16)
ax.set_xlim(0, 1)
plt.show()
```

![Stationary distribution](docs/images/hawk_dove_analytical_full_sd.png)

We can obtain the same results through numerical simulations. The error will depend on how many independent simulations
you perform and for how long you let the simulation run. While a future implementation will offer an adaptive method to
vary these parameters depending on the variations between the estimated distributions, for the moment it is important
that you let the simulation run for enough generations after it has achieved a steady state. Here is a comparison
between analytical and numerical results:

```python
from egttools.numerical import PairwiseMoran
from egttools.numerical.games import NormalFormGame

# Instantiate the game
game = NormalFormGame(1, A)
numerical_evolver = PairwiseMoran(Z, game, 1000000)

# We do this for different betas
betas = np.logspace(-4, 1, 50)
stationary_points = []
# numerical simulations
for i in range(len(betas)):
    stationary_points.append(numerical_evolver.stationary_distribution(30, int(1e6), int(1e3),
                                                                       betas[i], 1e-3))
stationary_points = np.asarray(stationary_points)
# Now we estimate the probability of Cooperation for each possible state
state_frequencies = np.arange(0, Z + 1) / Z
coop_level = np.dot(state_frequencies, stationary_points.T)
```

Lastly, we plot the results:

```python
from sklearn.metrics import mean_squared_error

mse = mean_squared_error(coop_level_analytical, coop_level)

# Finally, we plot and compare visually (and check how much error we get)
fig, ax = plt.subplots(figsize=(7, 5))
# ax.scatter(betas, coop_level, label="simulation")
ax.scatter(betas, coop_level_analytical, marker='x', label="analytical")
ax.scatter(betas, coop_level, marker='o', label="simulation")
ax.text(0.01, 0.535, 'MSE = {0:.3e}'.format(mse), style='italic',
        bbox={'facecolor': 'red', 'alpha': 0.5, 'pad': 10})
ax.legend()
ax.set_xlabel(r'$\beta$', fontsize=15)
ax.set_ylabel('Cooperation level', fontsize=15)
ax.set_xscale('log')
plt.show()
```

![Comparison numerical analytical](docs/images/hawk_dove_comparison.png)

Finally, you may also visualize the result of independent simulations:

```python
init_states = np.random.randint(0, Z + 1, size=10, dtype=np.uint64)
output = []
for i in range(10):
    output.append(evolver.run(int(1e6), 1, 1e-3,
                              [init_states[i], Z - init_states[i]]))
# Plot each year's time series in its own facet
fig, ax = plt.subplots(figsize=(5, 4))

for run in output:
    ax.plot(run[:, 0] / Z, color='gray', linewidth=.1, alpha=0.6)
ax.set_ylabel('k/Z')
ax.set_xlabel('generation')
ax.set_xscale('log')
```

![Comparison numerical analytical](docs/images/hawk_dove_indep_runs.png)

---

## Documentation

The [analytical](egttools/analytical/sed_analytical.py) module contains classes and functions that you may use to
investigate the evolutionary dynamics in N-player games. For now only the replicator dynamics (for infinite populations)
and the Pairwise Comparison imitation process (for finite populations) are implemented.

When your state-space is too big (in finite populations), it might become computationally hard to solve the system
analytically. Thus, we provide an efficient [numerical](egttools/src/egttools) module written in C++ and compiled to
Python. You may use it to estimate the fixation probabilities and stiationary distribution through Monte-Carlo
simulations, or perform individual runs of the Moran process.

You can find more information in the [ReadTheDocs](https://egttools.readthedocs.io/en/latest/) documentation.

---

### Caveats

1. On Apple M1 (arm64) you should install (for the moment) [miniforge](https://github.com/conda-forge/miniforge), create
   a conda environment using it, and install EGTtools from the conda environment.

2. In MacOSX it is assumed that you have [Homebrew](https://brew.sh) installed.
3. You should install libomp with homebrew ``brew install libomp`` if you want to have support for parallel operations (
   there is a big difference in computation time).

4. You **must** have Eigen 3.3.* installed.

5. You **do not** need any of the above if you install EGTtools through ```pip install egttools```. This will soon be an
   option.

---

## Citing

You may cite this repository in the following way:

```latex
@misc{Fernandez2020,
  author = {Fernández Domingos, Elias},
  title = {EGTTools: Toolbox for Evolutionary Game Theory},
  year = {2020},
  publisher = {GitHub},
  journal = {GitHub repository},
  howpublished = {\url{https://github.com/Socrats/EGTTools}},
  doi = {10.5281/zenodo.3687125}
}
```

## Licence

* EGTtools is released under the [GNU General Public Licence](LICENSE), version 3 or later.
* [pybind11](https://github.com/pybind/pybind11) is released under [a BSD-style license](pybind11/LICENSE).
[![Documentation Status](https://readthedocs.org/projects/simulationpracticemd/badge/?version=latest)](https://simulationpracticemd.readthedocs.io/en/latest/?badge=latest)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/0fb7c77817fe41368642070f959648b5)](https://www.codacy.com/gh/SuldinVyacheslav/Inertia-MolecularDynamics/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=SuldinVyacheslav/practice&amp;utm_campaign=Badge_Grade)


![license](https://img.shields.io/github/license/SuldinVyacheslav/Inertia-MolecularDynamics)



## Lennard Jones simulation /w inertia moment effect

This repository aims to be convenient for solving molecular dynamics problems. 
Standard modeling tools have been implemented:  
* Lennard-Jones potential  
* Maxwell velocity distribution  
* Periodic boundary conditions.  

The mechanism for constructing graphs of the researching quantities is also implemented.
With the help of the above algorithms and formula for calculating the moment, influence on the motion of Brownian particles, caused by the moment of the inertia center is obtained.

## Demonstration

<p align="center">

      <img src="https://i.ibb.co/jGYJjqZ/left-online-video-cutter-com.gif">

</p>

## Dependencies

* SFML 2.0+ development headers and library

```
sudo apt-get install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libsfml-dev
```

* C++11 compliant compiler
* CMake build tool

## Repository 

Standard GitHub cloning, adding the recursive term for submodules.

```
git clone `https://github.com/SuldinVyacheslav/Inertia-MolecularDynamics.git`
```

## Installation

```
$ cd Inertia-MolecularDynamics
$ mkdir build/ && cd build/
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

## License

Source code of this repository is released under
the [Apache-2.0 license](https://choosealicense.com/licenses/apache-2.0/)

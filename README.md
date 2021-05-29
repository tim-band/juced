juced
=====

[![Build Status](https://travis-ci.org/kunitoki/juced.svg)](https://travis-ci.org/kunitoki/juced)

Community Based Juce

How to build
============

## Ubuntu ##

### Install prerequisites ###

```sh
sudo apt install premake4 libc6-dev liblo-dev libjack-dev libfftw3-dev \
libccptest-dev libsamplerate0-dev libsndfile1-dev libasound2-dev libgcc-9-dev \
libfreetype-dev libx11-dev libxext-dev libxi-dev libxinerama-dev \
libglu1-mesa-dev libgl-dev dssi-dev
```

Possibly lash and sqlite need installing as well for some configurations.

### Build ###

For example, from the base directory:

```sh
premake4 gmake
make bitmangler
```

You can add `config=release` to `make` for the release build. You can use
`make all` and `make clean` to make everything and clean everything.
You can't clean an individual project with make, but you can remove the
appropriate directory from `bin/intermediate`.

`premake4 --help` will include help on the configuration options suitable for
this project.

### Tests ###

```sh
make unit_testing
./bin/linux/unit_testing
```

And watch all the failures.

### Run ###

Run them from the `bin/linux` directory.

| app | description | working? | VST working in Jost? | VST working in Reaper? |
| :-- | :-- | :-- | :-- | :-- |
| analyzer | Looks like a spectrum analyzer | Runs, but no signal displayed | Not recognized as VST | |
| bitmangler | lo-fi distortion | Yes | Yes | Yes |
| capsaicin | Additive synth | Runs but no sound | Yes | Yes |
| drumsynth | Drum Synthesizer | Yes | Yes | Yes |
| dubdelay | Mad delay | N/A | Yes | Yes |
| eqinox | 6-band parametric equalizer | Yes | Yes | Yes |
| helix | Synth with brutalist UX | Yes | Yes | Yes |
| hybridreverb2 | Reverb | Runs, but what are these files it wants? | | Fails to scan |
| implzr | Impulse reverb (uses .wav files) | Yes? | | Yes? |
| jacked | | Runs, but just a blank screen | N/A | N/A |
| jost | VST host | Yes | N/A | N/A |
| kombat | No idea | N/A? | N/A? Doesn't recognize it as a plugin | N/A |
| monitor | Probably a monitor? But what sort of plugin | N/A? | N/A? | N/A |
| nekobee | Simple monosynth | Yes | Yes | Yes |
| notemap | What sort of plugin? | N/A? | N/A? | N/A |
| peggy2000 | Some sort of synth | Maybe... needs a huge screen, can't work it out | | |
| soundcrab | Soundfont player | Runs, but just drones | | |
| tal-filter | | runs, but sounds terrible | runs, sounds terrible | Yes |
| tal-reverb | Reverb | Yes, but clips | Yes, but clips | Yes |
| vex | Decent polysynth | Yes | Yes but sounds terrible | Yes |
| wolpertinger | Weird noise making synth | Yes | Yes | Yes |
| unit_testing | Tests | No | N/A | N/A |

## Windows ##

### Build ###

```
premake5 --file=premake4.lua vs2013
```

...or whichever Visual Studio version you like.

A file `juced.sln` will be produced, which you can open with
Visual Studio. You can now build the project.

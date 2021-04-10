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

Possibly lash and sqlite need installing as well for some effects.

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
| bitmangler | lo-fi distortion | Yes | | segfaults |
| capsaicin | | Segfaults | | |
| drumsynth | Drum Synthesizer | Memory allocation failure | | |
| dubdelay | What sort of plugin? | | | |
| eqinox | 6-band parametric equalizer | Yes | segfaults | segfaults |
| helix | | crashes | | |
| hybridreverb2 | Reverb | Runs, but what are these files it wants? | | |
| implzr | Impulse reverb | Runs, but needs an impulse file. What format? | | |
| jacked | | Runs, but just a blank screen | | |
| jost | VST host | Yes! | N/A | N/A |
| kombat | No idea | N/A? | N/A? Doesn't recognize it as a plugin | N/A |
| monitor | Probably a monitor? But what sort of plugin | N/A? | N/A? | N/A |
| nekobee | Simple monosynth | Yes | segfaults | segfaults during scanning! |
| notemap | What sort of plugin? | N/A? | N/A? | N/A |
| peggy2000 | Some sort of synth | Maybe... needs a huge screen, can't work it out | | |
| soundcrab | Soundfont player | | | |
| tal-filter | | runs, but sounds terrible | runs, sounds terrible | fails to scan |
| tal-reverb | Reverb | Yes | | |
| vex | | Crashes | | |
| wolpertinger | Weird noise making synth | Yes | Yes | |
| unit_testing | Tests | No | N/A | N/A |

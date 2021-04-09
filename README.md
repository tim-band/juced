juced
=====

[![Build Status](https://travis-ci.org/kunitoki/juced.svg)](https://travis-ci.org/kunitoki/juced)

Community Based Juce

How to build
============

== Ubuntu ==

=== Install prerequisites ===

```sh
sudo apt install premake4 libc6-dev liblo-dev libjack-dev libfftw3-dev \
libccptest-dev libsamplerate0-dev libsndfile1-dev libasound2-dev libgcc-9-dev \
libfreetype-dev libx11-dev libxext-dev libxi-dev libxinerama-dev \
libglu1-mesa-dev libgl-dev dssi-dev
```

Possibly lash and sqlite need installing as well for some effects.

=== Build ===

For example, from the base directory:

```sh
premake4 gmake
make bitmangler
```

You can add `config=release` to `make` for the release build (it doesn't work at
the moment, sadly). You can use `make all` and `make clean` instead.

`premake4 --help` will include help on the configuration options suitable for
this project.

=== Tests ===

```sh
make unit_testing
./bin/linux/unit_testing
```

And watch all the failures.

=== Run ===

Run them from the `bin/linux` directory.

| app | description | working? | VST working? |
| :-- | :-- | :-- | :-- |
| analyzer | | | |
| bitmangler | lo-fi distortion | Yes | |
| capsaicin | | Segfaults | |
| drumsynth | Drum Synthesizer | Memory allocation failure | |
| dubdelay | | Segfaults | |
| eqinox | 6-band parametric equalizer | Yes | |
| helix | | crashes | |
| hybridreverb2 | Reverb | Runs, but what are these files it wants? | |
| implzr | Impulse reverb | Runs, but needs an impulse file. What format? | |
| jacked | | Runs, but just a blank screen | |
| jost | VST host | Yes! | N/A |
| kombat | | N/A? | |
| monitor | | N/A? | |
| nekobee | Simple subtractive synth | Works, but segfaults if config file is already present | |
| notemap | | N/A? | |
| peggy2000 | Some sort of synth | Maybe... needs a huge screen, can't work it out | |
| soundcrab | Soundfont player | | |
| tal-filter | | segfaults | | |
| tal-reverb | Reverb | Yes | |
| vex | | Crashes | |
| wolpertinger | Synth | | |
| unit_testing | Tests | No | N/A |

# About

This was made for an assignment in [CPSC 599.86 - Computer Haptics](https://pages.cpsc.ucalgary.ca/~sonny.chan/cpsc599.86/) at the University of Calgary under [Dr. Sonny Chan](http://vt2.cpsc.ucalgary.ca/). It uses the [CHAI3D](http://www.chai3d.org/) haptics engine.

It is a basic dynamics engine (rigidbody physics simulation) supporting dynamic and static rigidbodies with sphere colliders, and spring constraints. Note that the TorsionSpring is unfinished and broken.

# Install

Unfortunately this will only work for Windows with Visual Studio, because I didn't bother with CMake. However, given its structure, it _should_ be easy to port to other platforms using CMake.

The project is structured as a CHAI3D module, so after downloading and building CHAI3D, simply clone the project into the CHAI3D/modules directory, and then build with Visual Studio.

# chai3d-dynamics

## Controls

| Control       | Action                                                                                                                                 |
| ------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| Space         | Toggle workspace lock for the current scene (so you cannot move the workspace)                                                         |
| Left          | Cycle scenes left                                                                                                                      |
| Right         | Cycle scenes right                                                                                                                     |
| 1             | Spawn a heavy sphere at (0, 0, 1) in the current scene                                                                                 |
| 2             | Spawn a light ball at your cursor position attached by a "rope" spring (only applies force to correct elongation) in the current scene |
| 3             | Toggle the visibility of the mesh for the current scene                                                                                |
| Device button | Delete objects touching the cursor                                                                                                     |

## Notes

- Green springs denote close to natural length
- Red springs denote longer than natural length
- Yellow springs denote shorter than natural length
- "Springs" on the second scene and on the balls attached to the cursor are "ropes"
- As easily visualized by pressing 3, the third scene has the basic horizontal spring connections described in the assignment. The fourth scene adds criss-cross springs which results in a much stronger mesh.
- I attempted to get torsion springs working but failed.

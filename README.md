# G4CMP Phonon Simulation
Program to Create Caustic Phonon Plots.

In order to utilize qubits as particle detectors, understanding energy dissipation in qubit substrate (Sapphire) phonon kinematics is essential. These mechanisms are strongly associated with correlated errors in qubit chips, as observed in cosmic muon and gamma ray absorption events reported recently. We are motivated to understand the scattering of sub-Mev Dark Matter (for scalar and vector mediators) and the phonon excitations with sub-eV energy in Sapphire. We attempt to better understand energy dissipation in Sapphire with phonon caustics and kinematics simulation. For this, We expand the capabilities of G4CMP to include the Sapphire Substrate Material. In this G4CMP program, you can obtain the phonon caustic images for Sapphire (Also this can work for other promising materials such as (GaAs, LiF, and SiO2).<br> 

Note.- For the moment the kinematic for those Substrate Materials  is only for Phonon Transportation. The kinematic for electron holes pair transportation is under construction.<br> 

How are the phonons generated in an experimental setup?

The Substrate Crystal has cooled to a low temperature (only a few degrees above absolute zero temperature). On one face of the Substrate, a metal film is deposited and on the opposite face, a superconductor material (sensor) is deposited. The phonons are produced by passing a short burst of current through a metal or by hitting the metal with a source of focused laser light. After the excitation, several non-spherical shells of phonons (Longitudinal and Transverse) are produced and detected on the superconductor detector (Increasing the temperature of the detector). It is possible to select the phonon mode by triggering the arrival time on the detector (Longitudinal phonons travel at different velocities).

How are the phonons caustics images produced?<br> 

The ballistic phonons emitted from a point source concentrate along certain directions of the crystal, this is called phonon focusing.<br> 

If we have a small detector and we want to see how those lines are concentrated in the space we have two options. Move the detector to different positions in the space and later plot the intensity (number of lines detected on the detector) obtained at every point of the space. The other option is to keep the detector fixed and move the source point. In both cases, we are going to obtain the same plots of the intensities as a function of the position. In an experiment is not possible to move the detector, therefore the point source is moved. In the case of the simulation, we can  move both the phonon source or the detector, also create a big detector area that covers the maximum possible directions. <br> 

On the simulation, we follow the approach of creating a big detector, because moving the source takes more time to end the simulation (on a standard laptop)~1 day. 


 The phonon simulation is simple in terms of geometry. The basic elements of the simulation are 

* A Sapphire substrate of 2mm x 2mm x 2mm.
* A big bolometer sensor of 2mm x 2mm x 0.0001 mm (Sensitive part where the phonons are absorbed).
* The new config.txt file with all the parameters for the Sapphire substrate.
* The Caustic.mac file to generate 40e+6 phonos with isotropic initial random momentum.
* The Caustic_plot.root program to plot the caustic pattern for Transverse Slow Phonons, Transverse Fast Phonons, or both together.
# Miller Orientations
The phonon caustic depends on the orientation of the crystal with the sensor. You can obtain different phonon caustics images by changing the crystal orientation. <br>
In the case of Sapphire 4 Miller indices are needed. The program 4_Miller_to_3_Miller.py converts 4 Miller indices to 3 Miller.<br>
For more information about  [4 Miller indices ](https://apps.dtic.mil/sti/trecms/pdf/AD1115835.pdf)
Note.- The program  4_Miller_to_3_Miller.py is designed to use only for Sapphire and macth the experimental results:


# How to Obtain the Phonon Caustics Patterns
We follow the standard procedure established on geant4 to compile and execute a program. 
```console
User@fun:~$ cmake ..
User@fun:~$ make install
[100%] Built target g4cmpPhononCaustics
```
If you do not have errors
```console
./g4cmpaSapphire Caustic.mac
```
You will have a txt file "phonon_hits.txt" with three columns: <br> 
The first is the name of the particle (Transverse Fast or Transverse Slow) <br> 
The second and third column is the final position (X,Y) of the phonons on the bolometer <br> 
If you want to plot only Transverse Fast Phonon Caustics
```console
 root 'Caustics_Plots.C("Fast")'
```
for Transverse Slow
```console
root 'Caustics_Plots.C("Slow")'
```
Both Phonons
```console
root 'Caustics_Plots.C("Both")'
```
Your plot will look like 
for 0 0 1 0 Miller Orientation .

# Phonon Caustic Plots



![Alt text of the image](https://github.com/Israel-Tanjiro/Sapphire_G4CMP/blob/main/Sapphire_Phonon.png)

# Adding New Materials 
The Folder Crystal Maps Includes the config.txt Files for other Substrate Materials.
You can reproduce the Phonon Caustics Pattern using the same program, you only need to change the followings lines on Caustic_PhononDetectorConstruction.cc file
You need to specify the materials 
```ruby
fSubstrate = new G4Material("fSubtrate", 3.98*g/cm3, 2);
fSubstrate->AddElement(nistManager->FindOrBuildElement("Al"), 2);
fSubstrate->AddElement(nistManager->FindOrBuildElement("O"), 3);

```
The important part is the FindOrBuildElement and the Density of the Material. The other  is only the name of the variables (fSapphire).
For example for GaAs the lines must be 
```ruby
fSubstrate = new G4Material("fSubstrate", 5.32*g/cm3, 2);
fSubstrate->AddElement(nistManager->FindOrBuildElement("Ga"), 1);
fSubstrate->AddElement(nistManager->FindOrBuildElement("As"), 1);
```
The other line of the code that you must change is this
```ruby
  G4LatticeLogical* SubstrateLogical = LM->LoadLattice(fSubstrate, "Al2O3");
```
to 

```ruby
  G4LatticeLogical* SubstrateLogical = LM->LoadLattice(fSubstrate, "GaAs");
```


The next steps is to compile and execute the program as the standard cmake .. and make commands<br> 
You can use the same root program to plot the phonon caustic plots.

# Using New Crystal Structures in Your Code
here’s a cool plot you can make for GaAs!
![Alt text of the image](https://github.com/Israel-Tanjiro/Sapphire_G4CMP/blob/main/Phonon_GaAS.png)




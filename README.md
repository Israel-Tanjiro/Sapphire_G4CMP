# Sapphire_G4CMP
Program to Create Caustic Phonon Plots.

In order to utilize qubits as particle detectors, understanding energy dissipation in qubit substrate (Sapphire) phonon kinematics is essential. These mechanisms are strongly associated with correlated errors in qubit chips, as observed in cosmic muon and gamma ray absorption events reported recently. We are motivated to understand the scattering of sub-Mev Dark Matter (for scalar and vector mediators) and the phonon excitations with sub-eV energy in Sapphire. We attempt to better understand energy dissipation in Sapphire with phonon caustics and kinematics simulation. For this, We expand the capabilities of G4CMP to include the Sapphire Substrate Material. In this G4CMP program, you can obtain the phonon caustic images for Sapphire (Also this can work for other promising materials such as (GaAs, LiF, and CaWO4)

This is the first simulation for a new material implemented on G4CMP after 10 years. The phonon simulation is simple in terms of geometry. The basic elements of the simulation are 

* A Sapphire subtrate of 2mm x 2mm x 2mm.
* A big bolometer sensor of 2mm x 2mm x 0.0001 mm (Sensitive part where the phonons are absorbed).
* The new config.txt file with all the parameters for the Sapphire substrate.
* The Causitic.mac file to generate 40e+6 phonos with isotropic initial random momentum.
* The Caustic_plot.root program to plot the caustic pattern for Transverse Slow Phononos, Transverse Fast Phonons, or both together.
# Miller Orientations
You can change the Miller Orientation using the following command
```ruby
/g4cmp/Miller_Sapphire  1 1 2 0 . # For Sapphire you need to specify four Miller Indices
```
In the program, We transform the 4 Miller indices into 3 Miller Indices.
In this example, we tested two Miller indices orientation 
```ruby
*/g4cmp/Miller_Sapphire  0 0 0 1
and
*/g4cmp/Miller_Sapphire  1 1 2 0
```

# How to Obtain the Phonon Caustics Patterns
We follow the standard procedure established on geant4 to compile and execute a program. 
```console
User@fun:~$ cmake ..
User@fun:~$ make install
[100%] Built target g4cmpPhononCaustics
```
If We do not have errors
```console
./g4cmpaSapphire Caustic.mac
```
You will have a txt file with three columns: <br> 
The first is the name of the particle (Transverse Fast or Transverse Slow) <br> 
The second and third column is the final position of the phonons on the bolometer <br> 
If you want to plot only Transverse Fast Phonon Caustics
```console
 root 'Cuastic_Plots.C("Fast")'
```
for Transverse Slow
```console
root 'Cuastic_Plots.C("Slow")'
```
Both Phonons
```console
root 'Caustic_Plots.C("Both")'
```
Your plot will look like 
for 0 0 0 1 Miller Orieantation .

# Phonon Caustic Plots



![Alt text of the image](https://github.com/Israel-Tanjiro/Sapphire_G4CMP/blob/main/Sapphire_Phonon.png)




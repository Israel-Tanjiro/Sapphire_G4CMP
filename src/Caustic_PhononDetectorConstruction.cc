/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file exoticphysics/phonon/src/PhononDetectorConstruction.cc \brief
/// Implementation of the PhononDetectorConstruction class
//
// $Id: a2016d29cc7d1e75482bfc623a533d20b60390da $
//
// 20140321  Drop passing placement transform to G4LatticePhysical
// 20211207  Replace G4Logical*Surface with G4CMP-specific versions.
// 20220809  [ For M. Hui ] -- Add frequency dependent surface properties.
// 20221006  Remove unused features; add phonon sensor pad with use of
//		G4CMPPhononElectrode to demonstrate KaplanQP.

#include "Caustic_PhononDetectorConstruction.hh"
#include "Caustic_PhononSensitivity.hh"
#include "G4CMPLogicalBorderSurface.hh"
#include "G4CMPPhononElectrode.hh"
#include "G4CMPSurfaceProperty.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4GeometryManager.hh"
#include "G4LatticeLogical.hh"
#include "G4LatticeManager.hh"
#include "G4LatticePhysical.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SolidStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4Tubs.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Caustic_PhononDetectorConstruction::Caustic_PhononDetectorConstruction()
  : fLiquidHelium(0),fAluminum(0),fOxigen(0),fSapphire(0),
    fWorldPhys(0), topSurfProp(0), botSurfProp(0), wallSurfProp(0),
    electrodeSensitivity(0), fConstructed(false) {;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

Caustic_PhononDetectorConstruction::~Caustic_PhononDetectorConstruction() {
  delete topSurfProp;
  delete botSurfProp;
  delete wallSurfProp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* Caustic_PhononDetectorConstruction::Construct()
{
  if (fConstructed) {
    if (!G4RunManager::IfGeometryHasBeenDestroyed()) {
      // Run manager hasn't cleaned volume stores. This code shouldn't execute
      G4GeometryManager::GetInstance()->OpenGeometry();
      G4PhysicalVolumeStore::GetInstance()->Clean();
      G4LogicalVolumeStore::GetInstance()->Clean();
      G4SolidStore::GetInstance()->Clean();
    }
    // Have to completely remove all lattices to avoid warning on reconstruction
    G4LatticeManager::GetLatticeManager()->Reset();
    // Clear all LogicalSurfaces
    // NOTE: No need to redefine the G4CMPSurfaceProperties
    G4CMPLogicalBorderSurface::CleanSurfaceTable();
  }

  Caustic_DefineMaterials();
  Caustic_SetupGeometry();
  fConstructed = true;

  return fWorldPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Caustic_PhononDetectorConstruction::Caustic_DefineMaterials()
{
  G4NistManager* nistManager = G4NistManager::Instance();

  fLiquidHelium = nistManager->FindOrBuildMaterial("G4_AIR"); // to be corrected
  fAluminum = nistManager->FindOrBuildMaterial("G4_Al");

 fOxigen = nistManager->FindOrBuildMaterial("G4_O");
fSapphire = new G4Material("fSapphire", 3.98*g/cm3, 2);
fSapphire->AddElement(nistManager->FindOrBuildElement("Al"), 2);
fSapphire->AddElement(nistManager->FindOrBuildElement("O"), 3);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void Caustic_PhononDetectorConstruction::Caustic_SetupGeometry()
{
    bool checkOverlaps = true;
  //
  // World
  //
  G4VSolid* worldSolid = new G4Box("World",6.*cm,6.*cm,6.*cm);
  G4LogicalVolume* worldLogical =
    new G4LogicalVolume(worldSolid,fLiquidHelium,"World");
  worldLogical->SetUserLimits(new G4UserLimits(10*mm, DBL_MAX, DBL_MAX, 0, 0));
  fWorldPhys = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"World",0,
                                 false,0);

  //
  // Germanium cylinder - this is the volume in which we will propagate phonons
  //
  // G4VSolid* fSapphireSolid = new G4Tubs("fSapphireSolid",0.*cm,3.81*cm,
  //                                        0.27*cm, 0.*deg, 360.*deg);
 G4VSolid* fSapphireSolid= new G4Box("fSapphireSolid",0.1*cm,0.1*cm,0.1*cm);

  G4LogicalVolume* fSapphireLogical =
    new G4LogicalVolume(fSapphireSolid,fSapphire,"fSapphireLogical");
  G4VPhysicalVolume* GePhys =
    new G4PVPlacement(0,G4ThreeVector(),fSapphireLogical,"fSapphirePhysical",
                      worldLogical,false,0,checkOverlaps);

  //
  //Germanium lattice information
  //

  // G4LatticeManager gives physics processes access to lattices by volume
  G4LatticeManager* LM = G4LatticeManager::GetLatticeManager();
  G4LatticeLogical* GeLogical = LM->LoadLattice(fSapphire, "Al2O3");

  // G4LatticePhysical assigns G4LatticeLogical a physical orientation
  G4LatticePhysical* GePhysical = new G4LatticePhysical(GeLogical);
  //Convertion of 4 Miller Indices to 3
  //1102 -> 332
  //0001
  GePhysical->SetMillerOrientation(0,2,1);// it was 0 0 1
  //  GePhysical->SetMillerOrientation(0,0,0);// it was 0 0 1
  // h=2H+K
  // k=2K+H
  // l=L

  LM->RegisterLattice(GePhys, GePhysical);

  // NOTE:  Above registration can also be done in single step:
  // G4LatticlePhysical* GePhysical = LM->LoadLattice(GePhys, "Ge");

  //
  // Aluminum - crystal end caps. This is where phonon hits are registered
  //
  // G4VSolid* fAluminumSolid = new G4Tubs("aluminiumSolid",0.*cm,0.5*cm,0.01*cm,
  //                                       0.*deg, 360.*deg);
  //G4VSolid* fAluminumSolid= new G4Box("aluminiumSolid",0.005*cm,0.005*cm,0.001*cm);// Real Dimension of the Detector
    //G4VSolid* fAluminumSolid= new G4Box("aluminiumSolid",0.1*cm,0.1*cm,0.001*cm); // This Works For some S
      G4VSolid* fAluminumSolid= new G4Box("aluminiumSolid",0.0075*cm,0.0075*cm,0.001*cm);
  //G4VSolid* fAluminumSolid = new G4Tubs("aluminiumSolid",0.*cm,0.5*cm,0.01*cm,0.*deg, 360.*deg);

  G4LogicalVolume* fAluminumLogical =
    new G4LogicalVolume(fAluminumSolid,fAluminum,"fAluminumLogical");
  G4VPhysicalVolume* aluminumTopPhysical = new G4PVPlacement(0,
    G4ThreeVector(0.,0.,0.101*cm), fAluminumLogical, "fAluminumPhysical",
    worldLogical,false,0,checkOverlaps);
  // G4VPhysicalVolume* aluminumBotPhysical = new G4PVPlacement(0,
  //   G4ThreeVector(0.,0.,-1.28*cm), fAluminumLogical, "fAluminumPhysical",
  //   worldLogical,false,1);

  //
  // detector -- Note : "sensitive detector" is attached to Germanium crystal
  //
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if (!electrodeSensitivity)
    electrodeSensitivity = new Caustic_PhononSensitivity("PhononElectrode");
  SDman->AddNewDetector(electrodeSensitivity);
  fSapphireLogical->SetSensitiveDetector(electrodeSensitivity);

  //
  // surface between Al and Ge determines phonon reflection/absorption
  //
  if (!fConstructed) {
    const G4double GHz = 1e9 * hertz;

    //the following coefficients and cutoff values are not well-motivated
    //the code below is used only to demonstrate how to set these values.
    const std::vector<G4double> anhCoeffs = {0, 0, 0, 0, 0, 1.51e-14};
    const std::vector<G4double> diffCoeffs =
      {5.88e-2, 7.83e-4, -2.47e-6, 1.71e-8, -2.98e-11};
    const std::vector<G4double> specCoeffs =
      {0,928, -2.03e-4, -3.21e-6, 3.1e-9, 2.9e-13};

    const G4double anhCutoff = 520., reflCutoff = 350.;   // Units external

    topSurfProp = new G4CMPSurfaceProperty("TopAlSurf", 1.0, 0.0, 0.0, 0.0,
					  	        0.3, 1.0, 0.0, 0.0);
    // topSurfProp->AddScatteringProperties(anhCutoff, reflCutoff, anhCoeffs,
		// 			 diffCoeffs, specCoeffs, GHz, GHz, GHz);
    //AttachPhononSensor(topSurfProp);// I am not interestering on KaplanQP Class

    botSurfProp = new G4CMPSurfaceProperty("BotAlSurf", 1.0, 0.0, 0.0, 0.0,
					   	        0.3, 1.0, 0.0, 0.0);
    // botSurfProp->AddScatteringProperties(anhCutoff, reflCutoff, anhCoeffs,
		// 			 diffCoeffs, specCoeffs, GHz, GHz, GHz);
    //AttachPhononSensor(botSurfProp); I am not interestering on KaplanQP Class

    wallSurfProp = new G4CMPSurfaceProperty("WallSurf", 0.0, 1.0, 0.0, 0.0,
					    	          1.0, 1.0, 0.0, 0.0);
    // wallSurfProp->AddScatteringProperties(anhCutoff, reflCutoff, anhCoeffs,
		// 			  diffCoeffs, specCoeffs, GHz, GHz,GHz);

  }

  //
  // Separate surfaces for sensors vs. bare sidewall
  //
  new G4CMPLogicalBorderSurface("detTop", GePhys, aluminumTopPhysical,
				topSurfProp);
  // new G4CMPLogicalBorderSurface("detBot", GePhys, aluminumBotPhysical,
	// 			botSurfProp);
  new G4CMPLogicalBorderSurface("detWall", GePhys, fWorldPhys,
				wallSurfProp);

  //
  // Visualization attributes
  //
  worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  G4VisAttributes* simpleDetectorAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  fSapphireLogical->SetVisAttributes(simpleBoxVisAtt);
  fAluminumLogical->SetVisAttributes(simpleDetectorAtt);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// Attach material properties and electrode/sensor handler to surface

void Caustic_PhononDetectorConstruction::
AttachPhononSensor(G4CMPSurfaceProperty *surfProp) {
  if (!surfProp) return;		// No surface, nothing to do

  // Specify properties of aluminum sensor, same on both detector faces
  // See G4CMPPhononElectrode.hh or README.md for property keys

  // Properties must be added to existing surface-property table
  auto sensorProp = surfProp->GetPhononMaterialPropertiesTablePointer();
  sensorProp->AddConstProperty("filmAbsorption", 1.0);    // True sensor area
  sensorProp->AddConstProperty("filmThickness", 600.*nm);
  sensorProp->AddConstProperty("gapEnergy", 173.715e-6*eV);
  sensorProp->AddConstProperty("lowQPLimit", 3.);
  sensorProp->AddConstProperty("phononLifetime", 242.*ps);
  sensorProp->AddConstProperty("phononLifetimeSlope", 0.29);
  sensorProp->AddConstProperty("vSound", 3.26*km/s);
  sensorProp->AddConstProperty("subgapAbsorption", 0.1);

  // Attach electrode object to handle KaplanQP interface
  surfProp->SetPhononElectrode(new G4CMPPhononElectrode); //I am commenting this, I am not interestering on KaplanQp intergace
}

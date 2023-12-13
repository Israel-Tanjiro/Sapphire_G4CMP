/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file exoticphysics/phonon/include/PhononDetectorConstruction.hh
/// \brief Definition of the PhononDetectorConstruction class
//
// $Id: 4c06153e9ea08f2a90b22c53e5c39bde4b847c07 $
//
// 20221006  M. Kelsey -- Remove "IsField" flag, unnecessary with phonons.
//		Add material properties for aluminum phonon sensors

#ifndef Caustic_PhononDetectorConstruction_h
#define Caustic_PhononDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4Material;
class G4VPhysicalVolume;
class G4CMPSurfaceProperty;
class G4CMPElectrodeSensitivity;


class Caustic_PhononDetectorConstruction : public G4VUserDetectorConstruction {
public:
  Caustic_PhononDetectorConstruction();
  virtual ~Caustic_PhononDetectorConstruction();

public:
  virtual G4VPhysicalVolume* Construct();

private:
  void Caustic_DefineMaterials();
  void Caustic_SetupGeometry();
  void AttachPhononSensor(G4CMPSurfaceProperty* surfProp);

private:
  G4Material* fLiquidHelium;
  G4Material* fAluminum;
  G4Material* fOxigen;
  G4Material* fSapphire;
  G4VPhysicalVolume* fWorldPhys;
  G4CMPSurfaceProperty* topSurfProp;
  G4CMPSurfaceProperty* botSurfProp;
  G4CMPSurfaceProperty* wallSurfProp;
  G4CMPElectrodeSensitivity* electrodeSensitivity;

  G4bool fConstructed;		// Flag to not re-recreate surface properties
};

#endif

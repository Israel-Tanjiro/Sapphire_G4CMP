/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file exoticphysics/phonon/src/PhononPrimaryGeneratorAction.cc
/// \brief Implementation of the PhononPrimaryGeneratorAction class
//
// $Id: e75f788b103aef810361fad30f75077829192c13 $
//
// 20140519  Allow the user to specify phonon type by name in macro; if
//	     "geantino" is set, use random generator to select.

#include "Caustic_PhononPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4Geantino.hh"
#include "G4ParticleGun.hh"
#include "G4RandomDirection.hh"
#include "G4PhononTransFast.hh"
#include "G4PhononTransSlow.hh"
#include "G4PhononLong.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

Caustic_PhononPrimaryGeneratorAction::Caustic_PhononPrimaryGeneratorAction() {

fParticleGun  = new G4GeneralParticleSource();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


Caustic_PhononPrimaryGeneratorAction::~Caustic_PhononPrimaryGeneratorAction() {
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


void Caustic_PhononPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  //fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  G4double selector = G4UniformRand();
  if (selector<0.5) {
  fParticleGun->SetParticleDefinition(G4PhononTransFast::Definition());}
  else{
  fParticleGun->SetParticleDefinition(G4PhononTransSlow::Definition());
  // fParticleGun->SetParticleDefinition(G4PhononLong::Definition());
  }
     fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

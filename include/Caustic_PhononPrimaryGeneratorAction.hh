/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

/// \file exoticphysics/phonon/include/PhononPrimaryGeneratorAction.hh
/// \brief Definition of the PhononPrimaryGeneratorAction class
//
// $Id: ecbf57649dfaeb88e0fac25491bf8fb68c9308ec $
//

#ifndef Caustic_PhononPrimaryGeneratorAction_h
#define Caustic_PhononPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"


class G4ParticleGun;
class G4Event;

class Caustic_PhononPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  Caustic_PhononPrimaryGeneratorAction();
  virtual ~Caustic_PhononPrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
    //G4ParticleGun*                fParticleGun;
    G4GeneralParticleSource *fParticleGun;

};


#endif

/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/


//20240110 Israel Hernandez -- Illinois Institute of Technology
#include "Caustic_PhononConfigManager.hh"
#include "Caustic_PhononConfigMessenger.hh"
#include "G4RunManager.hh"
#include <stdlib.h>


// Constructor and Singleton Initializer

Caustic_PhononConfigManager* Caustic_PhononConfigManager::theInstance = 0;

Caustic_PhononConfigManager* Caustic_PhononConfigManager::Instance() {
  if (!theInstance) theInstance = new Caustic_PhononConfigManager;
  return theInstance;
}

Caustic_PhononConfigManager::Caustic_PhononConfigManager()
  : Hit_file(getenv("G4CMP_HIT_FILE")?getenv("G4CMP_HIT_FILE"):"phonon_hits.txt"),
    messenger(new Caustic_PhononConfigMessenger(this))
    ,Millerh(getenv("G4CMP_Millerh")?strtod(getenv("G4CMP_Millerh"),0):1.0)// New commands to support 4 Miller indices
    ,Millerk(getenv("G4CMP_Millerk")?strtod(getenv("G4CMP_Millerk"),0):1.0)
    ,Milleri(getenv("G4CMP_Milleri")?strtod(getenv("G4CMP_Milleri"),0):1.0)
    ,Millerl(getenv("G4CMP_Millerl")?strtod(getenv("G4CMP_Millerl"),0):1.0)
{;}

Caustic_PhononConfigManager::~Caustic_PhononConfigManager() {
  delete messenger; messenger=0;
}


// Trigger rebuild of geometry if parameters change

void Caustic_PhononConfigManager::UpdateGeometry() {
  G4RunManager::GetRunManager()->ReinitializeGeometry(true);
}

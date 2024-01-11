/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/


//20240110 Israel Hernandez -- Illinois Institute of Technology
#include "Caustic_PhononConfigMessenger.hh"
#include "Caustic_PhononConfigManager.hh"
#include "G4UIcmdWithAString.hh"


// Constructor and destructor

Caustic_PhononConfigMessenger::Caustic_PhononConfigMessenger(Caustic_PhononConfigManager* mgr)
  : G4UImessenger("/g4cmp/", "User configuration for G4CMP phonon example"),
    theManager(mgr), hitsCmd(0) {
  hitsCmd = CreateCommand<G4UIcmdWithAString>("HitsFile",
			      "Set filename for output of phonon hit locations");
  MillerhCmd = CreateCommand<G4UIcmdWithADouble>("Millerh","Set the 1 Miller Indice");// New commands to support 4 Miller indice
 MillerkCmd = CreateCommand<G4UIcmdWithADouble>("Millerk","Set the 2 Miller Indice");
MilleriCmd = CreateCommand<G4UIcmdWithADouble>("Milleri","Set the 3 Miller Indice");
MillerlCmd = CreateCommand<G4UIcmdWithADouble>("Millerl","Set the 4 Miller Indice");
}


Caustic_PhononConfigMessenger::~Caustic_PhononConfigMessenger() {
  delete hitsCmd; hitsCmd=0;
  delete MillerhCmd; MillerhCmd=0;
  delete MillerkCmd; MillerkCmd=0;// New commands to support 4 Miller indice
  delete MilleriCmd; MilleriCmd=0;
  delete MillerlCmd; MillerlCmd=0;
}


// Parse user input and add to configuration

void Caustic_PhononConfigMessenger::SetNewValue(G4UIcommand* cmd, G4String value) {
  if (cmd == hitsCmd) theManager->SetHitOutput(value);
  if (cmd == MillerhCmd)
      theManager->SetMillerh(MillerhCmd->GetNewDoubleValue(value));
  if (cmd == MillerkCmd)
      theManager->SetMillerk(MillerkCmd->GetNewDoubleValue(value));
  if (cmd == MilleriCmd)
      theManager->SetMilleri(MilleriCmd->GetNewDoubleValue(value));
if (cmd == MillerlCmd)
          theManager->SetMillerl(MillerlCmd->GetNewDoubleValue(value));
}

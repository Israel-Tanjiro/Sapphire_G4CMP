/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

#ifndef Caustic_PhononConfigMessenger_hh
#define Caustic_PhononConfigMessenger_hh 1

// $Id$
// File:  PhononConfigMessenger.hh
//
// Description:	Macro command defitions to set user configuration in
//		PhononConfigManager.
//
// 20170816  Michael Kelsey

#include "G4UImessenger.hh"

class Caustic_PhononConfigManager;
class G4UIcmdWithAString;
class G4UIcommand;


class Caustic_PhononConfigMessenger : public G4UImessenger {
public:
  Caustic_PhononConfigMessenger(Caustic_PhononConfigManager* theData);
  virtual ~Caustic_PhononConfigMessenger();

  void SetNewValue(G4UIcommand* cmd, G4String value);

private:
  Caustic_PhononConfigManager* theManager;
  G4UIcmdWithAString* hitsCmd;

private:
  Caustic_PhononConfigMessenger(const Caustic_PhononConfigMessenger&);	// Copying is forbidden
  Caustic_PhononConfigMessenger& operator=(const Caustic_PhononConfigMessenger&);
};

#endif /* PhononConfigMessenger_hh */

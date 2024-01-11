/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

#ifndef Caustic_PhononConfigManager_hh
#define Caustic_PhononConfigManager_hh 1
//20240110 Israel Hernandez -- Illinois Institute of Technology, Quantum Science Center and Fermilab

#include "globals.hh"

class Caustic_PhononConfigMessenger;


class Caustic_PhononConfigManager {
public:
  ~Caustic_PhononConfigManager();	// Must be public for end-of-job cleanup
  static Caustic_PhononConfigManager* Instance();   // Only needed by static accessors

  // Access current values
  static const G4String& GetHitOutput()  { return Instance()->Hit_file; }
  static G4double GetMillerh(){ return Instance()->Millerh; }
  static G4double GetMillerk(){ return Instance()->Millerk; }
  static G4double GetMilleri(){ return Instance()->Milleri; }
  static G4double GetMillerl(){ return Instance()->Millerl; }

  // Change values (e.g., via Messenger)
  static void SetHitOutput(const G4String& name)
    { Instance()->Hit_file=name; UpdateGeometry(); }
  static void SetMillerh(G4double value)
       { Instance()->Millerh = value; UpdateGeometry(); }
  static void SetMillerk(G4double value)
          { Instance()->Millerk = value; UpdateGeometry(); }
  static void SetMilleri(G4double value)
             { Instance()->Milleri = value; UpdateGeometry(); }
  static void SetMillerl(G4double value)
                        { Instance()->Millerl = value; UpdateGeometry(); }

  static void UpdateGeometry();

private:
  Caustic_PhononConfigManager();		// Singleton: only constructed on request
  Caustic_PhononConfigManager(const Caustic_PhononConfigManager&) = delete;
  Caustic_PhononConfigManager(Caustic_PhononConfigManager&&) = delete;
  Caustic_PhononConfigManager& operator=(const Caustic_PhononConfigManager&) = delete;
  Caustic_PhononConfigManager& operator=(Caustic_PhononConfigManager&&) = delete;

  static Caustic_PhononConfigManager* theInstance;

private:
  G4String Hit_file;	// Output file 
  G4double Millerh;// Four Miller Indices
  G4double Millerk;
  G4double Milleri;
  G4double Millerl;

  Caustic_PhononConfigMessenger* messenger;
};

#endif

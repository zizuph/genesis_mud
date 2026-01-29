#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 4
#define SAT A_FEET
#define SAM ({0,0,0})
#define SNAME "boots"
#define SADJ "soft"
#define SSHORT "pair of soft leather boots"
#define SPSHORT "pairs of soft leather boots"

create_armour()
{
  set_name(SNAME);
  add_name(({"pair","pair of boots"}));
  set_adj(SADJ);
  add_adj(({"leather","short"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+", obviously made by orcs, provides "+
    "some protection to the feet of the wearer.  The boots hardly top "+
    "the calf of the wearer, and the leather is poorly tanned.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT)+random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(101));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
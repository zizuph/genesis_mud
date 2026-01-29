#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 23
#define SAT A_FEET|A_LEGS
#define SAM ({1,1,-2})
#define SNAME "boots"
#define SADJ "brigandine"
#define SSHORT "pair of brigandine leather boots"
#define SPSHORT "pairs of brigandine leather boots"

create_armour()
{
  set_name(SNAME);
  add_name(({"pair","pair of boots"}));
  set_adj(SADJ);
  add_adj(({"leather","tall"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+", although obviously made by orcs, seems "+
    "very well crafted.  Small steel plates are sandwiched between "+
    "layers of leather from the top of the foot to mid-thigh.\n");
  set_default_armour(SAC,A_FEET|A_LEGS,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,A_LEGS)-random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(51));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
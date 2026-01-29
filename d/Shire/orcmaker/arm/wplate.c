#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 37
#define SAT A_TORSO
#define SAM ({0,0,0})
#define SNAME "armour"
#define SADJ "plate"
#define SSHORT "bronze plate armour"
#define SPSHORT "bronze plate armour"

create_armour()
{
  set_name(SNAME);
  add_name(({"plate","barf"}));
  set_adj(SADJ);
  add_adj(({"iron","heavy"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" is rather heavy, crafted of thick bronze "+
    "plates that are then strapped together to protect the chest "+
    "and back of the wearer.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(651));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(51));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 4
#define SAT A_TORSO
#define SAM ({0,1,-1})
#define SNAME "vest"
#define SADJ "soft"
#define SSHORT "black doeskin vest"
#define SPSHORT "black doeskin vests"

create_armour()
{
  set_name(SNAME);
  add_name(({"leather","doeskin"}));
  set_adj(SADJ);
  add_adj(({"leather","doeskin"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" somewhat protects the chest and back of "+
    "the wearer with soft doeskin that has been dyed black and tooled "+
    "with crude designs of death and destruction.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(41));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
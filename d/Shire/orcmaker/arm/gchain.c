#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 28
#define SAT A_TORSO
#define SAM ({-2,3,-1})
#define SNAME "hauberk"
#define SADJ "alloyed"
#define SSHORT "alloyed steel hauberk"
#define SPSHORT "alloyed steel hauberks"

create_armour()
{
  set_name(SNAME);
  add_name(({"chainmail","mail"}));
  set_adj(SADJ);
  add_adj(({"chainmail","steel"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" bears the marks of orcish smiths, yet "+
    "it is extremely well crafted of a steel alloy. "+
    "Steel links of mail protect the wearer from harm in combat.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(51));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
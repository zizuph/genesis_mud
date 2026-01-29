#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 25
#define SAT A_TORSO
#define SAM ({-2,3,-1})
#define SNAME "hauberk"
#define SADJ "iron"
#define SSHORT "iron chainmail hauberk"
#define SPSHORT "iron chainmail hauberks"

create_armour()
{
  set_name(SNAME);
  add_name(({"chainmail","mail"}));
  set_adj(SADJ);
  add_adj(({"chainmail","dsa"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" bears the marks of orcish smiths, yet "+
    "it still appears to be rather sturdy and well made. "+
    "Iron links of mail protect the wearer from most harm in combat.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(11));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
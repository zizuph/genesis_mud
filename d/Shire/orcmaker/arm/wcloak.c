#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 3
#define SAT A_ROBE
#define SAM ({0,0,0})
#define SNAME "cloak"
#define SADJ "cloth"
#define SSHORT "cheap cloth cloak"
#define SPSHORT "cheap cloth cloaks"

create_armour()
{
  set_name(SNAME);
  add_name(({"cloth","barf"}));
  set_adj(SADJ);
  add_adj(({"cheap","soiled"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" is crudely woven from cheap, common plant "+
    "fibers.  It barely provides any protection, from the cold or "+
    "things more dangerous, but it is likely better than nothing.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(61));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(21));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
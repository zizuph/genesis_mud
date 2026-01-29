#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 10
#define SAT A_TORSO
#define SAM ({-1,0,1})
#define SNAME "vest"
#define SADJ "heavy"
#define SSHORT "heavy hide vest"
#define SPSHORT "heavy hide vests"

create_armour()
{
  set_name(SNAME);
  add_name(({"leather","hide"}));
  set_adj(SADJ);
  add_adj(({"leather","hide"}));
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" protects the back and chest of the wearer "+
    "fairly well, but the stench is enough to make one puke.  The hide "+
    "is untreated, and tufts of fur still stick out in places.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) - random(76));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }
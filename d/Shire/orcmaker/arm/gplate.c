#pragma save_binary

inherit "/lib/keep";
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define SAC 40
#define SAT A_TORSO
#define SAM ({0,0,0})
#define SNAME "breastplate"
#define SADJ "steel"
#define SSHORT "heavy steel breastplate"
#define SPSHORT "heavy steel breastplates"

create_armour()
{
  set_name(SNAME);
  // add_name(({"plate","platearmour"})); Why are these names, not adj?
  set_adj(SADJ);
  add_adj("heavy");
  set_short(SSHORT);
  set_pshort(SPSHORT);
  set_long("This "+short()+" is beautifully crafted of a high-strength "+
    "steel alloy. Seemingly delicate flower designs have been etched "+
    "into the breastplate to enhance its beauty and value.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT) + random(901));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(101));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
  set_keep();
}


string query_recover() { return MASTER+":"+query_arm_recover(); }
void init_recover(string arg) { init_arm_recover(arg); }

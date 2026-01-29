//  Mod:  Added /std/keep to this armour -Igneous

inherit "/std/armour.c";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

void create_armour()
{
  set_name("mail");
  add_name("hauberk");
  set_short("black steel hauberk");
  add_adj(({"black","steel"}));
  set_long("This "+short()+" is artfully forged of an unknown steel "+
    "alloy that is both black and lusterless. The mail is "+
    "tightly linked with additional strands of the metal woven "+
    "into the armour for additional strength. The "+short()+" is "+
    "very heavy because of all the extra steel alloy used in its "+
    "construction.\n");
  set_default_armour(50,A_TORSO,({-1,1,0}),0);
  set_likely_break(0);
  set_likely_cond(1);
  add_prop(MAGIC_AM_MAGIC, ({60,"enchantment"}));
  add_prop(MAGIC_AM_ID_INFO,
    ({"This "+short()+" is enchanted to provide superior protection "+
    "to the wearer.",15,
    "It resists breaking and being damaged when hit forcefully.",30,
    "However, the enchantment also causes the alloy to "+
    "increase greatly in weight.\n",64}));
  add_prop(OBJ_S_WIZINFO,"This "+short()+" provides improved "+
    "protection but weighs much more than comparable normal "+
    "armours.\n\n");
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(51,A_TORSO)+3000);
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(50)+random(41));
}

string
query_recover()
{
   return MASTER + ":" + query_arm_recover() + query_keep_recover();
}
 
void
init_recover(string arg)
{
   init_arm_recover(arg);
   
   init_keep_recover(arg);
}

#pragma save_binary

inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void create_armour()
{
  set_name("shield");
  add_name("waverunner");
  set_adj(({"small","white"}));
  set_short("small white shield");
  set_long("The "+short()+" is barely large enough to cover an arm "+
    "so obviously it was chosen for maneuverability, not coverage, "+
    "being made of a light steel alloy riveted to a wooden frame. The "+
    "front of the shield bears the symbol of its owner, a large black "+
    "swan swimming on a turbulent white sea.\n");
  set_default_armour(16,A_SHIELD,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(16)+random(51));
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(16,A_SHIELD)-random(101));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
}

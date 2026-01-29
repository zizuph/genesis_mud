#pragma strict_types
#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

#define SAC 15
#define SAT A_ROBE
#define SAM ({0,1,-1})

void
create_armour()
{
  set_name("cloak");
  set_adj(({"leather","heavy","studded"}));
  set_short("studded leather cloak");
  set_long("This "+short()+" is made of thick, cured leather that "+
    "is covered with small, steel studs along its entire length. "+
    "The cloak is heavy because of the studs, but it also provides "+
    "superior protection because of them.\n");
  set_default_armour(SAC,SAT,SAM,0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(SAC,SAT));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(SAC) + random(51));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
  set_keep();
}

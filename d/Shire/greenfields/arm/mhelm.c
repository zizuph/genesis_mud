inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

void create_armour()
{
  set_name("helm");
  set_default_armour(24,A_HEAD,0,0);
  set_short("black tabarded helm");
   add_adj(({"black","tabarded"}));
   set_long("This black tabarded helm looks not of orc-make, but "+
   "more dwarvish in nature. It is a bit dented, and so "+
   "probably gained in battle.\n");
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(22,A_TORSO)+random(121));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(24)+random(31));
}


inherit "/std/armour";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

create_armour()
{
  set_ac(35);
  set_at(A_BODY);
  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 10000);
  add_prop(OBJ_I_VALUE, 0);
  set_name("robe of orc hides");
  add_name(({ "hide", "robe", }));
  set_adj("reeking");
  set_long("A collection of orc hides roughly stitched together. "+
     "The gruesome array of hides protect the body of its wearer "+
     "fairly well. An overwhelming stench pervades the surroundings "+
     "of this makeshift armour.\n");
}

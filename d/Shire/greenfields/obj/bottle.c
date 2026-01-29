inherit "/std/drink";
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

create_drink()
{
  set_name("bottle");
  set_adj("large");
  set_short("large bottle"); 
  set_long("This is a large bottle of some murky liquid.\n");
  set_soft_amount(100);
  set_alco_amount(20);
  set_drink_msg("You down the murky liquid and toss the bottle away.\n");
  add_prop(OBJ_I_WEIGHT,400+random(101));
  add_prop(OBJ_I_VOLUME,300+random(101));
  add_prop(OBJ_I_VALUE,F_VALUE_ALCO(20));
}

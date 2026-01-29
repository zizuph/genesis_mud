inherit "/std/armour";

#include "/sys/wa_types.h"
#include <macros.h>
#include <stdproperties.h>

create_armour()
{

  set_name("robe");
  set_short("guardian robe");
  set_adj("guardian");
  add_adj("cirathian");
  set_long("This robe is made of wool and is red and black with the sign "+
    "of the cirathian guardian force on it.\n");
  set_ac(12);
  set_am(({0,1,-1})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  add_prop(OBJ_I_WEIGHT,1500);
  add_prop(OBJ_I_VOLUME,1000);
}

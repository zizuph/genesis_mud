inherit "/std/armour";

#include "/sys/wa_types.h"
#include <macros.h>
#include <stdproperties.h>

create_armour()
{

  set_name("robe");
  set_short("guardian robe");
  set_adj("guardian");
  set_long("This robe is made of leather and has the sign of Cirath on it.\n");
  set_ac(5);
  set_am(({0,1,-1})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,1000);
}

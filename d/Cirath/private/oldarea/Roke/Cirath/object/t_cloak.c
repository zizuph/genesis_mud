inherit "/std/armour";

#include "/sys/wa_types.h"
#include <macros.h>
#include <stdproperties.h>

create_armour()
{

  set_name("cloak");
  set_short("filthy cloak");
  set_adj("filthy");
  set_long("This cloak is made of cotton and hasn't been washed the last century.\n");
  set_ac(6);
  set_am(({0,1,-1})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  add_prop(OBJ_I_WEIGHT,1000);
  add_prop(OBJ_I_VOLUME,700);
}

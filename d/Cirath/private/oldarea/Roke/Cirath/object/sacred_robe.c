inherit "/std/armour";

#include "/sys/wa_types.h"
#include <macros.h>
#include <stdproperties.h>

create_armour()
{

  set_name("robe");
  set_short("white robe");
  set_adj("white");
  add_adj("ametist");
  set_long("This robe is made special for the members of the Holy Temple Order.\n "+
    "There is a large picture of an eagle on it. The robe is covered with small \n "+
    "ametists. They are probably worth quite a lot. \n");
  set_ac(25);
  set_am(({0,0,0})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  add_prop(OBJ_I_WEIGHT,4500);
  add_prop(OBJ_I_VOLUME,1000);
}

#pragma save_binary

inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h> 

create_object()
{
  int ran = random(3);
  set_name("pebble");
  set_adj("small");
  switch(ran)
  {
    case 0:
      add_adj("purple");
      set_short("small purple pebble");
      set_long("This "+short()+" has grey swirls that form neat "+
        "little patterns.\n");
    case 1:
      add_adj("brown");
      add_adj("rounded");
      set_short("rounded brown pebble");
      set_long("This is just a small, plain, "+short()+".\n");
    case 2:
      add_adj("grey");
      add_adj("slippery");
      set_short("slippery grey pebble");
      set_long("This small grey pebble is quite slippery!\n");
  }
  add_prop(OBJ_I_VOLUME,10+ran*2);
  add_prop(OBJ_I_WEIGHT,50+3*ran); 
  add_prop(OBJ_I_VALUE,50-4*ran);
}
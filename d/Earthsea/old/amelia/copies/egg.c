#pragma save_binary

inherit "/std/food";

#include <stdproperties.h>

create_food()
{
  set_name("egg");
  set_short("white egg");
  set_adj("white");
  set_long("A white egg, most likely from a hen.\n");

  add_prop(OBJ_I_WEIGHT,50);
  add_prop(OBJ_I_VOLUME,25);

  set_amount(50);
}
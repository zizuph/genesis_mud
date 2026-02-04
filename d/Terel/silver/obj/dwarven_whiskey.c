// Drink to be cloned to ~silver/body_guard.c
// Tomas  -- Feb 2000

#include <stdproperties.h>
inherit "/std/drink";

void
create_drink()
{
  set_name("dwarven whiskey");
  add_name("whiskey"); 
  add_name("flask");
  add_pname("flasks of dwarven whiskey");
  set_short("flask of dwarven whiskey");
  set_long("A flask of very strong whiskey made by dwarves.\n");
  set_soft_amount(75);
  set_alco_amount(100);
  
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 300);
}

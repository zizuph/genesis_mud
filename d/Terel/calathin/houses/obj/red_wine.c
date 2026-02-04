// Drink to be cloned to ~calathin/houses/npc/house4_captain.c
// Tomas  -- Feb 2000

#include <stdproperties.h>
inherit "/std/drink";

void
create_drink()
{
  set_name("glass of red wine");
  add_name("wine"); 
  add_name("glass");
  add_pname("glasses of red wine");
  set_short("glass of red wine");
  set_long("A glass of red wine.\n");
  set_soft_amount(70);
  set_alco_amount(100);
  
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 300);
}

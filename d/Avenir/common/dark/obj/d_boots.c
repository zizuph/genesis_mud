// Dwarven boots for treasure hunter
// Made by Boriska@Genesis Nov 1994

inherit "/std/armour";

#include <wa_types.h>

create_armour()
{
  set_name("boots");
  set_pname("boots");
  set_short ("dwarven boots");
  set_pshort ("dwarven boots");
  add_adj ("dwarven");
  set_long ("Squeaky leather boots of dwarven craft.\n");

  set_ac (7);
  set_at (A_FEET);
}

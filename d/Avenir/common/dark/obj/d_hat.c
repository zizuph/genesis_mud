// Dwarven hat for treasure hunter
// Made by Boriska@Genesis Nov 1994

inherit "/std/armour";

#include <wa_types.h>

create_armour()
{
  set_name("hat");
  set_short ("old hat");
  add_adj ("old");
  set_long ("Old black hat that could conceal a part of your face.\n");
  set_ac (5);
  set_at (A_HEAD);
}

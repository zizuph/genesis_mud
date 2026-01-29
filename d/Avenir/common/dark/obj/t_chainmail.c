// Chainmail worn by troll workers
// made by Boriska@Genesis, Nov 1994

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

create_armour ()
{
  set_name ("chainmail");
  set_short ("trollish chainmail");
  set_long ("Heavy armour, quite tiresome for your shoulders to carry.\n");
  set_ac (10);
  set_at (A_BODY);
  add_prop (OBJ_I_WEIGHT, 25000);
  add_prop (OBJ_I_VOLUME, 5000);
}

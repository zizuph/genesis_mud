// lancer_sash.c
// for dwarven_lancer.c
// Tomas  Feb. 2000

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("sash");
  set_short("crimson sash");
  add_adj(({"crimson", "silk"}));
  set_long ("A crimson colored silk sash worn by the " +
     "dwarven lancers of Stonehold.\n");
  set_ac (1);
  set_am(({ 0, 0, 0}));
  set_at (A_WAIST);
}
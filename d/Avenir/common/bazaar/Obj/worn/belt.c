// Standard mail shirt for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("belt");
  set_short("thin leather belt");
  add_adj(({"thin", "leather"}));
  set_long ("This is a normal belt that fastens around the waist.\n");
  set_ac (1);
  set_am(({ 0, 0, 0}));
  set_at (A_WAIST);
}

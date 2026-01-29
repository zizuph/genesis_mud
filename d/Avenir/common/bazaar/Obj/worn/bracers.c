
// Standard bracers for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("bracers");
  add_name("pair");
  set_short("pair of solid steel bracers");
  set_pshort("pairs of solid steel bracers");
  add_adj(({"solid", "steel"}));
  set_long ("This is a pair of sturdy steel bracers that fit nicely "
           +"over the arms, providing quite a bit  of protection, "
           +"especially against sharp weapons.\n");
  set_ac (20);
  set_am(({ 2, 2, -4}));
  set_at (A_ARMS);
}


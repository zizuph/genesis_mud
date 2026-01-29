// Standard cloak for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("cloak");
  set_short("blood-red cloak of velvet");
  add_adj(({"blood-red", "velvet"}));
  set_long ("This is a beautiful cloak of velvet, stained a ruby-red and "
           +"fastened at the neck by a small silver clip. It is an "
           +"extravagant item, and strange to find it on someone who "
           +"is not rich.\n");
  set_ac (3);
  set_am(({ -1, 0, 1}));
  set_at (A_ROBE);
}


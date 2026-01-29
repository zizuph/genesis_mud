
// Standard helm for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("helm");
  set_short("light helm");
  add_adj(({"light", "steel"}));
  set_long ("This is a light steel helm that offers a fair amount "+
            "of protection for the head.\n");
  set_ac (14);
  set_am(({ -2, 0, 2}));
  set_at (A_HEAD);
}


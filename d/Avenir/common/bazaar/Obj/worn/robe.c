 /* A cloak made for the librarian to wear */
 /* Glinda */

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name("robe");
  set_short("dark dusty robe");
  add_adj(({"dark", "dusty"}));
  set_long ("This dark dusty robe smells slightly of sweat, bearing " +
            "witness of your not being the first person to own it.\n");
  set_ac (3);
  set_am(({ -1, 0, 1}));
  set_at (A_ROBE);
}


// Standard helm for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name(({"helm", "helmet"}));
  set_short("low crowned steel helm");
  add_adj(({"low", "crowned", "steel"}));
  set_long ("This shiny steel helm reaches down "
           +"along the sides of the face and partially "
           +"encloses the neck.\n");
  set_ac (14);
  set_am(({ -2, 0, 2}));
  set_at (A_HEAD | A_NECK);
}


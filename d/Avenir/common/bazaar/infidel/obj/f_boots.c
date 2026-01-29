// Infidel boots for the females
//    -Ilyian, Oct 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
  set_name(({"boots","pair"}));
  set_short("long pair of soft leather boots");
  add_adj(({"long", "leather", "soft"}));
  set_long ("These boots reach to the mid-thigh, and are "
           +"made from fairly supple leather. They are "
           +"well broken-in, and quite comfortable.\n");
  set_ac (8);
  set_am(({ -1, 2, -1}));
  set_at (A_LEGS | A_FEET);
}

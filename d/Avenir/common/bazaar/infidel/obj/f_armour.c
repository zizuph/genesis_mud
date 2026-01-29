//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
  set_name("shirt");
  set_short("heavy woven shirt");
  add_adj(({"heavy", "woven"}));
  set_long ("This shirt is made from a weave of very heavy "
           +"cords, offering more protection that it would "
           +"at first appear.\n");
  set_ac (13 + random (3));
  set_am(({ -1, 3, -2}));
  set_at (A_BODY);
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 1000);
}

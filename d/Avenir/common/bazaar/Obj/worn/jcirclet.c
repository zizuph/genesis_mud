// golden circlet for jadestone doll
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>


void
create_armour ()
{
  set_short("heavy golden circlet");
  set_name(({"circlet","helmet","helm"}));
  set_adj(({"heavy","gold","golden"}));
  set_long ("This circlet seems to be made from a strong alloy "+
            "of gold and steel. It is masterfully crafted, providing "+
            "very good protection for the head because of the "+
            "enclosing shape, while at first glance it appears "+
            "only to be ornamental.\n");
  set_ac (35);
  set_am(({ 0, 2, -2}));
  set_at (A_HEAD);
  add_prop (OBJ_I_WEIGHT, 2000);  // about 5 pounds
  add_prop (OBJ_I_VOLUME, 2000);
  add_prop (OBJ_I_VALUE, 3000); // It is gold, after all...
}



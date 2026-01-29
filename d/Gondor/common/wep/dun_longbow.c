#include <stdproperties.h>
#include <formulas.h>

inherit "/std/bow";

public void
create_bow()
{
  set_adj("dunlending");
  add_name("longbow");
  set_short("dunlending longbow");
  set_long("This is a simple longbow made of ash with a worn leather strap " +
	   "tied around it for handle. Bows such as this are often used by " +
	   "the Dunlendings that live in the hill lands near the White " +
	   "Mountains.\n");
  add_prop(OBJ_I_WEIGHT, 1300);
  add_prop(OBJ_I_VOLUME, 3350);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 32) - 30);
  set_hit(28);
  set_pen(32);
}

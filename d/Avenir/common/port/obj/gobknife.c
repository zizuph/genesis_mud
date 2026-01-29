
inherit "/d/Avenir/inherit/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

#define LONG \
  "It is a little, steel knife used for self-defence.\n"

create_weapon()
{
  set_name("knife");
  set_pname("knives");
  set_adj("steely");
  set_long(LONG);
  set_short("knife");
  set_hit(8);
  set_pen(10);
  set_wt(W_KNIFE);
  set_dt(W_SLASH | W_IMPALE);
  set_hands(W_ANYH);
  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 120);
  add_prop(OBJ_I_VALUE, 60);
}

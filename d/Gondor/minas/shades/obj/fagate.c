inherit "/std/object";
#include <stdproperties.h>

create_object() {
  set_name("agate");
  add_adj("fire");
  add_name("stone");
  add_name("jewel");
  set_short("fire agate");
  set_pshort("sparkling jewels");
  set_long("This is a many hued jewel, it shows traces of red, green, gold, and brown.\n");
  add_prop(OBJ_I_WEIGHT,8);
  add_prop(OBJ_I_VOLUME,12);
  add_prop(OBJ_I_VALUE,120);
}

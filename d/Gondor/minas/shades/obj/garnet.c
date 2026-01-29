inherit "/std/object";
#include <stdproperties.h>

create_object() {
  set_name("garnet");
  add_name("jewel");
  add_name("stone");
  set_short("deep red garnet");
  set_pshort("deep red stones");
  set_long("This is a deep red garnet. One of the semi-precious stones of Middle-Earth.");
  add_prop(OBJ_I_WEIGHT,13);
  add_prop(OBJ_I_VOLUME,14);
  add_prop(OBJ_I_VALUE,600);
}

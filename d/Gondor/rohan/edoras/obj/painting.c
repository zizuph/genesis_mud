inherit "/std/object";

#include "/sys/stdproperties.h";

create_object() {
  set_short("painting");
  set_long("This is a worthless painting.\n");
  set_name(({"painting"}));
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,1000);
  add_prop(OBJ_I_VALUE,50);
}


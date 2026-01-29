inherit "/std/object";
#include "/sys/stdproperties.h";

create_object() {
  set_name("ruby");
  add_name("jewel");
  set_short("sparkling red ruby");
  set_pshort("sparkling jewels");
  set_long("This is a sparkling red ruby.\n");
  add_prop(OBJ_I_WEIGHT,8);
  add_prop(OBJ_I_VOLUME,12);
  add_prop(OBJ_I_VALUE,144);
}


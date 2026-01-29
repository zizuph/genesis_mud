inherit "/std/bow";

#include "/sys/stdproperties.h";

create_bow() {
  set_name("bow");
  add_name("recurve");
  add_adj("oxhorn");
  set_short("oxhorn recurve bow");
  set_long("With a handle made of oxhorn, and limbs of aged oak, "
    + "this " + query_short() + " looks like the type of weapon a "
    + "serious archer would cary into battle.\n");
  set_hit(40);
  set_pen(35);
  add_prop(OBJ_I_WEIGHT, 2400);
  add_prop(OBJ_I_VOLUME, 1200);
  add_prop(OBJ_I_VALUE, 216 + random(144));
}


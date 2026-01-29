inherit "/std/bow";

#include "/sys/stdproperties.h";

create_bow() {
  set_name("bow");
  add_name("longbow");
  set_short("great longbow");
  set_long("This is a great longbow, almost as long as a man is high.\n");
  set_hit(40);
  set_pen(35);
  add_prop(OBJ_I_WEIGHT, 2400);
  add_prop(OBJ_I_VOLUME, 1200);
  add_prop(OBJ_I_VALUE, 216 + random(144));
}

public void
did_parry(object att, int aid, int dt)
{
    ::did_parry(att, aid, dt);
    query_wielded()->change_to_sword();
}

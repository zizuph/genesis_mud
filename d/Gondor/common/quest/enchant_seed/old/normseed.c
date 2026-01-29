inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_object()
{
  set_name("seed");
  set_short("little green seed");
  set_long("This is the green seed of some unknown plant. There is nothing\n"+
    "special about it.\n");
  set_adj("little");
  set_adj("green");
  add_prop(OBJ_I_WEIGHT,5);
  add_prop(OBJ_I_VOLUME,5);
  add_prop(OBJ_I_VALUE,1);
}

init()
{
  add_action("plant_me","plant");
  add_action("plant_me","sow");
}

plant_me(string str)
{
  if (str == "seed" || str == "little seed" || str == "green seed" 
      || str == "little green seed") {
    write("You carefully plant the little green seed in the ground.\n");
    say(QCTNAME(this_player())+" sows a little green seed in the ground.\n");
    remove_object();
    return 1;
    }
  write(capitalize(query_verb())+" what?\n");
  return 1;
}

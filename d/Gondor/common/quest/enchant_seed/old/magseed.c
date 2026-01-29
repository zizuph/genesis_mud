inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_object()
{
  set_name("seed");
  add_name("enchanted_seed");
  set_short("little green, magic, red-shimmering seed");
  set_long("This is the green seed of some unknown plant. You feel there\n"+
    "is something special about it, as it seems to glow red a little.\n");
  set_adj("little");
  set_adj("green");
  set_adj("magic");
  set_adj("red-shimmering");
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
    write("You carefully plant the magic little seed in the ground.\n");
    say(QCTNAME(this_player())+" sows a little green seed in the ground.\n");
    seteuid(getuid()); /* Added by Nick */
    clone_object("/d/Gondor/common/herbs/lothore")->move(environment(this_player()));
    write("After a few moments a beautiful red flower grows up from the ground!\n");
    say("After a short while a red flower grows from the ground!\n");
    remove_object();
    return 1;
    }
  write(capitalize(query_verb())+" what?\n");
  return 1;
}

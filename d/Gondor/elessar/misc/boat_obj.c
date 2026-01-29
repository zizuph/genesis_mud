inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_object()
{
  set_name("boat");
  add_name("rowing boat");
  set_adj("rowing");
  set_adj("wooden");
  set_short("wooden rowing boat");
  set_long("@@long_func");
  add_prop(OBJ_M_NO_GET,1);
  add_prop(OBJ_I_WEIGHT,400000);
  add_prop(OBJ_I_VOLUME,10000);
  setup_boat();
}

init()
{
  ::init();
  add_action("enter_boat","embark");
  add_action("enter_boat","enter");
  add_action("enter_boat","use");
  add_action("enter_boat","board");
}

enter_boat(string str)
{
  if (str == "boat" || str == "in boat" || str == "aboard boat") {
    write("You try to climb aboard the wooden boat.\n");
    this_player()->move_living("aboard the boat.","/d/Gondor/elessar/misc/inboat");
    setup_boat();
    return 1;
    }
  else write(query_verb()+" what?\n");
  return 1;
}

setup_boat()
{
  seteuid(getuid(this_object()));
  "/d/Gondor/elessar/misc/inboat"->set_boat_obj(this_object());
}

no_of_persons()
{
  return "/d/Gondor/elessar/misc/inboat"->query_livings();
}

long_func()
{
  string longstr;
  longstr = "It is a little rowing boat made of wood, just big enough to "+
    "hold three persons. Right now there are "+no_of_persons()+" persons in the boat. ";
  if (!present("oars",find_object("/d/Gondor/elessar/misc/inboat"))) longstr = longstr +
    "There are no oars in the boat.\n";
  else longstr = longstr+"There is a pair of oars in the boat.\n";
  return break_string(longstr,70);
}



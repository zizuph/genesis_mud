#include <stdproperties.h>
#include "../stddefs.h"

#pragma save_binary

inherit OBJECT;
inherit STRINGLIB;

#define NAMES ({"tree", "palm", "palm tree"})

#define LONG \
  "It is a gently bowing palm tree.\n" + \
  "On its trunk, someone has enscribed: @@palm_date@@.\n" + \
  "Hmm... It has to be a date palm.\n"

#define GET_FAIL_MSG \
  "It is inseparable from the ground.\n"

string date;

create_object() {
  int weight;
  set_name(NAMES);
  set_adj(({"bowing", "palm"}));

  date = "" + (1 + random(28)) + "/"+ (1 + random(12));
  
  set_long(WRAP(LONG));

  weight = 200000 + random(100000);
  add_prop(OBJ_I_WEIGHT, weight);
  add_prop(OBJ_I_VOLUME, (weight * 12) / 10);
  add_prop(OBJ_M_NO_GET, GET_FAIL_MSG);
}


init()
{
  add_action("climb", "climb");
  ::init();
}

string palm_date()
{
  return date;
}

climb(str)
{
  if (!id(str))
    notify_fail("Climb what?\n");
  else {
    write("The palm tree is too small and weak to climb.\n");
    say(this_player()->query_name() +
	" tries to climb the palm tree, but find it too small and weak.\n",
	this_player());
    return 1;
  }
}

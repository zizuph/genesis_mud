inherit "/d/Gondor/common/lib/town";

#include <macros.h>

#include "/d/Gondor/defs.h"

object door;

create_room()
{
    hillside="west";
    height=4;
    road=1;
    density=2;
    extraline ="Kingsroad ends here, almost at the top of the hill. All off the west side of Edoras can be seen below you. The great lawns, that surround Meduseld's great walls can be see upwards to the east, but they can't be accessed from here. There is a white stonehouse to the west. There is a large sign over the door of the house. To the south, there is the house of a wealthy Rohirrim noble. Kingsroad continues towards a little square to the northeast. ";
   make_the_room();
  add_exit("/d/Gondor/rohan/edoras/edlibrary","west",0);
  add_exit("/d/Gondor/rohan/edoras/square2","northeast",0);
  door = clone_object(EDORAS_DIR + "rooms/path8door");
  door->move(TO);
  add_item(({"sign","large sign"}),"The sign states:'The Library of Edoras' in large black letters.\n");
}

init()
{
    add_action("do_read","read");
    add_action("knock_door","knock");
    ::init();
}

do_read(str)
{
  if(!str) return;
  if(str=="sign"|| str == "large sign") {
    write("It states:\n"+
    "The Library of Edoras\n");
    return 1;
  }
}

int
no_reaction()
{
  tell_room(TO, "There's no reaction.\n");
  return 1;
}

int
knock_door(string str)
{
  if(!stringp(str) || (str != "door" && str != "on door" && str != "at door"))
  {
    NF("Knock on what?\n");
    return 0;
  }
  write("You knock on the door of the house of a wealthy Rohirrim.\n");
  say(QCTNAME(TP)+" knocks on the door of the old building.\n",TP);
  set_alarm(10.0, 0.0, no_reaction);
  return 1;
}

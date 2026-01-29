/* created by Aridor 06/19/93 */

#include "../local.h"

inherit STREET_BASE

object ken;

query_to_jail()
{
  return "north";
}

void
reset_palan_room()
{
    if (ken)
      return;
    ken = clone_object(PLAINS_LIV + "kender");
    ken->move(TO);
}

void
create_palan_room()
{
    object door;

    set_short("Outside the Silver Dragon Inn");
    set_long("You are standing just outside the Silver Dragon Inn. A symbol " +
	     "of a dragon hangs above the door and there are windows next " +
	     "to the door, drawing your attention to them. Circle Street " +
	     "leads east and west and Library Lane goes off to the north.\n");

    add_item(({"symbol","dragon"}),
	     "It's a dragon made of silvery metal swaying lightly in the " +
	     "wind.\n");
    add_item(({"windows","window"}),"@@window_sign");

    door = clone_object(OBJ + "wooddoor");
    door->move(this_object());

    add_exit(ROOM + "street2","east","@@bend_north_east",1);
    add_exit(ROOM + "street8","west","@@bend_north_west",1);
    add_exit(ROOM + "street3","north",0,1);

    reset_room();
}


int
bend_north_east()
{
  write("The street bends to the northeast.\n");
  return 0;
}

int
bend_north_west()
{
  write("The street bends to the northwest.\n");
  return 0;
}


string
window_sign()
{

    string str = BS("Unfortunately, the windows are made of "
		    +  "a milky glass so you can't see anything "
		    +  "inside.",SL)
      + BS("You notice a sign hanging in the window saying: "
	   +  "                          "
	   +  "        JOB OFFERED --- ask the proprietor.",SL);

    return str;
}



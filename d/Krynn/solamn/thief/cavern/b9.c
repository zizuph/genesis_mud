/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a narrow cavern. There are narrow stairs leading down " +
	     "and you can make out a small hatch in the wall to the west.\n");
    
    add_exit(CAVERN + "a5","down");
    add_exit(CAVERN + "b7","west","@@topple_in_room");
    
    DARK;

    add_item("stairs","They are cut out of the rock, leading downwards.\n");
    add_item("hatch","It's made of stone, naturally fitting into the cavern. " +
	     "It seems large enough for you to fit through.\n");
}

int
topple_in_room()
{
    write("You push the hatch, topple forward as you attempt to get through, " +
	  "and staggering into the next room. The hatch closes behind you, " +
	  "becoming indistinguishable from the wall.\n");
    return 0;
}

void
reset_thief_room()
{
  if (present("chalk",TO))
    return;
  clone_object(OBJ + "chalk")->move(TO);
}

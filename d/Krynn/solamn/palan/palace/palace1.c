/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

#define JANITOR_ROOM "/d/Krynn/solamn/palan/palace/office4.c"

query_to_jail()
{
  return "west";
}

void
create_palan_room()
{
    set_short("Entrance Hall of the Palace");
    set_long(BS("This is the grand entrance hall of the palace of "
           + "Palanthas. Fine tapestries hang from the walls showing "
           + "battle scenes, but also palace life and hunting scenes. "
           + "A sign on the west doorway says that offices are in that "
           + "direction, whereas the east entrance is guarded. "
           + "Marble stairs lead up into the tower, but there is a "
           + "dim green light shining down from above.", SL));

    add_exit(PALACE + "palace2","east","@@guarded",0);
    add_exit(PALACE + "hall1","west",0,0);
    add_exit(PALACE + "palace5","up",0,1);
    add_exit(ROOM + "plaza","south");

    JANITOR_ROOM->load_me();
}


guarded()
{
    if (present("iletter", TP) || TP->query_wiz_level())
    {   
        write(BS("The guard steps aside from the door and lets "
           +  "you pass.",SL));
        return 0;
    }
    write(BS("The guard says: I am truly sorry, but you may only enter if "
           +  "you have been invited personally.",SL));
    return 1;
}


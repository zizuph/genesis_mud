/* created by Aridor 09/14/93 */
/* minor text modification by Vitwitch 08/08/21 */

#include "../local.h"
#include CLOCKH

inherit CITY_ROOMBASE;

#define JANITOR_ROOM "/d/Krynn/solamn/palanthas/palace/office4.c" 

 query_to_jail()
{
  return "west";
} 

void
create_palan_room()
{
    SHORT("Entrance Hall of the Palace");
    LONG("This is the grand entrance hall of the palace of "
           + "Palanthas. Fine tapestries hang from the walls showing "
           + "battle scenes, but also palace life and hunting scenes. "
           + "A sign on the west doorway says that offices are in that "
           + "direction, whereas the east entrance is guarded. "
           + "Marble stairs lead up into the tower, but there is a "
           + "dim light shining down from above.\n");

    EXIT(PALACE + "palace2","east","@@guarded",0);
    EXIT(PALACE + "hall1","west",0,0);
    EXIT(PALACE + "palace5","up",0,1);
    EXIT(ROOM + "plaza", "south",0,0);

    JANITOR_ROOM->load_me(); 
}


guarded()
{
    if (present("iletter", TP) || TP->query_wiz_level())
    {   
        write("The guard steps aside from the door and lets "
           +  "you pass.\n");
        return 0;
    }
    write("The guard says: I am truly sorry, but you may only enter if "
           +  "you have been invited personally.\n");
    return 1;
}


/*
ROOM: City Council hall end
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
    ::create_room();                         
    hear_bell = 2;                           

    set_short("The hallway of the City Council building");
    set_long(
      "This is the end of the hallway of the City Council building, with "+ 
      "an office to the west, and a debate chamber to the end northwest. "+
      "The hall is very plain, no accessories are standing anywhere, and no "+
      "carpet covers the dirty wooden floor. A stairway leads upwards to the north. "
    );
    set_time_desc(
      "Many people are walking up and down the corridor.\n",
      "It is unnaturally quiet around here.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CENTRAL(plaza/cc_hall1), "south", 0, 0, 0);
    add_exit(CENTRAL(plaza/cc_off2), "west", 0, 0, 0);
    add_exit(CENTRAL(plaza/cc_deb), "northwest", 0, 0, 0);
    add_exit(CENTRAL(plaza/cc_up), "up", 0, 0, 0);

    add_item("offices",
      "There is an office to the west with a sign on the door.\n"
    );

    add_item(({"office", "sign"}),
      "The office to the west has a sign on the door reading 'Council "+
      "Intelligence Association.'\n"
    );

    add_item(({"chamber", "debate chamber"}),
      "There is a soft mumbling comming from the debate chamber.\n"
    );
}

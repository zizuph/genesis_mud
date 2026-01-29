#pragma strict_types

#include "/d/Faerun/defs.h"

#include <stdproperties.h>

inherit "std/room";

public void
create_room()
{
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 0);

    set_short("An elaborate entry hall");
    
    set_long("Leaving the courtyard you enter a grand hallway. There " +
        "are statues here. With a few large potted plants. Sconces are " +
        "dimly lit. The hall wraps around the courtyard and provides exits " +
        "that lead to the rest of the building. The polished wood floor " +
        "gleams under your feet.\n");

    add_item(({"statues"}),
        "Lifesize statues stand at each corner of the hall.  " +
        "You recognize more depictions of Grecian Gods. \n");
        
    add_item(({"plants"}),
        "Pots of spathiphyllum stand guard at the open archways " +
        "leading into the guild and on the opposite side, further " +
        "into the premises.\n");
        
    add_exit("/d/Faerun/bootcamp/lounge", "lounge");
    add_exit("/d/Faerun/bootcamp/courtyard","courtyard");
	add_exit("/d/Faerun/bootcamp/sideyard","sideyard");
}
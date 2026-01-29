#pragma strict_types

#include "/d/Faerun/defs.h"
 
inherit "std/room";
 
public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 0);
    
    set_short ("A small side yard");

    set_long("This is a small sideyard located outside the main hall. It's " +
        " not as kept up as the main courtyard and it seems almost " +
        "forgotten. It is overgrown and there seems to be an old well in " +
        "the center of the yard.\n");
    
    add_item(({"gate"}),
        "There is a small wrought iron gate that is hanging ajar. The iron " +
        "is bent and curled entricately. Obviously done by hand.\n");
    
    add_item(({"iron","wrought-iron","iron","wrought"}),
        "The iron of the gate looks a bit rusty, as if it hasn't been oiled " +
        "in quite some time.\n");
    
    add_item(({"well"}),
        "There is a very old well in the center of the sideyard, it appears " +
        "as if it once held water, but no longer. There is a bucket seated " +
        "on the edge of the well, with an old rope attached and tied to a " +
        "crank.\n");
    
    add_item(({"bucket"}),
        "The old wooden bucket sits on the edge of the well. It is dry as a " +
        "bone.\n");
    
    add_item(({"rope"}),
        "The rope looks old and is a little frayed in some areas. It makes " +
        "you wonder if the well did have water, would it be able to hold a " +
        "full bucket?\n");
    
    add_exit("/d/Faerun/bootcamp/lounge", "lounge");
    add_exit("/d/Faerun/bootcamp/courtyard","courtyard");
	add_exit("/d/Faerun/bootcamp/menzo_start","drow");
}



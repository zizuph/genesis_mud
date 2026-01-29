inherit "/d/Emerald/ctower/room/ctower_base";
inherit "/d/Emerald/ctower/room/guardian_room";

#include "../../ctower.h" 

void
create_ctower_room()
{
    set_short("Tower stairs");
   
    set_long( "There is a set of spiral stairs leading up.  "+
        "They are evenly spaced and are almost transparent.  You can see "+
        "that the stairs end one flight up.\n" );
   
    add_item(({"wall", "ceiling"}),  "The walls are made "+
        "of a dark crystal that seems to absorb the light.\n" );
   
   
    add_item(({"stairs"}),  "The stairs appear to be quite sturdy "+
        "even though there doesn't seem to be any visible support.\n" );
   
    add_exit(CTOWER_ROOM_ELEM + "airsd", "up", exit_block, 2);
    add_exit(CTOWER_ROOM_ELEM + "elem11", "south");

    level = 2;  
    add_guardian();
}
 

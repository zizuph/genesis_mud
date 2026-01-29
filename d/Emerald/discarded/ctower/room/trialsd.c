inherit "/d/Emerald/ctower/room/ctower_base";
inherit "/d/Emerald/ctower/room/guardian_room";
 
#include "../ctower.h"

void
create_ctower_room()
{
    set_short("Tower stairs");
   
    set_long("There is a set of spiral stairs leading down.  "+
	"They are evenly spaced and are almost transparent.  You can see "+
	"that the stairs end one flight down.\n");
   
    add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
	"milky crystal that is cold to the touch.\n");
   
    add_item(({"stairs"}),  "The stairs appear to be quite sturdy "+
	"even though there doesn't seem to be any visible support.\n");
   
    add_exit(CTOWER_ROOM + "mazesu", "down", 0, 2);
    add_exit(CTOWER_ROOM_ELEM + "elem2", "north", exit_block);

    level = 1;  
    add_guardian();
}

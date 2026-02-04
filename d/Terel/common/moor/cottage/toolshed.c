// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
// This room is newly accessible because it is part of the safe-cracking
// quest that Sorgum was working on but never implemented. 
//
// Revisions:
//    Lilith, Feb 2022: updated powder clone amts so players have extra
//                      to experiment with.


#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "../local.h"
	
void
create_room()
{
    set_short("toolshed");
    set_long(
	"The toolshed has no windows and is rather dark. You are able " +
	"to see by the light of day through the door behind you. " +
	"There are shelves with various bottles and tools on them and " +
	"various gardening equipment lying around stacked against the " +
	"walls. The floor is littered with the remnants of several " +
	"powdered substances.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);
    add_exit("cottage_garden", "south", 0);    
	
    seteuid(getuid(TO));
    add_object(OBJDIR + "scissors", 1);
    add_object(OBJDIR + "rake", 1);
    add_object(OBJDIR + "hammer", 1);

    add_object(OBJDIR + "al_powder", 2+(random(4)));
    add_object(OBJDIR + "white_powder", 2+(random(4)));
    add_object(OBJDIR + "black_powder", 2+(random(4)));

}



// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
create_room()
{
    set_short("hill top");
    set_long(
        "You stand at the top of a long hill sloping gently downwards " +
        "towards a small cottage.  Singing birds trill and hover above you " +
        "on stuttering wings.  In the distance rocky crags and jagged peaks " +
    	"form a majestic crest that pokes above the horizon.\n"
    );

    add_item(({"cottage", "small cottage"}), 
	"The cottage is to far away to get a good look at.  You could " +
	"probably get a better look at the bottom of the hill.\n"
    );

   
    add_prop(ROOM_I_INSIDE, 0);

    add_exit("hill_mid", "north", 0);
    add_exit("creek_incline", "east", 0);
}



inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
    set_short("Balcony");
    set_long("This is a stone balcony surrounding this tower at its"+
	" second floor.  The forest lies below and all around you." +
	"  Far off to the west, you can see the Sea of Rhun.\n");

    add_item(({"sea", "sea of rhun" }), "@@room_desc@@");
    add_exit(RHUN_DIR+"tower/inside/2balcony2", "east", 0);
        
}

string
room_desc()
{
    string desc, time = tod();

    switch(time)
    {
        case "evening":
        case "night": desc = "Although it's " + time + " now, the Sea of "
                           + "Rhun can be seen easily in the moonlight.\n";
            break;
        default: desc = "The Sea of Rhun is glittering beautifully in the "
                      + "bright sunlight.\n";
            break;
    }
    return desc;
}

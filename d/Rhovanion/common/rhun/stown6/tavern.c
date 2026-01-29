inherit "/std/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Rhovanion/farlong.h"

void
create_room()
{

	set_short("Abandoned tavern");
	set_long(break_string("The interior of this abandoned tavern"
		+" is especially sparse and vacant.  The owner has apparently"
		+" sold off everything he could to save his business."
		+"  There is a menu here which you may read.  The only"
		+" exit leads back out to the north.\n",75));

add_item("menu","The menu was meant to be read.\n");

AE(RHUN+"stown6/road_sw","north",0);

add_prop(ROOM_I_LIGHT,1);
IN

    add_cmd_item("menu", "read", "@@read");

    add_prop(ROOM_I_INSIDE, 1);

    add_drink( ({ "whiskey", "whiskeys", "stale", "stale whiskeys" }),
    "whiskey", "stale", 150, 15, 100, 0, 0,
    "This whiskey looks like it has been sitting for a long time.\n");
    add_food (({ "venison", "tough", "tough venison" }),
        "venison","tough",90,5+(90*90/600),0,0,
    "It seems like the cook intentionally picked the worst deer he could " +
        "find for this piece.\n");
}

init()
{
    ::init();
    init_pub();
}

int
read(string str)
{
    write("" +
    "   Fine imported whiskey             100 cc\n" +
    "   Tender venison strips             200 cc\n" +
    "");
    return 1;
}


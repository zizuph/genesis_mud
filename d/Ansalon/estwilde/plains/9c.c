#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit BPLAINS_OUT;
#define R1 "8c"
#define R2 "9d"
#define R4 "8b"
#define THROTYL "/d/Krynn/throtyl/rooms/throtyl-15-4-E"

#define THROTYL_OPEN 1

void
reset_estwilde_room()
{
    return;
}

create_estwilde_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + R1,"north",0);
    add_exit(ROOM + R2,"east",0);
    add_exit(ROOM + R4,"northwest",0);
    add_exit(THROTYL, "southwest", "@@check_season", 4, 1);

    add_item_hill();

    add_item(({"throtyl", "moors", "moorlands", "bogs", "boggy moors", 
        "plain","pass"}),
        "To your southwest is Throtyl, a land of vast moorlands " +
        "filled with nomadic goblin races. Heath and peat bogs are common " +
        "here, and this poorly drained land is inundated with rain " +
        "throughout the year. Even when at its driest the moors are " +
        "exhausting to navigate, but during the wet season almost " +
        "impossible.\n");

    reset_estwilde_room();
}

string
short_descr()
{
    return tod_descr1() + " on the edge of the Throtyl moorlands";
}

int
check_season()
{
    if(!THROTYL_OPEN)
    {
        write("The moors are currently flooded. You are unable to " +
            "travel in that direction.\n");
        return 1;
    }

    if(GET_SEASON == SPRING)
    {
        write("The moors are impassable in that direction due to " +
            "flooding from spring rains. You can only travel in " +
            "that direction in the less-wet seasons.\n");
        return 1;
    }
    else
        return 0;
}

string
long_descr()
{
    return plain_desc()+
    "To your southwest is a pass between the hills that leads to " +
    "the moorlands of Throtyl.\n";
}

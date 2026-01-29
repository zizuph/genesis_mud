/*
 * The Beach of Faerie, beneath the second pier
 * By Finwe, April 2005
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit BEACH_BASE;

int do_climb(string str);

void
create_beach_room()
{
    FIXEUID;
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("Underneath the landing");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The landing " +
        "stretches northwest and east as it runs above you. The beach " +
        "is wide and slopes north into the water. Waves lap at the " +
        "sand leaving marks on it.\n");

    add_item(({"logs", "large logs"}),
        "They were cut from the forest centuries ago. They are used as " +
        "pilings and support the landing. One side of the a log looks " +
        "strange, with grooves cut into it.\n");
    add_item(({"grooves"}),
        "They are carved into a piling and run up the side of it.\n");

    reset_room();
    
    set_add_beach();
    set_pier_bottom();

    add_exit(FOREST_DIR + "beach01s", "east");
    add_exit(FOREST_DIR + "beach01n", "northwest");
    
}
void
reset_room()
{
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
}

int
do_climb(string str)
{
    if (!str)
    {
        write("Climb what?\n");
        return 1;
    }

    if (!parse_command(str, ({}),
        "[landing] [up] [pier] [log] [logs] [piles] [piling] [pilings] [grooves] "))
    {
        write("Climb where?\n");
        return 1;
    }

    write("With great effort, you carefully climb up the side of the " +
        "landing.\n");
    say(QCTNAME(TP) + " climbs carefully up the side of the landing.\n");
    TP->move_living("M",FOREST_DIR + "landing",1,0);
    say(QCTNAME(TP) +" arrives climbing up the landing.\n");
    return 1;
}

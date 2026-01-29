/* 
 * A sample farm road room for Ardent
 *
 * Varian - April, 2020
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>

public void drink_message(string from);

void 
create_farms_room()
{
    set_items_road();
    set_items_mill();
    set_herbs_1();

    set_short("Sample farms room");
    
    set_long("This is a sample room for the farms area, it occupies " +
        "the same space as farmroad07. But you do think it is nice " +
        "to see the " + VBFC("light_type") + " from the " + 
        VBFC("day_desc") + " " + VBFC("sun_moon") + " shining " +
        "down on a small pool here. The " + VBFC("daylight_desc") + 
        "is nice to look at.\n");

    add_item( ({"fence", "fences", "wooden fence", "wooden fences",
            "low fence", "low fences", "low wooden fence",
            "low wooden fences"}),
        "There are some low wooden fences strung out along the " +
        "side of the road.\n");
    add_item( ({"pool", "small pool", "water"}),
        "This is a small pool of water, you could probably drink " +
        "from it!\n");

    add_tell("An old farmer drives his wagon north towards the " +
        "city of Drakmere.\n");

    add_exit(FARMS_DIR + "farmroad06", "north");
    add_exit(FARMS_DIR + "farmroad08", "east");
    add_exit(FARMS_DIR + "farmroad09", "south");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "west"}),
        "There are some small fences along the side of the road " +
        "preventing you from going in that direction!\n");

    set_drink_from(({"pool", "small pool"}));
}

int *
query_coordinates()
{
    return ({38, 17, 0}); 
}

void
init()
{
    ::init();
    init_drink();
}

public void
drink_message(string from)
{
    write("Stooping down, you take a drink of cool water from the " +
        "small pool here.\n");
    say(QCTNAME(TP) + " stoops down and takes a drink of water from " +
        "the small pool here.\n");
}
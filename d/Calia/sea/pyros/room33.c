
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/mountain/defs.h"


void
create_room()
{
    set_short("A foggy room in a dark tunnel");
    set_long("You can barely make anything out in this room as the "+
        "fog is so thick here.  The air in this room is very cold.  "+
        "You can see some sort of shiny object in the room.  The only "+
        "exit is back to the west.\n");

    add_item("fog","The fog is white and very thick here.  You can "+
        "barely make out your hand in front of your face.\n");

    add_item(({"object","shiny object"}),"After closer examination, "+
        "the shiny object seems to be a statue made of ice.  The "+
        "fog is being created by warm air below the statue rising "+
        "through cracks in the floor.  The air does not seem to be "+
        "hot enough to melt the statue, just to create this fog.\n");

    add_item("cracks","The cracks in the floor are very small.  "+
        "Looking down through them you see lava flowing.\n");

    add_item("statue","The statue is roughly five and a half feet "+
        "tall and is of a human female.  She is holding her hands "+
        "above her head as if she is calling out to her god.\n");

    add_exit(CAVE+"room32","west");
}

void
init()
{
    ::init();
    add_action("try_hold","hold");
}

int
try_hold(string str)
{
    notify_fail("Hold what?\n");
    if (str == "my hands above my head")
    {
        this_player()->catch_msg("You are sucked into "+
            "the statue.\n");
        this_player()->move_living("into the statue",CAVE+"water/entrance",1);
        return 1;
    }
    return 0;
}

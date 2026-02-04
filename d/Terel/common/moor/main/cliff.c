inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/include/Terel.h"
#include "../local.h"


void
create_room()
{
    set_short("Cliff over the Moors");
    set_long("This is a small ledge in the cliff above the moors and swampland. "
        +"It has been eroded away over the years, causing a cave to open in "
		+"the wall.\n");

    add_item("cave", "It is very dark.\n");
    add_item("cliff", "It is a narrow crumbling bit of rocks.\n");
    add_item("swamp", "It spreads out below the cliff.\n");
    add_item("wall", "It is crumbling away.\n");
    add_exit("swamp", "down", 0);
    add_exit("cave", "in", 0);
    add_cmd_item("cliff", "climb", "@@climb@@");

}

int
climb()
{
    int skill;
    skill = TP->query_skill(SS_CLIMB);
    if (skill > 29){
        tell_room(environment(this_player()), QCTNAME(this_player()) +
                " scrambles up the cliff.\n", this_player());

        this_player()->catch_msg("You scramble up the cliff.\n");

        set_dircmd("cliff");
        TP->move_living("up", MOOR_DIR +"tcaves/entrance");
        return 1;
    }
    this_player()->catch_msg("You fail to get a sure footing.\n");
    return 1;

}


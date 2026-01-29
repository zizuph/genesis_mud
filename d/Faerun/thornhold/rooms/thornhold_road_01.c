/*
 * Road to Thornhold
 * -- Twire/Gnim June 2016
 * Added secret path to Waterdeep,
 * blocked the north exit until Thornhold is approved.
 * Raymundo, 2019
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

#define SOUTHWARD_DIR "/d/Faerun/waterdeep/southward/"

inherit BASE_ROAD;
int
block_people()
{
    write("A burly dwarven guard steps out of the shadows.\nHe looks at "
        + "you and says: Thornhold Castle is not accepting vistors at "
        + "the moment. I would turn back if I were you.\nHe glares "
        + "menacingly at you.\n");
        return 1;
}
void
create_road()
{
	string exit_right = "northeast";
	string exit_left = "north";

	add_road();
	
    add_twoway_road_string(exit_left, exit_right);
	add_extra_string_end("The High Road is just around the northeast " +
	"bend, and from here you can see it stretching northwest along " +
	"the edge of the swampy mere, and southeast along the Sword Coast.");

    remove_item("cliff");
    add_item("cliff", "The cliff is rocky and steep here. Far below, you "
        + "see the coastline.\n");
    add_item( ({"coast", "coastline", "coast line"}),
        "The coastline is far below you, beneath this jagged cliff. You "
        + "notice a path running southward along the coast. You may well "
        + "be able to climb the cliff down to it.\n");
    add_item("path", "The path runs along the coast in a southernly "
        + "direction.\n");
    reset_faerun_room();

    add_exit("/d/Faerun/highroad/rooms/srd12",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_02",   exit_left, block_people);
    
    set_no_exit_msg(({"west", "northwest"}),
    "A sheer, jagged rock blocks passage in that direction.\n");

    set_no_exit_msg(({"east"}),
    "There is no sure footing to make your way to the High Road by " +
    "going directly east, but the northeast road leads directly there.\n");

    set_no_exit_msg(({"southwest", "south", "southeast"}),
    "Sharp and jagged rocks, slick with sea air, create a slippery " +
    "embankment that offers no egress in that direction.\n");
}

public void
init()
{
    ::init();
    add_action("climb_cliff", "climb");
}

void
reset_faerun_room()
{
    set_searched(0);
}

int
climb_cliff(string str)
{
        if(!strlen(str))
    {
        notify_fail("Climb what? Down the cliff?\n");
        return 0;
    }
    
    
    if (parse_command(str, TO,  
        " [down] [the] [steep] [jagged] [steep] 'cliff' ") )
    {
        if(TP->query_skill(SS_CLIMB) <=20)
        {
            notify_fail("The cliff is too steep for you!\n");
            return 0;
        }
        else
        {
        write("You climb down the cliff!\n");
        say(QCTNAME(TP) + " climbs down the cliff!\n");
        tell_room(SOUTHWARD_DIR + "o_n_11", QCTNAME(TP) + " arrives from "
            + "above!\n");
        TP->move_living("M", SOUTHWARD_DIR + "o_n_11");
        return 1;
        }


    }
    else
    {
        notify_fail("Climb what? Down the cliff?\n");
        return 0;
    }
}
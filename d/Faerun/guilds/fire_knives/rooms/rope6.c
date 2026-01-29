/* /d/Faerun/guilds/fire_knives/rooms/rope6.c
 *
 * Climbing the rope, step 6.
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1); 

    set_short("At the end of the rope");
    
    set_long("All around you the massive walls of mountains protect "
    +"you from the "
    +"wind and snow. Amidst the encroached "
    +"narrow space in between the rocks "
    +"security reigns a silence complete, broken only by "
    +"your own respiration as "
    +"you continue climbing. Right above you a dim "
    +"light becomes clear around "
    +"the contour of a hole through which you could climb out of. \n");

    add_item(({"hole","contour"}),
    "The hole is right above you, the rope you are holding crawling out of "
    +"it to be held somewhere on the surface. You could crawl through it to "
    +"reach it as well.\n");

    add_item(({"rope"}),
    "You are hanging from the rope that extends from "
    +"the top of the hole to the "
    +"floor below. You could down on it. \n");

   /* Climb up rope / Climb down rope */

    add_item(({"sky"}),
    "The sky cannot be seen from here, obscured from view "
    +"by the narrow passage up "
    +"the tight hole created by the encroaching walls "
    +"of the mountains. All you can "
    +"see is a dim light outlining the hole above you. \n");

    add_item(({"walls"}),
    "The narrow space between the mountains surrounding "
    +"you leave only their walls "
    +"visible to you, creating the sense of being in a hole.\n");

    add_item(({"rocks"}),
    "The walls of the mountains are formed of earth "
    +"and rock formed tightly together "
    +"to make up the surroundings.\n");

    add_item(({"draft"}),
    "A slight draft comes in from beyond the narrow opening in "
    +"which you are in. It "
    +"is nothing comparable to the stormy winds outside, "
    +"but still enough to make "
    +"even the heavy rope dangle.\n");


    add_exit(FIREKNIVES_ROOMS_DIR + "o10", "up");
    add_exit(FIREKNIVES_ROOMS_DIR + "rope5", "down");


    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

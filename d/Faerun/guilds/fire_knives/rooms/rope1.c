/* /d/Faerun/guilds/fire_knives/rooms/rope1.c
 *
 * Climbing the rope, step 1.
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

    set_short("Climbing upwards on the rope");
    
    set_long("All around you the massive walls of mountains "
    +"protect you from the "
    +"wind and snow. Amidst the encroached narrow "
    +"space in between the rocks' "
    +"security reigns a silence complete, broken "
    +"only by your own respiration as "
    +"you continue climbing.\n");

    add_item(({"rope"}),
    "You are hanging from the rope that extends from "
    +"the top of the hole to the "
    +"floor below. You could climb up or down on it. \n");

    add_item(({"sky"}),
    "The sky cannot be seen from here, obscured from "
    +"view by the narrow passage up "
    +"the tight hole created by the encroaching "
    +"walls of the mountains.\n");

    add_item(({"walls"}),
    "The narrow space between the mountains surrounding "
    +"you leave only their walls "
    +"visible to you, creating the sense of "
    +"being in a hole.\n");

    add_item(({"footsteps"}),
    "Footsteps are printed with patches of snow "
    +"on the ground, proof that someone "
    +"has frequently been here before.\n");

    add_item(({"rocks"}),
    "The walls of the mountains are formed of "
    +"earth and rock formed tightly together "
    +"to make up the surroundings.\n");

    add_item(({"draft"}),
    "A slight draft comes in from beyond the "
    +"narrow opening in which you are in. It "
    +"is nothing comparable to the stormy winds "
    +"outside, but still enough to make "
    +"even the heavy rope dangle.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "rope2", "up");
    add_exit(FIREKNIVES_ROOMS_DIR + "rope_bottom", "down");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

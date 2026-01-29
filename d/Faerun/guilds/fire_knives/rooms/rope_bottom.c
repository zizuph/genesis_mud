/* /d/Faerun/guilds/fire_knives/rooms/full-members-entrance.c
 *
 * At the foot of the mountain, west past the hidden exit for full members.
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

    set_short("Tightly between the mountains");
    
    set_long("All around you the massive walls of "
    +"mountains protect you from the "
    +"wind and snow, although patches of it "
    +"can be found on the floor from the "
    +"footsteps that have brought it in. Amidst "
    +"the encroached narrow space in "
    +"between the rocks' security reigns a silence "
    +"complete, broken only by the "
    +"swishing sounds of the thick rope which "
    +"has fallin from above and now dangles "
    +"from the center, brushed back and forth "
    +"by the a draft.\n");

    add_item(({"rope"}),
    "The rope hangs from above and dangles in the "
    +"center between the walls. It would "
    +"be possible to climb up it and reach wherever it is hanging from. \n");

    add_item(({"snow", "snowdrift","snowflakes", "flakes","flake",
    "layer","layers","patch","patches"}),
    "Patches of snow are found on the ground between "
    +"the walls, brought in by the "
    +"footsteps coming in and out.\n");

    add_item(({"ground","floor"}),
    "The ground seems drier than outside due to "
    +"the walls' protection, but there "
    +"are still patches of snow on it.\n");

    add_item(({"sky"}),
    "The sky cannot be seen from here, obscured "
    +"from view by the narrow passage up "
    +"the tight hole created by the encroaching "
    +"walls of the mountains.\n");

    add_item(({"walls"}),
    "The narrow space between the mountains surrounding "
    +"you leave only their walls "
    +"visible to you, creating the sense of being in a hole.\n");

    add_item(({"footsteps"}),
    "Footsteps are printed with patches of snow on "
    +"the ground, proof that someone "
    +"has frequently been here before.\n");

    add_item(({"rocks"}),
    "The walls of the mountains are formed of earth "
    +"and rock formed tightly together "
    +"to make up the surroundings.\n");

    add_item(({"draft"}),
    "A slight draft comes in from beyond the narrow "
    +"opening in which you are in. It "
    +"is nothing comparable to the stormy winds "
    +"outside, but still enough to make "
    +"even the heavy rope dangle.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "rope1", "up");
    add_exit(FIREKNIVES_ROOMS_DIR + "mountain_ft_member", "west");


    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
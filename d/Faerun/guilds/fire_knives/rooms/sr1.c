/* /d/Faerun/guilds/fire_knives/rooms/sr1.c
 *
 * Starting Room for trainees.
 * 
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

    set_short("Inside well-kept barracks");
    
    set_long("The capacious area's walls have been reinforced with "
    +"thick planks of "
    +"wood to provide warmth and silence. Overarching structures "
    +"throughout the room "
    +"line up thickly-framed square beds, between which are wide and "
    +"round poles that "
    +"serve to hang individual lanterns. The wooden floor is carpeted "
    +"to avoid the "
    +"sound of steps upon it, while the high ceiling has been covered "
    +"as well with "
    +"drooping curtains that absorb any echoes. In front of each square "
    +"is an oblong "
    +"chest for any belongings, each one lined perfectly with the "
    +"rest as if they "
    +"were attached to the floor. \n");
    
    add_item(({"walls","wall"}),
    "The walls have been reinforced with thick planks of wood, providing "
    +"warmth "
    +"from the otherwise cold stone, while also helping to deafen "
    +"the sound that "
    +"would otherwise echo off of them.\n");

    add_item(({"planks","wooden planks","planks of wood"}),
    "The planks have been perfectly lined up and embedded against "
    +"the evenly cut "
    +"stone in the wall, covering it completely.\n");

    add_item(({"structure", "wooden structures","structures"}),
    "The wooden structure throughout the chambers "
    +"line up the thickly-framed square "
    +"beds. They also provide support for a second "
    +"floor within the room should "
    +"there ever be need for it.\n");

    add_item(({"bed","beds","square beds","square bed"}),
    "The beds look comfortable although slim and "
    +"narrow. Supported by four poles "
    +"for the ceiling above it, they can be closed "
    +"off from the rest of the room "
    +"by hanging curtains from each side.\n");

    add_item(({"chest","chests","oblong chests","oblong chest"}),
    "Each one of the beds has in front of it a "
    +"chest with a lock. It seems massive "
    +"and heavy, as if it belonged to the floor "
    +"rather than having been placed at its "
    +"location by human means. It serves to store your possessions.\n");

    add_item(({"ceiling","high ceiling"}),
    "The high ceiling is cut short by a cover of "
    +"drooping curtains hanging from the "
    +"walls that aim to reach it, sealing off "
    +"what lies beyond to render the chamber "
    +"free from possible echoes while providing a sense of comfort.\n");

    add_item(({"curtains","curtain"}),
    "The drooping curtains from the ceiling are of a "
    +"velvet hue, made to seem darker "
    +"by the growing absence of in the ascension towards the ceiling.\n");

    add_item(({"floor","carpets","carpet","carpeted floor"}),
    "The wooden floor is carpeted to muffle any possible "
    +"sounds of steps or otherwise. "
    +"The carpets are dark brown and seemingly thick, "
    +"engulfing your steps and absorbing "
    +"their  trails.\n");

    add_item(({"pole","poles"}),
    "Between each square bed is a wide, round pole that "
    +"is supported by the rest of the "
    +"wooden structure. From each one of them hangs a "
    +"lamp that sheds off enough light "
    +"to its immediate area without invading the rest.\n");

    add_item(({"lantern","lanterns"}),
    "The lanterns are spherical, although somewhat elongated "
    +"at the ends. Made of glass "
    +"encased in a bronze frame, they hold oil inside "
    +"which is now burning.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "o9.c", "south");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


int
do_start(string str)
{
    if (str != "here")
    {

        write("<start here>, perhaps?\n");

        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()))
    {
        this_player()->set_default_start_location(file_name(this_object()));

        write("From now on, you will awake here when entering the game.\n");

        return 1;
    }
    
    write("You are not a member of the Fire Knives!\n");
    return 1;
}


void init()
{
    ::init();

    add_action(do_start, "start");
}

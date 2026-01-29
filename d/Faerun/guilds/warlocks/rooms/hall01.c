/* /d/Faerun/guilds/warlocks/rooms/hall01.c
 *
 * Hallway in the guildhall.
 *
 * Nerull, 2018.
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

/*
 * Function name: block_nonmembers
 * Description  : Hinder players from passing through.
 */
public int
block_me()
{
    // We will rebuild the library later.
    write("An invisible magical wall of force stops you from "
    +"going in that direction! Strange!\n");

    return 1;
    
    
    if (this_player()->query_wiz_level())
    {
        return 0;
    }
    
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()) 
    || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
    || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        return 0;
    }

    write("You immediately stop in your track as a faint whisper "
    +"suddenly echoes in your mind, saying: Do you "
    +"feel you have sufficiently proven your worth to us in "
    +"order to enter the library? No? Then begone, Fool! Return "
    +"when you are truly worthy!\n");

    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("In a barren yellow-tinted claystone corridor");
    
    set_long("The plain smooth area is bathed in the strong "
    +"yellow light produced by the open dancing flame that emanates "
    +"from a tentacle-like bronze brazier embedded in the center of the "
    +"corridor. There are no other visible features here except for a "
    +"simple iron book stand containing a small leather binding standing "
    +"next to the south wall.\n");
    
    add_item(({"wall", "walls", "north wall"}),
    "The walls are smoothed over, making them plain and without any "
    +"edges or depressions.\n");
    
    add_item(({"ceiling", "roof"}),
    "The ceiling is smooth and without any imperfections. It reflects "
    +"the strong yellow light emanating from the dancing flame.\n");
    
    add_item(({"ground", "floor"}),
    "The ground is smooth and free of any dust. It is almost featureless "
    +"except for the tentacle-like bronze brazier that is embedded in "
    +"the center, and the simple iron book stand that is planted into "
    +"the ground near the south wall.\n");
    
    add_item(({"corridor"}),
    "The claystone corridor leads to other adjacent areas. You feel the "
    +"slight draft coming from other directions.\n");
    
    add_item(({"brazier", "bronze brazier", "tentacle-like bronze brazier",
    "tentacle-like brazier"}),
    "This strange brazier is embedded into the ground at the center of the "
    +"corridor. It's made of bronze and has the shape of an octopus-like "
    +"tentacle, curling towards "
    +"the smooth ceiling. On top of it, you see a dancing flame that emits "
    +"a very strong yellow light, illuminating the area with great "
    +"efficiency.\n");
    
    add_item(({"flame", "dancing flame"}),
    "The flame seems to be quite hot judging by its bright yellow "
    +"colour. It greatly illuminates the area, as if it was "
    +"magically enhanced to emit more light. It dances and curls "
    +"in the shape of an octopus tentacle. Weird.\n");
    
    add_item(({"simple iron stand", "iron stand",
    "stand", "book stand", "simple iron book stand", 
    "iron book stand"}),
    "The simple iron book stand consists of a plain iron rod stuck "
    +"in the ground near the south wall. It measures about four "
    +"feet in height and maybe "
    +"an inch in diameter. On top of the rod there is a flat iron "
    +"plate measuring about twelve inches by eight inches, and a "
    +"small leather binding is resting on top of it.\n");
    
    add_item(({"shadow", "shadows"}),
    "Shadows fill the parts of the hall in an unstable pattern, "
    +"only interrupted by the light from the sconces.\n");


    add_exit(WARLOCK_ROOMS_DIR + "library", "north", block_me);
    add_exit(WARLOCK_ROOMS_DIR + "hall02", "east");
    add_exit(WARLOCK_ROOMS_DIR + "train", "west");
    
    room_add_object(WARLOCK_OBJ_DIR + "yellow/yellow_book");

    reset_faerun_room();
}


void
do_whispers()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()) 
    || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
    || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        return;
    }
    
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("You hear strange whispers emanating "
            +"from the small leather binding when you pass by.\n");
            
            return;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("You hear strange whispers emanating "
            +"from the small leather binding when you pass by.\n");
            
            return;
        }
    }
 
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(0.5, 0.0, &do_whispers());
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
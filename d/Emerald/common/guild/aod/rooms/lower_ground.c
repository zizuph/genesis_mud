/*
 *  /d/Emerald/common/guild/aod/rooms/lower_ground.c
 *
 *  This is the area directly beneath the guild, where things connect
 *  with the rest of the domain.
 *
 *  Created May 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Emerald/std/room";


/* Prototypes */
public void        create_emerald_room();


/* 
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("on a wide path before the dark peaks of the mountains");
    set_em_long("The dark peaks of the Blackwall mountains rise sheer"
      + " and bleak before you, blocking out all view to the north."
      + " The path which runs southwest into the forest is much"
      + " wider here, growing even moreso as it travels up a steep"
      + " slope toward the peaks. There is a heavy darkness which hangs"
      + " like death over everything in that direction. A small track leads"
      + " east along the edge of the mountains.\n");

    add_item( ({ "track", "small track" }),
        "The track is strewn with filth. Whoever uses this track must"
      + " have no use for cleanliness.\n");
    add_item( ({ "filth" }),
        "Err ... yes. The things you see along the track are disgraceful"
      + " to say the least. To put it bluntly, someone is pooping a lot"
      + " here for some reason.\n");
    add_item( ({ "poop", "shit", "crap" }),
        "Yes, exactly.\n");

    add_item( ({ "forest", "wood", "woods" }),
        "To the southwest, the forest grows thickly. Here, however, it"
      + " has been all but obliterated. Trees lie twisted and mangled"
      + " upon the ground on all sides of the path.\n");
    add_item( ({ "tree", "trees" }),
        "Something has torn them apart. Something really REALLY"
      + " strong!\n");
    add_item( ({ "peak", "peaks", "dark peak", "dark peaks",
                 "dark peaks of the blackwall mountains", 
                 "dark peaks of the mountains" }),
        "They seem to glower down at you.\n");
    add_item( ({ "view", "view to the north" }),
        "There isn't much of one, unless you like staring at"
      + " walls of stone.\n");
    add_item( ({ "stone" }),
        "The walls to the north are made of it. Yep.\n");
    add_item( ({ "wall of stone", "walls of stone" }),
        "There they are, staring right back at you.\n");
    add_item( ({ "sky", "up" }),
        "Even the sky looks a bit darker here. This place is"
      + " not a friend to the followers of light.\n");
    add_item( ({ "dark", "darkness", "heavy darkness" }),
        "It is thick here.\n");
    add_item( ({ "light" }),
        "What light there is is heavily muted by the darkness.\n");
    add_item( ({ "path", "trail", "road", "wide path" }),
        "Though much narrower to the southwest where it travels"
      + " through the woods, the path here has been trodden by"
      + " seemingly gigantic feet and pounded flat and wide. To"
      + " the north it grows even wider, travelling up a steep"
      + " slope into the mountains.\n");
    add_item( ({ "footprint", "footprints", "prints" }),
        "Huge and terrifying!\n");
    add_item( ({ "slope", "steep slope" }),
        "It travels directly into the heart of the mountains.\n");
    add_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "They tower above you directly to the north. There is a"
      + " heavy darkness hanging over them.\n");
    add_item( ({ "heart of the mountain", "heart of the mountains" }),
        "There appears to be some dark force at work up there.\n");
    add_item( ({ "force", "dark force" }),
        "One can only imagine what it might be.\n");

    add_exit("middle_ground", "north");
    add_exit("/d/Emerald/common/guild/aod/rooms/grunts_entrance", "east");
    add_exit("/d/Emerald/north_shore/outpost/path1", "southwest");

    set_no_exit_msg( ({ "northeast", "northwest" }),
        "You walk a bit along the base of the mountains, but soon"
      + " return to where you were.\n");
    set_no_exit_msg( ({ "east", "southeast", "south", "west" }),
        "The woods are too dense in that direction to proceed.\n");

    add_npc(AOD_NPC_DIR + "aod_ogre", 1);
} /* create_emerald_room */

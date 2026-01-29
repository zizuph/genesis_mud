/*
 *  /d/Sparkle/guilds/new_merc/rooms/temporary_camp.c
 *
 *  This is a small room to act as a roleplaying device for some players
 *  who have need of it.
 *
 *  Created September 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <stdproperties.h>
#include "../merc_defs.h"

inherit "/d/Sparkle/area/city/rooms/delay_room";
inherit "/d/Sparkle/lib/room_tell";

/* Global Variables */
static mapping     No_exit_msg = ([]);     /* custom no-exit msgs */

/* Prototypes */
public void        create_room();
public void        set_no_exit_msg(mixed dir, string msg);


/* 
 * Function name:        create_room
 * Descrption   :        set up the room
 */
public void
create_room()
{
    set_short("on a small fortified island in the swamp");
    set_long("You stand amid some very basic fortifications that have"
      + " been set in place on what is otherwise a very wide and flat"
      + " island of solid ground in the swamp. Reeds and other types"
      + " of plant life choke the shores where the water laps quietly"
      + " at the edges of the muddy banks. A misty path leads"
      + " southeast back toward a trail.\n\n");

    add_item( ({ "fort", "fortifications", "basic fortifications",
                 "very basic fortifications",
                 "temporary fortification",
                 "fortification" }),
        "The fortifications look recently constructed, and in fact"
      + " do not look complete. A few stone walls have been built"
      + " at the four corners of the island. A fence of sharpened"
      + " poles bound together by dried grass and rope stretches"
      + " between them.\n");
    add_item( ({ "wall", "walls", "stone wall", "stone walls",
                 "few stone walls" }),
        "The walls have been built from carefully laid stones caked"
      + " with a bit of dried mud. They do not look like a permanent"
      + " solution of any kind. Perhaps they are meant to serve only"
      + " until some more robust structure can be completed.\n");
    add_item( ({ "mud", "dirt", "earth" }),
        "Well, it is a swamp here, so there is no shortage of that.\n");
    add_item( ({ "caked mud", "dried mud", "stones caked with mud",
                 "stones caked with a bit of dried mud" }),
        "A quick solution when mortar is not available in quantity.\n");
    add_item( ({ "fence", "pole", "poles", "sharpened pole",
                 "sharp pole", "sharp poles", "sharpened poles",
                 "fence of sharp poles", "fence of sharpened poles" }),
        "It wouldn't keep someone out for long if they were undisturbed"
      + " and trying to climb over. But they would certainly make the"
      + " area much more easy to defend.\n");
    add_item( ({ "swamp", "fen", "fens" }),
        "This swamp stretches out over a large area here.\n");
    add_item( ({ "island", "solid ground", "flat and wide island",
                 "island of solid ground",
                 "flat and wide island of solid ground" }),
        "This area seems to have been selected by someone who wanted"
      + " to put up a temporary fortification.\n");
    add_item( ({ "ground", "down", "floor" }),
        "The ground here is that of dirt.\n");
    add_item( ({ "up", "sky" }),
        "Thy sky is dimly lit through the mist.\n");
    add_item( ({ "mist", "fog" }),
        "Fog surrounds this island.\n");
    add_item( ({ "reed", "reeds" }),
        "They are the basic variety you often see growing in"
      + " swampy areas.\n");
    add_item( ({ "other types", "plant life",
                 "other types of plant life" }),
        "Most of the other plant life here is soggy underbrush.\n");
    add_item( ({ "underbrush", "soggy underbrush" }),
        "It is all over the place.\n");
    add_item( ({ "shore", "bank", "muddy bank", "banks",
                 "muddy banks", "shores" }),
        "The shore is fairly still. You notice a few frogs now and"
      + " then.\n");
    add_item( ({ "frog", "frogs" }),
        "Ribbit!\n");
    add_item( ({ "water" }),
        "It is dark and clouded with mud. Definitely not very"
      + " inviting.\n");
    add_item( ({ "path", "misty path" }),
        "A path leads southeast out of the fort heading back toward"
      + " the main trail.\n");
    add_item( ({ "trail", "main trail" }),
        "It is a ways off to the southeast.\n");

    add_cmd_item( ({ "water", "swamp",
                     "in water", "in swamp",
                     "into the water", "into the swamp" }),
                  ({ "swim", "dive", "enter" }),
        "This is definitely not a choice swimming location. You decide"
      + " against it.\n");

    add_exit("/d/Genesis/start/human/wild2/c_trail", "southeast");

    set_no_exit_msg( ({ "north", "northeast", "east", "south",
                        "southwest", "west", "northwest" }),
        "You wander along the outskirts of the island, but find"
      + " nothing of interest.\n");

    set_tell_time(180);

    add_tell("A few frogs croak in the distance.\n");
    add_tell("Mist drifts lazily across the island.\n");
    add_tell("You hear a muffled splash from somewhere to the west.\n");
    add_tell("A weathered dark-haired human arrives from the southwest"
      + " and walks the perimeter of the fort. He appears to make a few"
      + " repairs to the structure, and then heads back to the trail"
      + " southeast of here.\n");
    add_tell("A stillness comes suddenly over the swamp.\n");
    add_tell("A slight wind rustles the nearby reeds.\n");

    add_prop(ROOM_S_MAP_FILE, "temporary_camp.txt");
} /* create_room */


/*
 * Function name:        enter_inv
 * Description  :        we mask this to set up the room tells.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    start_room_tells(); 
} /* enter_inv */


/*
 * From: /d/Gondor/std/room.c
 *
 * Function name:       set_no_exit_msg
 * Description  :       set the custom no-exit msg for direction(s)
 * Arguments    :       mixed dir -- either a string or an array of strings;
 *                                   each string is a direction for which
 *                                   this room does not have an exit.
 *                      string msg -- the msg for these directions
 *
 * So instead of "There is no obvious exit west.", you can tell
 * players "You wander west among the trees for a bit, then return
 * to the road."
 */
public void
set_no_exit_msg(mixed dir, string msg)
{
    int         i, n;

    if ( pointerp(dir) )
    {
        for ( i = 0, n = sizeof(dir); i < n; ++i )
            No_exit_msg[dir[i]] = msg;
    }
    else if ( stringp(dir) && strlen(dir) )
    {
        No_exit_msg[dir] = msg;
    }
} /* set_no_exit_msg */


/*
 * Function name: unq_no_move
 * Description  : mask parent to do custom msgs for 'normal' but
 *                nonexistant directions.  Here, 'normal'
 *                exits are north, southeast, down, etcetera.
 * Arguments    : string str - the command line argument.
 * Returns      : int 0 - always.
 */
public int
unq_no_move(string str)
{
    string      vb = query_verb();

    if ( strlen(No_exit_msg[vb]) )         /* custom msg */
        notify_fail(No_exit_msg[vb]);
    else                                /* oh, well */
        notify_fail("There is no obvious exit "+vb+".\n");
    return 0;
} /* unq_no_move */
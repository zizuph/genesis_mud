/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/under_lake.c
 *
 *  A massive underground cavern lies far beneath the bottom of the lake
 *  of Del Rimmon. Though rock separates the water from the cave, much
 *  has trickled through cracks over the years to form a subterranean
 *  lake within this cave which surrounds the island of the Crystal
 *  Tower.
 *
 *  Copyright (c) April 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/random_noise";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public void        add_cavern_items();
public int         do_swim(string arg);
public void        init();
public int         random_noise();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("a subterranean lake deep beneath the ground");
    set_long("A subterranean lake deep beneath the ground. Vast walls"
      + " of rock rise in all directions to form the domed roof of"
      + " this massive underground place. The water in which you swim"
      + " surrounds you, spreading out to the east into the far reaches"
      + " of the cavern where very little light penetrates. The entire"
      + " area is lit by a brightly illuminated object which rises on the"
      + " rocky shore just to the west of where you are floating.\n");

    set_noise_interval(40, 30);

    add_item( ({ "wall", "walls of rock", "wall of rock", "vast walls",
                 "vast wall", "vast wall of rock",
                 "vast walls of rock" }),
        "In all directions, vast walls of rock slope gradually upward"
      + " to form a great domed ceiling above the surface of the water."
      + " Just to the west, the walls are brightly lit by an object which"
      + " rises along the shore.\n");
    add_item( ({ "down", "ground", "floor" }),
        "Beneath you here, there is only water. How deep that water"
      + " might be, or what lies beneath it, you have no idea.\n");
    add_item( ({ "light", "illumination", "bright light" }),
        "The cavern is lit by a brightly illuminated object which"
      + " rises on the rocky shore to the west.\n");
    add_item( ({ "object", "brightly illuminated object",
                 "illuminated object", "tower", "crystal tower",
                 "building" }),
        "The object appears to be a very tall building of some kind,"
      + " perhaps a tower. Bright light issues from its walls to fill"
      + " the entire cavern with illumination.\n");
    add_item( ({ "shore", "rocky shore", "west", "western shore",
                 "lakeshore", "lake shore", "shore of the lake" }),
        "Just to the west, the lake runs up against a rocky shore,"
      + " where a brightly lit object rises before vast walls of"
      + " rock.\n");

    add_cavern_items();

    add_cmd_item( ({ "northwest", "north", "northeast", "east",
                     "southeast", "south", "southwest" }),
                  ({ "swim" }),
        "You swim a ways in that direction, but soon realize that"
      + " you are just tiring yourself out, and there does not appear"
      + " to be any shore along the lake in that direction.\n");
    add_cmd_item( ({ "water", "lake", "under water", "under lake",
                     "under the water", "under the lake", "down" }),
                  ({ "dive", "swim" }),
        "You dip down beneath the surface of the water, and are greeted"
      + " with icy darkness. You soon return to the surface.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from the east, emerging from the waters of the lake.");

    add_exit(DELRIMMON_DIR + "lakeside/caves/tower_shore", "west",
             0, 5, 1);

    set_no_exit_msg( ({ "northeast", "north", "northwest" }),
        "You swim a bit to the north, and soon realize that there is"
      + " nothing to swim to in that direction, and return to where"
      + " you were.\n");
    set_no_exit_msg( ({ "east" }),
        "After a few short strokes, you realize that the lake extends"
      + " into empty darkness in that direction, and return to where you"
      + " were.\n");
    set_no_exit_msg( ({ "southwest", "south", "southeast" }),
        "You swim a bit to the south, but soon realize that there is"
      + " no obvious destination in that direction, and return to where"
      + " you began.\n");
    set_no_exit_msg( ({ "down" }),
        "You dive below the surface of the lake, and are greeted with"
      + " icy blackness. After a moment of literally no progress, you"
      + " reemerge above the water.\n");

    FIX_EUID
} /* create_del_rimmon */


/*
 * Function name:        add_cavern_items
 * Description  :        add the cavern details
 */
public void
add_cavern_items()
{
    add_item( ({ "lake", "subterranean lake", "water",
                 "underground lake", "huge lake",
                 "huge underground lake", "basin", }),
        "It appears as if, over the years, water has seeped through"
      + " cracks in the rock to slowly form this huge underground lake."
      + " Drips can be constantly heard echoing throughout the cavern,"
      + " and you can see tiny ripples along the surface of the water."
      + " Other than this, the lake is perfectly still, and you do not"
      + " hear any running water.\n");
    add_item( ({ "drip of water", "drips of water", "drip", "drips",
                 "drop of water", "drops of water", "drop", "drops",
                 "droplet of water", "droplets of water", "droplet",
                 "droplets" }),
        "Drips of water fall continuously from the great domed roof"
      + " of this cavern which, somewhat disconcertingly, must support"
      + " the very lake of Del Rimmon high above.\n");
    add_item( ({ "del rimmon", "lake of del rimmon" }),
        "Del Rimmon must be situated above the great domed roof of this"
      + " cavern. The thought is somewhat disturbing, as you can see"
      + " drips of water issuing constantly from above.\n");
    add_item( ({ "east", "far reaches", "far reaches of the cavern" }),
        "To the east, the lake spreads nearly out of sight, travelling"
      + " into the far reaches of the cavern, where the light is"
      + " extremely dim, and details scarce.\n");
    add_item( ({ "roof", "domed roof", "great roof", "great domed roof",
                 "ceiling", "domed ceiling", "great ceiling",
                 "great domed ceiling", "roof of the cavern", 
                 "cavern roof", "ceiling of the cavern",
                 "cavern ceiling", "up", "sky" }),
        "High above, vast walls of rock rise to form a great domed"
      + " roof which spreads out over the water. Drips of water fall"
      + " continuously from its high reaches to quietly disturb the"
      + " surface of the lake.\n");
    add_item( ({ "surface", "surface of the water",
                 "surface of the lake", "ripple", "ripples" }),
        "Tiny ripples move continuously about the surface of the water,"
      + " where drips of water fall from the great domed ceiling high"
      + " above.\n");
    add_item( ({ "wall", "walls of rock", "wall of rock", "vast walls",
                 "vast wall", "vast wall of rock",
                 "vast walls of rock" }),
        "In all directions, vast walls of rock slope gradually upward"
      + " to form a great domed ceiling above the surface of the"
      + " water.\n");
    add_item( ({ "here", "area", "cave", "cavern", "underground",
                 "underground area", "underground cave",
                 "underground cavern", "subterranean cave",
                 "subterranean area", "subterranean cavern" }),
        "This sheer size of this subterranean cavern is remarkable."
      + " The far reaches of the lake extend almost beyond sight to"
      + " the east.\n");
} /* add_cavern_items */


/*
 * Function name:        do_swim
 * Description  :        allow the player to swim to the west
 * Arguemnts    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_swim(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Where do you wish to swim?");
    }

    if (!parse_command(arg, ({}),
        "[to] [the] 'west' / 'shore'"))
    {
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'west' here, using"
            + " command(). Since you are a wizard, that won't work on"
            + " you. Simply type 'w'.\n");
        return 1;
    }

    this_player()->command("$west");
    return 1;
} /* do_swim */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    init_random_noise();

    add_action(do_swim, "swim");
} /* init */


/*
 * Function name: random_noise
 * Description  : the player can hear drips in the chamber
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, BSN(        ({
        "A sudden sound of water dripping breaks the silence, and you"
      + " see ripples running along the surface of the lake.",
        "The sound of dripping water echoes throughout the cavern.",
        "A droplet of water echoes through the cavern as it falls from"
      + " somewhere above.",
        })[random(3)] ) );

    return 1;
} /* random_noise */

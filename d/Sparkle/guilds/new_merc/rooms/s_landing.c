/*
 *  /d/Sparkle/guilds/new_merc/rooms/s_landing.c
 *
 *  Just at the top of the landing of the evil aligned side of the
 *  Mercenary lodge. 
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public void        init();
public int         climb_stairs(string arg);
public int         stair_msg();


/* 
 * Function name:        create_merc_room
 * Descrption   :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("on the south landing on the second floor of the lodge");
    set_long("A broad stairway descends to the first floor of the lodge"
      + " here, leading off of a landing that joins with a hallway"
      + " that travels west. A large window in the south wall overlooks"
      + " the grounds. Beside the window, a suit of armour stands"
      + " in the corner.\n\n");

    add_item( ({ "window", "large window", "window in the south wall",
                 "large window in the south wall" }),
        "Looking through the window, you get a good view of woods.\n");
    add_item( ({ "wood", "woods", "trees", "forest", "tree" }),
        "Looking out the window, you get a very good view of the"
      + " forest which borders the mercenary camp on the south side."
      + " A few guards are placed along the perimeter.\n");
    add_item( ({ "guard", "guards" }),
        "They are placed at various points along the edge of the"
      + " forest just south of the lodge. Through the window, you"
      + " are able to watch them, but there isn't much to see. They"
      + " aren't doing much other than standing there looking"
      + " stalwart.\n");
    add_item( ({ "perimeter", "perimeter of the forest", "edge",
                 "forest edge", "forest's edge", "forests edge",
                 "edge of the forest" }),
        "The edge of the forest is perhaps 50 yards south of the"
      + " lodge. Through the window, you get a good view of the"
      + " entire area.\n");
    add_item( ({ "landing", "south landing" }),
        "The landing joins with a hallway that travels to the west.\n");
    add_item( ({ "north", "north wall", "northern wall",
                 "wall to the north" }),
        "The southern wall is mainly characterized by the large window"
      + " it holds. There is also a suit of armour situated in the"
      + " corner.\n");
    add_item( ({ "east wall", "eastern wall", "east", "wall to the east" }),
        "The east wall is bare of any decorations, but there is a suit"
      + " of armour propped in the corner.\n");
    add_item( ({ "armour", "armor", "suit", "suit of armor",
                 "suit of armour" }),
        "The armour is damaged in several places, and is splattered"
      + " with dried blood. The armour has the markings of a soldier"
      + " of Gondor. One has to wonder ... is this a decoration or"
      + " a trophy?\n");
    add_item( ({ "blood", "dried blood", "bloodstains", "bloodstain",
                 "stain", "blood stains", "blood stain", "stains" }),
        "Bloodstains are all over the armour. Why would armour be"
      + " displayed like this?\n");
    add_item( ({ "hall", "hallway", "west" }),
        "A hallway travels a ways to the west leading off of this"
      + " landing.\n");
    add_item( ({ "stair", "stairs", "stairway", "broad stair", 
                 "broad stairs", "broad stairway" }),
        "The stairs are sturdy and well-travelled.\n");
    add_item( ({ "first floor", "first floor of the lodge",
                 "ground floor" }),
        "It is right at the bottom of these stairs.\n");
    add_item( ({ "second floor", "second floor of the lodge" }),
        "Imagine the ground floor, but higher. There you go.\n");
    add_item( ({ "sunlight", "sun", "light", "sun light",
                 "beam", "sun beam", "sunbeam" }),
        "The window in the south wall lets in plenty of light.\n");
    add_item( ({ "corner", "corner of the landing" }),
        "A suit of armour is propped up in the corner of the landing.\n");
    add_item( ({ "decoration" }),
        "A decoration? Covered in blood?\n");
    add_item( ({ "trophy" }),
        "Yes ... thinking about it ... why would someone prop up a"
      + " suit of armour covered with blood unless they WANTED people"
      + " to see the blood for some reason. This must be a trophy, and"
      + " whoever put it up must be no friend of Gondor.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_tell("Below, you see a Mercenary enter the lodge, pause to"
      + " wipe " + one_of_list( ({ "his", "her" }) ) + " feet, and"
      + " then disappear into the entry hall.\n");
    add_tell("Through the window, you see a guard pacing the"
      + " perimiter of camp at the edge of the forest.\n");
    add_tell("You hear a door close somewhere in the lodge.\n");
    add_tell("A bird swoops past the window outside.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("entrance", "north", stair_msg, 1, 0);
    add_exit("entrance", "down", stair_msg, 1, 1);
    add_exit("s_hallway", "west");

    set_no_exit_msg( ({ "northwest", "south", "northeast", "east",
                        "southeast", "southwest" }),
        "The walls of the lodge block your path.\n");

    setuid();
    seteuid(getuid());
} /* create_merc_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
} /* init */


/*
 * Function name:        climb_stairs
 * Description  :        let the players try to climb the stairs with
 *                       a command rather than just directional movement
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [large] 'stair' / 'stairs' / 'stairway' /"
      + " 'stairways'"))
    {
        notify_fail("Climb down the stairs, perhaps?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        notify_fail("At this point, we would try to move the player"
          + " north using command(). Since you are a wizard,"
          + " that won't work. Just type the direction command yourself,"
          + " please.\n");
        return 0;
    }

    this_player()->command("$n");
    return 1;
} /* climb_stairs */


/*
 * Function name:        stair_msg
 * Description  :        print a message to player and room when the
 *                       stairs are climbed
 * Returns      :        int 0 - always
 */
public int
stair_msg()
{
    mixed  *targets = FILTER_LIVE(all_inventory(this_object()));
    mixed  *non_seers = filter(targets, not @ this_player()->check_seen);

    write("You climb down the stairs to the ground floor.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " climbs down the"
      + " stairs to the ground floor.\n", non_seers + ({ this_player() }));

    return 0;
} /* stair_msg */
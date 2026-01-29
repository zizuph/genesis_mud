/*
 *  /d/Sparkle/guilds/new_merc/rooms/n_landing.c
 *
 *  Just at the top of the landing of the good aligned side of the
 *  Mercenary lodge. 
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
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
    set_short("on the north landing on the second floor of the lodge");
    set_long("A broad stairway descends to the first floor of the lodge"
      + " here, leading off of a landing that joins with a hallway"
      + " that travels west. A large window in the north wall overlooks"
      + " the grounds.\n\n");

    add_item( ({ "window", "large window", "window in the north wall",
                 "large window in the north wall" }),
        "Looking through the window, you get a good view of the mill.\n");
    add_item( ({ "mill", "saw mill", "sawmill", "old mill", "old sawmill",
                 "old saw mill" }),
        "From here you can see the roof of the saw mill, which isn't"
      + " well-viewed from the ground.\n");
    add_item( ({ "roof of the sawmill", "sawmill roof", "saw mill roof",
                 "roof of the saw mill", "roof of the mill",
                 "mill roof" }),
        "Ahhh ... reminicences of youth. As a child, this might"
      + " be something one would be tempted to find a way on top of,"
      + " no?\n");
    add_item( ({ "landing", "north landing" }),
        "The landing joins with a hallway that travels to the west.\n");
    add_item( ({ "north", "north wall", "northern wall",
                 "wall to the north" }),
        "The northern wall is mainly characterized by the large window"
      + " it holds.\n");
    add_item( ({ "east wall", "eastern wall", "east", "wall to the east" }),
        "The eastern wall has a stuffed badger mounted on it.\n");
    add_item( ({ "badger", "stuffed badger" }),
        "Who would bother to stuff a badger? Most unimpressive.\n");
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
    add_item( ({ "particle", "particles", "particle of dust",
                 "particles of dust", "dust" }),
        "Watching them float through the sunbeam seems to cast a spell"
      + " of laziness on you. Ah ... quiet moments.\n");
    add_item( ({ "sunlight", "sun", "light", "sun light",
                 "beam", "sun beam", "sunbeam" }),
        "The window in the north wall lets in plenty of light.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_tell("Below, you see a pair of Mercenaries pass by the stairway"
      + " on their way out of the lodge.\n");
    add_tell("Through the window, you see a few birds land on the roof"
      + " of the sawmill. After surveying the grounds for a moment,"
      + " they take flight and disappear from view.\n");
    add_tell("You faintly hear the waitress cursing at the top of"
      + " her lungs from the dining hall.\n");
    add_tell("Particles of dust float lazily through the sunlight"
      + " of the window.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("entrance", "south", stair_msg, 1, 0);
    add_exit("entrance", "down", stair_msg, 1, 1);
    add_exit("n_hallway", "west");

    set_no_exit_msg( ({ "northwest", "north", "northeast", "east",
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
          + " south using command(). Since you are a wizard,"
          + " that won't work. Just type the direction command yourself,"
          + " please.\n");
        return 0;
    }

    this_player()->command("$s");
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
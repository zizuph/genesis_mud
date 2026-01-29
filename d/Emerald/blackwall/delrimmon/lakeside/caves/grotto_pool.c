/*
 *  /d/Emerald/blackwall/lakeside/caves/grotto_pool.c
 *
 *  This grotto lies hidden beneath the Blackwall Mountains to the west
 *  of Del Rimmon in Emerald. A pool rests in the cave floor here, forming
 *  the only entrance and exit to the grotto for players.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/lib/water_effects";

#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public int         enter_pool(string arg);
public void        init();


/*
 * function name:        create_del_rimmon
 * descripiton  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("_grotto_pool");
    set_short("beside a small pool in a subterranean grotto");
    set_long("Beside a small pool in a subterranean grotto. Walls of"
           + " naturally formed rock rise to surround a small pool"
           + " of water here, whose dark depths lie deep beneath"
           + " its still and silent surface. A passageway has been"
           + " hewn in the rock to the west, and leads into some"
           + " dark chamber in that direction.\n");

    add_item( ({ "pool", "small pool", "pool of water",
                 "small pool of water" }),
        "Though only a small pool, the waters beneath the surface"
      + " look extremely deep, and descend to unknown reaches of"
      + " rock far below.\n");
    add_item( ({ "water", "waters", "surface", "surface of the pool",
                 "pool surface" }),
        "The surface of the pool is still and silent. No drops come"
      + " from above, and so it must be assumed that this pool has"
      + " collected from some unseen water source.\n");
    add_item( ({ "grotto", "subterranean grotto", "here", "area",
                 "cave" }),
        "This grotto appears to be some kind of natural opening which"
      + " has occurred by unknown forces when the cliffs were formed."
      + " Walls of rock slope upward to form a ceiling high above, and"
      + " the ground is rough and uneven underfoot.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "The roof of the grotto is formed of rock, and is very uneven"
      + " and rugged. There are no stalagmites or stalactites, which"
      + " would seem to indicate that there is no water seeping into"
      + " this place from above.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor of the grotto is composed of the rough rock which"
      + " comprises the entire cliff. It rises and falls unevenly,"
      + " surrounding a small pool at your feet. A bit to the west,"
      + " the ground levels out and looks quite even where a passageway"
      + " leads off into another chamber.\n");
    add_item( ({ "wall", "walls", "wall of rock", "walls of rock" }),
        "The walls are extremely rugged, and rise on all sides,"
      + " gradually sloping upward to come together in the form of"
      + " a roof overhead. A passageway has been carved to the west,"
      + " leading off into another chamber.\n");
    add_item( ({ "rock", "rocks", "stone", "stones", "cliff" }),
        "The rocks which make up the surroundings here are dark and"
      + " rugged. They do not look to have been carved by anything"
      + " other than nature, except where a passageway leads off to"
      + " the west.\n");
    add_item( ({ "west", "passage", "passageway", "corridor",
                 "opening" }), 
        "A passageway leads through the rock walls to the west into"
      + " what appears to be a chamber of some kind in that direction."
      + " It is quite obvious that the passageway is the result of"
      + " careful hands having hewn through the rough rock of the"
      + " grotto.\n");
    add_item( ({ "chamber", "dark chamber" }),
        "The chamber to the west is only dimly visible from here.\n");
    add_item( ({ "depth", "depths", "dark depth", "dark depths" }),
        "The depth of the pool can only be guessed at. Its bottom is"
      + " certainly beyond sight.\n");


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/grotto", "west");

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "northwest" }),
        "You bump up against the rock walls of the grotto in that"
      + " direction.\n");
} /* create_del_rimmon */


/*
 * Function name:        enter_pool
 * Description  :        if the pool is clean, allow the player to
 *                       try to swim around in its waters
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
enter_pool(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[in] [into] [the] 'water' / 'pool' / 'waters'"
      + " [of] [the] [pool]"))
    {
        return 0; /* player typed unusable syntax */
    }

    if (this_player()->query_skill(SS_SWIM) < 10)
    {
        write("You look doubtfully at the water, and think better"
            + " of it. You simply don't know how to swim well"
            + " enough to dare.\n");

        return 1;
    }

    write("You dive into the pool.\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " dives into the pool and disappears beneath the"
      + " water.\n", this_player());
    douse_flames(this_player());
    this_player()->move_living("M", 
        DELRIMMON_DIR + "lakeside/caves/pool_bottom", 1, 0);
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " arrives, plunging into the water amid a flurry of bubbles.\n",
        this_player());

    return 1;
} /* enter_pool */


/*
 * Function name: init
 * Description  : add actions for the player
 */
void
init()
{
    ::init();

    add_action(enter_pool, "swim");
    add_action(enter_pool, "dive");
    add_action(enter_pool, "enter");
} /* init */

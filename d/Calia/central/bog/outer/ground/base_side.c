// ROOM:  base_side.c

    /*  Calia Domain

    HISTORY

    [99-07-02] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OUTER\GROUND\BASE_SID.DOC].

    PURPOSE

    This is the base for ground-level rooms adjacent to the sides of the
    Sanctimonian fortress.  Climbing is only possible on the flat sides, not on
    the corners, so the ground-level rooms adjacent to the corners have a
    different baseroom.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

/*  If you change the SLIME_LIMIT, which is the maximum value for Slime_Factor,
you may also need to change the log_description function.  */

#define SLIME_LIMIT 29
#define CLIMB_FATIGUE 20

// GLOBAL VARIABLES

string This_Location;
int Slime_Effect = SLIME_LIMIT;

// FUNCTIONS

// Function:  log_description()

/*

Purpose:  provide log description, which depends upon the amount of slime that
has grown here.

Arguments:  none.

Returns:  string containing log description.

*/

string
log_description()

{

    int slime_index = Slime_Effect / 6;

    /*
     *  The following formula handles slime levels 0-24    
     */

    return "The logs look like the trunks of trees, trimmed of" +
        " all branches and expertly fitted together to make a solid" +
        " wall. " +
        ({"Although they are damp, and there appears to be" +
        " some slime in the cracks and crevices, the surface" +
        " of the logs looks as if it has recently" +
        " been scraped clean",
        "Dampness seems to permeate the logs, and you can see" +
        " patches of slime just barely visible on the surface" +
        " and collecting in the cracks and crevices",
        "Although the logs seem sound and free of rot, a thin" +
        " film of slime covers the surfaces and fills the" +
        " cracks and crevices",
        "A slippery coating of slime covers the damp logs" +
        " and fills their cracks and crevices",
        "A thick coating of slippery slime covers the logs and" +
        " fills the cracks and crevices"})[slime_index] +
        ".\n";

}

// Function:  grow_slime()

/*

Purpose:  replaces slime that has been scraped off by players.  The function
continues to call itself until the slime has been completely restored.

Arguments:  none.

Returns:  nothing.

*/

void
grow_slime()

{

    Slime_Effect += 1;

    if (Slime_Effect < SLIME_LIMIT) set_alarm(20.0, 0.0, grow_slime);

}

// Function:  scrape_slime(with_what)

/*

Purpose:  scrape the slime off the wall, making it easier to climb up.  You
need a bladed weapon to do this (W_SLASH damage type).

Arguments:  string containing "slime with" and the weapon used.

Returns:  1/0.

*/

int
scrape_slime(string with_what)

{

    object tp = this_player();
    object weapon;

    /*
     *  The combination of functions to generate the inventory is redundant, 
     *  but it ensures that any wielded weapon will be chosen before any
     *  unwielded one.    
     */

    if (parse_command(with_what, tp->query_weapon(-1) + all_inventory(tp),
        "'wall' / 'slime' 'with' %o", weapon))

    {

        if (weapon->query_dt() & W_SLASH)

        {

            if (weapon->query_wielded())

            {

                say(QCTNAME(tp) + " scrapes the slime off the" +
                    " wall with a " + weapon->short() +
                    ".\n");

                write("You scrape the slime off the wall with" +
                    " the " + weapon->short() +
                    ".\n");

                Slime_Effect = 0;
                set_alarm(20.0, 0.0, grow_slime);

            }

            else

            {

                write("You must be wielding it to scrape with it.\n");

            }

        }

        else

        {

            write("The " + weapon->short() + " is" +
                " an unsuitable tool for scraping slime." +
                " Perhaps something with a sharp blade would" +
                " do the trick.\n");

        }

        return 1;

    }

    else

    {

        notify_fail("Scrape what with what?\n");
        return 0;

    }

}

// Function:  climb_wall(string wall)

/*

Purpose:  climb a wall.

Arguments:  string containing "wall".

Returns: 1/0.

*/

int
climb_wall(string wall)

{

    object tp = this_player();

    if (!wildmatch("*wall", wall)) /*  Player did not specify what to climb. */

    {

        notify_fail("Climb what? The wall?\n");
        return 0;

    }

    if ((Slime_Effect + tp->query_encumberance_weight() * 2)
        >
        tp->query_skill(SS_CLIMB))

    {

        if (Slime_Effect > 5) write ("You can't seem to get a good" +
            " enough grip on the slimy logs to climb up the wall.\n");

        else write ("You are too heavily burdened to climb the wall.\n");

        return 1;

    }

    if (tp->query_fatigue() < CLIMB_FATIGUE)

    {

        write("You are too tired to climb the wall.\n");

        say(QCTNAME(tp) + " tries to climb the wall of" +
            " the fortress but fails.\n");

        return 1;

    }

    tell_room(this_object(),
        QCTNAME(tp) + " climbs up the wall of the fortress.\n", ({tp}));

    tp->move_living("M", BOG_OUTER_LOW + This_Location, 1);
    tp->add_fatigue(-CLIMB_FATIGUE);

    tell_room(environment(tp),
        QCTNAME(tp) + " climbs up from ground level.\n", ({tp}));

    return 1;

}

// Function:  init()

/*

Purpose:  add local commands.

Arguments:  none.

Returns: nothing.

*/

void
init()

{

    ::init();
    add_action(scrape_slime, "scrape");
    add_action(climb_wall, "climb");

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  register a player (or foreign npc) with the Sanctimonian control
room.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    ::enter_inv(ob, from);

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

}

// Function:  create_wall(location, *adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room, string array
containing the filenames of adjacent rooms.

Returns:  nothing.

*/

void
create_wall(string location, string *adjacent_rooms)

{

    string *compass = ({"north", "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest"});

    string face_direction;
    int n;

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
    if (adjacent_rooms[1]) add_exit(adjacent_rooms[1], "northeast", 0, 1);
    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
    if (adjacent_rooms[3]) add_exit(adjacent_rooms[3], "southeast", 0, 1);
    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
    if (adjacent_rooms[5]) add_exit(adjacent_rooms[5], "southwest", 0, 1);
    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);
    if (adjacent_rooms[7]) add_exit(adjacent_rooms[7], "northwest", 0, 1);

    /*
     *  There will be three adjacent compass directions for which there is no 
     *  exit.  For example, if you are standing at the south wall of the
     *  fortress, there will be no northeast, north, or northwest exit.
     *  Determine the direction the wall faces by finding the missing set of
     *  elements from the adjacent_rooms array and putting the opposite of the
     *  middle missing direction in face_direction.    
     */

    n = 0;

    while (n < 8 &&
        (adjacent_rooms[n] ||
        adjacent_rooms[(n + 1) % 8] ||
        adjacent_rooms[(n + 2) % 8]))

    {

        n += 1;

    }

    face_direction = compass[(n + 5) % 8];

    This_Location = location;

    set_short("Beside the " + face_direction + " wall of" +
        " a massive log fortress");

    set_long("You stand in the shadow of a massive log fortress." +
        " This wall faces " + face_direction + " and rises straight" +
        " up from the ground, which is moist, covered with" +
        " lush grass, and studded with bushes and broad tree" +
        " stumps. Far away from the fortress tall trees grow from" +
        " a dark, mist-enshrouded bog, every bit as forbidding as" +
        " the fortress itself.\n");

    add_item("shadow",
        "The shadow does not extend far from the wall, nor" +
        " is it dark enough to conceal you from anyone who" +
        " might be watching from the trees or the fortress.\n");

    add_item(({"bog", "mist-enshrouded bog", "trees", "tall trees"}),
        "The bog and trees surround the fortress in" +
        " every direction, separated from its walls by a circle" +
        " of ground that, judging from the stumps," +
        " has been painstakingly cleared of many large trees.\n");

    add_item(({"ground", "circle", "circle of ground", "hill", "slope"}),
        "Ground covered with lush grass and studded with many" +
        " stumps and bushes extends in every direction from the" +
        " fort, leading down to a mist-enshrouded bog about" +
        " a hundred meters from the walls.\n");

    add_item(({"stump", "stumps", "grass", "lush grass"}),
        "The stumps are broad enough to suggest that once" +
        " massive trees grew here, and the walls of the" +
        " fortress plainly tell what became of them. Between" +
        " the stumps grows lush grass, not particularly deep" +
        " but dense, soft, and moist, obviously thriving" +
        " without the stunting effect of an overshadowing forest.\n");

    add_item(({"bushes", "bush"}),
        "Bushes grow here in a variety of sizes and shapes," +
        " some only barely visible above the grass, others as tall" +
        " and wide as you.\n");

    add_item(({"wall", "walls", "solid wall", "solid walls",
        "fortress", "log fortress"}),
        "The sides of the fortress are constructed of" +
        " immense logs, tightly stacked and securely joined" +
        " together to make solid walls.\n");

    add_item(({"log", "logs", "slimy log", "slimy logs", "immense logs"}),
        "@@log_description@@");

    add_item(({"slime", "film", "patches", "cracks",
        "crevices", "crack", "crevice"}),
        "The slime is a common dull green variety that tends to" +
        " grow in damp places. It makes the surface of the" +
        " logs slippery, but if that's a problem you could" +
        " probably scrape it off with a sharp object.\n");

    /*
     *  The following exits are dummies to allow shouts from ground level to be 
     *  heard at all levels of the fortress exterior.   
     */

    add_exit(BOG_OUTER_LOW + This_Location, "u", 1, 1, 1);
    add_exit(BOG_OUTER_MIDDLE + This_Location, "u", 1, 1, 1);
    add_exit(BOG_OUTER_UPPER + This_Location, "u", 1, 1, 1);

    add_prop(ROOM_I_HIDE, -1);  /*  Impossible to hide. */
    add_prop(ROOM_I_LIGHT, 2);  /*  Partial shade. */

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}

/*
 *  /d/Emerald/telberin/dock/rmc_dock.c
 *
 *  Here, people can sail from Emerald to the Golden Isle where
 *  the Rich Men's Club is located.
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 *
 *  Revision history: Aug 2021 - Added fishing (Gorboth)
 */
#pragma strict_types

#include <stdproperties.h>
#include <time.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/telberin/dock/dockview";
inherit LIBPIER;
#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

/* prototypes */
public void        create_emerald_room();
//public string      read_sign();
public void        add_dock_stuff();


/*
 * Function nane:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("on a side pier off the main dock of Telberin");
    set_em_long("Here, a side pier extends out from the main dock of"
      + " Telberin whose timbers rise out of the lake to the east."
      + " South of here, a road travels up"
      + " the slope of a hill leading to the main gates of the city"
      + " of Telberin which rises majestically in the distance."
      + " A sign is fixed to a nearby post.\n");

    add_item( ({ "pier", "side pier", "here" }),
        "What appears to be gold dust has coated the boards of this"
      + " near the area where the ship which docks here regularly"
      + " would seem to make port.\n");
    add_item( ({ "dust", "gold dust" }),
        "It looks to have flaked off of something and stuck to the"
      + " planks.\n");
    add_item( ({ "board", "boards", "plank", "planks" }),
        "The planks of this pier are, in places, covered with"
      + " gold dust.\n");
    add_item( ({ "gold" }),
        "Gold? No ... just gold dust.\n");
    add_item( ({ "timber", "timbers" }),
        "Timmmmmmm-berrrrrrrrr!!\n");

    add_dock_stuff();

    add_prop("_live_i_can_fish", "freshwater");
    add_prop(ROOM_I_LIGHT, 9);
    add_exit("telberin_dock", "east");
    sign = clone_object(SIGN);
    sign->move(TO);
    reset_room();
    add_pier_entry(MASTER_OB(this_object()), "Telberin", "Pan-Donut Circle");    
    initialize_pier();
} /* create_emerald_room */


/*
 * Function name:        read_sign
 * Description  :        show the sign, in fun text graphics
 * Returns      :        string - the sign text
public string
read_sign()
{
    string desc;

    desc = "\n\n"
     + "          _____________________________\n"
     + "        .'                             `.\n"
     + "        |    Line to the Golden Isle    |\n"
     + "        |    Transferred  to Sparkle    |\n"
     + "        `._____________________________.'\n\n";

    return desc;
} read_sign */


/*
 * Function name:        add_dock_stuff
 * Description  :        To conserve filespace, we'll make this function
 *                       available so other rooms can use it too.
 */
public void
add_dock_stuff()
{
    add_item( ({ "cargo", "barrel", "barrels", "crate", "crates",
                 "crates and barrels", "barrels and crates" }),
        "Barrels and crates make their way off the ships onto the"
      + " docks where they sit in rows waiting to be loaded and"
      + " taken into the city.\n");
    add_item( ({ "dock", "docks", "dock of telberin",
                 "docks of telberin", "telberin dock", "telberin docks",
                 "main dock", "main docks" }),
        "These docks look well constructed, and stand tall above the"
      + " waters of the lake. A number of ships are moored along"
      + " the length of the dock, where occasionally elves move to"
      + " and fro loading or unloading cargo. Where the docks"
      + " meet the mainland, a road runs south up a hill. North of"
      + " the main dock, a pier runs out into the waters of the"
      + " lake.\n");
    add_item( ({ "shore", "shores", "lakeshore", "shores of the lake",
                 "shore of the lake" }),
        "The shores of the lake travel around the island south and"
      + " east of here until they are lost from view due to the"
      + " contour of their path.\n");
    add_item( ({ "island" }),
        "The island which extends in all directions to the south,"
      + " though very large, is covered almost completely by the"
      + " city of Telberin, whose walls wrap around the rocky"
      + " surfaces.\n");
    add_item( ({ "ship", "ships" }),
        "A few ship are moored along the dock. Some are clearly"
      + " cargo ships, while others have, perhaps, a more military"
      + " purpose.\n");
    add_item( ({ "road", "hill", "hillside", "slope", "south" }),
        "South of here, a road travels up the slope of a hill"
      + " toward the main gates of Telberin which lie at its"
      + " top.\n");
    add_item( ({ "gate", "gates", "main gate", "main gates",
                 "main gates of telberin", "gates of telberin",
                 "main gate of telberin", "gate of telberin" }),
        "The gates of Telberin are visible in the distance at"
      + " the top of a hill. From here, you can not make out"
      + " much detail.\n");
    add_item( ({ "telberin", "city", "city of telberin",
                 "telberin city" }),
        "Telberin, fairest jewel of all Emerald, rises majestically"
      + " from the shores of the lake, crowning the rocky slopes of"
      + " the island with its pearlescent towers and spires. Despite"
      + " the damage that certain portions of the city seem to have"
      + " sustained, there is no mistake - this is a major capitol"
      + " of great influence and wealth.\n");
    add_item( ({ "tower", "towers", "spire", "spires",
                 "pearlescent tower", "pearlescent towers",
                 "pearlescent towers and spires" }),
        "The city is a wonder to behold. The eye is drawn up along"
      + " the length of miracle pillars and spires which seem to"
      + " reach impossibly into the sky.\n");
    add_item( ({ "damage", "broken towers", "broken tower",
                 "burned building", "burned buildings" }),
        "Telberin seems to have suffered some form of calamity"
      + " recently. Large sections of the city are filled with"
      + " burned buildings and broken towers, almost as if a"
      + " terrible fire, or successful raid had occurred.\n");
    add_item( ({ "pier", "small pier", "north" }),
        "A small pier runs off from the main dock into the lake"
      + " to the north.\n");
    add_item( ({ "lake", "lake telberin", "telberin lake",
                 "water", "waters", "waters of the lake" }),
        "Lake Telberin surrounds this island in all directions,"
      + " its crystal form dazzlingly beautiful in the bright"
      + " light. A bridge spans the waters to the west, travelling"
      + " over the lake to the mainland.\n");
    add_item( ({ "mainland", "mainland of Emerald" }),
        "The mainland of Emerald is not too far to the west, over"
      + " the narrow body of the lake which runs between it and"
      + " this island.\n");
    add_item( ({ "bridge", "large bridge", "burned bridge" }),
        "A bridge connects this island to the mainland to the"
      + " west, crossing over the waters of the lake. It appears"
      + " to have been burned and partially destroyed. Its entire"
      + " middle section is missing, and it is completely"
      + " abandoned.\n");
    add_item( ({ "sky", "up", "cloud", "clouds",
                 "billowing cloud", "billowing clouds" }),
        "The sky above is filled with billowing clouds which"
      + " slowly drift over the city.\n");
    add_item( ({ "down", "ground", "floor" }),
        "The dock is firmly grounded beneath your feet.\n");

    add_prop(ROOM_I_LIGHT, 9);
} /* add_dock_stuff */


object
query_sign ()
{
  return sign;
}

/*
 * Function name:        do_dive
 * Description  :        allow the player to try to dive off the pier,
 *                       but inform him/her that that won't be possible
 * Arguments    :        string arg - what the player typed
 * Return       :        int 1 - success, 0 - failure
 */
public int
do_dive(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[off] [in] [to] [into] [the] 'lake' / 'water' / 'pier'"
      + " [telberin]"))
    {
        return 0; /* couldn't parse the player syntax */
    }

    write("Just as you are about to dive in, you notice that there"
      + " is no ladder by which you could climb back up. It would"
      + " be a long and unpleasant swim back to shore, so you"
      + " step back again.\n");
    return 1;
} /* do_dive */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_dive, "swim");
    add_action(do_dive, "dive");
} /* init */

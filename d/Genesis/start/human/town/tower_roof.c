/*
 *  /d/Genesis/start/human/town/tower_roof.c
 *
 *  This is the roof of the Genesis ShipLines Office where a Roc comes and
 *  lands to dump people off from the Athas Domain.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
inherit STDPIER;
/* Prototypes */
public void        create_room();
//public string      exa_sign();
public int         climb_stairs(string arg);
public void        init();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
  ::create_pier();
    set_short("a wide flat roof atop a building somewhere in"
      + " Sparkle");
    set_long("You stand atop a wide flat roof high above the"
      + " docks of Sparkle. The top of this building has been"
      + " put to use as a roost for some enormous creature, it"
      + " would seem. A massive nest is completely fills one"
      + " side of the roof. A sign is just beside the nest. A"
      + " stairway leads down from the roof into the building.\n\n");

    add_item( ({ "roof", "wide roof", "wide flat roof", "flat roof",
                 "here", "area", "top", "top of the building",
                 "top of this building" }),
        "The roof appears to be some kind of landing area.\n");
    add_item( ({ "landing area" }),
        "Boy ... from the looks of it, the creature that lands here"
      + " must be enormous!\n");
    add_item( ({ "sparkle", "city", "sparkle city", "town of sparkle",
                 "sparkle town", "city of sparkle" }),
        "Sparkle spreads out beneath this rooftop. You really are"
      + " quite high up.\n");
    add_item( ({ "dock", "docks", "docks of sparkle", "sparkle docks" }),
        "You can't see any real detail ... you are too high up.\n");
    add_item( ({ "roost" }),
        "The creature that roosts here must be truly epic in"
      + " size. I mean ... just look at that nest!\n");
    add_item( ({ "nest", "massive nest", "big nest", "huge nest",
                 "roc nest" }),
        "The nest is comprised of small fir trees which have been"
      + " uprooted, laid in a circular clump, and then sat on many"
      + " times by something's titanic haunches. Most unsettling!\n");
    add_item( ({ "tree", "trees", "fir tree", "fir trees" }),
        "They have seen better days, to be sure.\n");
    add_item( ({ "side", "side of the roof", "one side",
                 "one side of the roof" }),
        "The nest pretty much takes up the whole thing.\n");
    //add_item( ({ "sign" }), exa_sign);
    add_item( ({ "stairway", "stair", "stairs", "stair way",
                 "steps", "staircase" }),
        "The stairs disappear out of sight into the building.\n");
    add_item( ({ "building" }),
        "You can't see much of the building from up here.\n");
    add_item( ({ "sky", "up" }),
        "The sky is clear and bright overhead.\n");
    add_item( ({ "sun", "sunlight" }),
        "The sun shines brightly up here.\n");
    add_item( ({ "cloud", "clouds" }),
        "Not too many of them today. Its quite beautiful.\n");
    add_item( ({ "down", "ground", "floor" }),
        "The roof is flat and paved with stones.\n");
    add_item( ({ "stone", "stones" }),
        "They are carefully fitted together to make the surface of"
      + " the roof.\n");
    add_item( ({ "surface", "surface of the roof" }),
        "Yes ... yes it is. A surface. Nice.\n");
    add_item( ({ "clump", "circular clump" }),
        "It's probably where the monster's butt goes.\n");

    //    add_cmd_item( ({ "sign", "the sign" }),
    //                  ({ "read" }), exa_sign);


    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit("/d/Sparkle/area/city/shiplines/office/entrance", "down");
  add_pier_entry(MASTER_OB(TO), "Sparkle", "Roc to Tyr");
  initialize_pier();
} /* create_room */


/*
 * Function name:        exa_sign
 * Description  :        print the text when the sign is
 *                       examined or read
 * Returns      :        string - the description to see
public string
exa_sign()
{
    return ""
  + "                       _____\n"
  + "                      |     |`.\n"
  + " _____________________|_____|_|___________________\n"
  + "|                                                 `.\n"
  + "|              Passage to Athas                   | |\n"
  + "|                                                 | |\n"
  + "|           Price: XX silver coins                | |\n"
  + "|                                                 | |\n"
  + "| Warning! The City of Sparkle is not responsible | |\n"
  + "| for loss of life or limb encountered while      | |\n"
  + "| making use of this very UN-official mode of     | |\n"
  + "| transport. The lands of the Dark Sun are not    | |\n"
  + "| for the faint of heart!                         | |\n"
  + "|_________________________________________________| |\n"
  + "`.________________________________________________`.|\n"
  + "                      |     | |\n"
  + "                      |     | |\n\n";
} exa_sign */



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
          + " down using command(). Since you are a wizard,"
          + " that won't work. Just type the direction command yourself,"
          + " please.\n");
        return 0;
    }

    this_player()->command("$d");
    return 1;
} /* climb_stairs */


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

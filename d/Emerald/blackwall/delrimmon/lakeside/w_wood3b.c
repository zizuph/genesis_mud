/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood3b.c
 *
 *  This area of forest is westernmost in a direct line from the
 *  midpoint of Del Rimmon in the Blackwall Mountains. There is
 *  a large hollow stump here.
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";

#include <macros.h>    /* for CAP() */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Definitions
 */
#define  OUR_STUMP    (DELRIMMON_DIR + "lakeside/hollow_stump")

/* prototypes */
void               create_tree_room();
public void        add_forest_herbs();
public string      describe();
public string      maeltars_finger();


/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("west");
    set_show_area_desc();

    set_extraline(describe);

    add_item( ({ "shadow", "large shadow", "point" }), maeltars_finger);
    add_item( ({"stump", "tree stump", "tall stump", "hollow stump",
                "hollow tree stump", "tall tree stump",
                "tall hollow tree stump"}), BSN(
        "Rising from a thick patch of bushes, the base of this"
      + " massive tree stump must be at least six feet in diameter."
      + " It has been hollowed out by years of rot and decay,"
      + " and a large crack runs from the top of the trunk to"
      + " its base."));
    add_item( ({"crack", "large crack", "crack in the stump",
                "crack in the tree stump"}), BSN(
        "Peering into the crack, you see nothing but blackness."));
    add_item( ({"base", "base of the stump"}), BSN(
        "The base of the stump is partially concealed by bushes and"
      + " undergrowth."));
    add_item( ({"top", "top of the trunk"}), BSN(
        "The top of the trunk is perhaps eight feet from the ground"
      + " here, except where it dips some, broken by a large crack"
      + " which runs clear to the base."));
    add_item( ({"patch", "thick patch", "patch of bushes",
                "thick patch of bushes", "bush", "bushes"}), BSN(
        "A thick patch of bushes clusters here at the base of a"
      + " large tree trunk which rises from the ground."));
    add_item( ({"borders", "borders of the lake"}), BSN(
        "The borders of the lake are not visible here, but clearly"
      + " they lie not far to the east."));
    add_item( ({"blackness"}), BSN(
        "The contents of the stump are quite shouded by deep"
      + " shadows which no light from the outside is able to reach."));
    add_item( ({"shadow", "shadows", "deep shadow", "deep shadows"}),
    BSN("The shadows within the stump are completely black, revealing"
      + " nothing from this vantage point."));

    add_cmd_item( ({"stump", "tree stump", "tall stump", "hollow stump",
                    "hollow tree stump", "tall tree stump",
                    "tall hollow tree stump"}),
                  ({"search"}), BSN(
        "Poking around the stump, you discover that it is indeed"
      + " quite massive, and that the hollow within would probably"
      + " provide room enough for three at least."));
    add_cmd_item( ({"crack", "large crack", "crack in the stump",
                    "crack in the tree stump"}),
                  ({"search"}), BSN(
        "Examining the crack more closely, you notice that it"
      + " widens to just over a foot about three feet from the"
      + " base."));

    add_exit(DELRIMMON_DIR + "lakeside/w_wood4b","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4", "northeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood2b","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff2", "southwest",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff3","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff4", "northwest",
             check_sitting,1,1);
} /* create_tree_room */

/*
 * Function name:        add_forest_herbs
 * Description  :        redefine the function, so we can add special
 *                       herb to this room
 */
public void
add_forest_herbs()
{
    set_up_herbs( ({ "/d/Emerald/herbs/darkroot",
                     "/d/Emerald/herbs/darkroot",
                     "/d/Emerald/herbs/darkroot" }),
                          ({ "ground", "bush", "tree",
                             "undergrowth", "trees", "forest",
                             "shrub", "shrubs", "bushes",
                             "roots", "root", "stump" }),
                  3 );
} /* add_forest_herbs */


/*
 * Function name: enter_crack
 * Description  : allows mortals to try and enter the stump
 * Arguments    : str - what the player tried it on
 * Returns      : 1 - success, 0 - failure
 */
int
enter_crack(string str)
{
    string  vb = query_verb();

    if (!strlen(str))
    {
        NFN0(CAP(vb) + " what?");
    }

    if (!parse_command(str, ({}),
        "[in] [into] [the] [tall] [massive] [hollow] [tree] [large]"
      + " 'stump' / 'crack' [of] [the] [tall] [massive] [hollow]"
      + " [tree] [stump]"))
    {
        NFN0("What do you wish to " + vb + "?");
    }

    WRITE("You manage to squeeze through the crack into the hollow"
        + " of the tree stump.");
    SAY(" squeezes through a narrow crack into the dark hollow"
      + " of a nearby tree stump.");
    TP->move_living("M", OUR_STUMP);
    SAY(" arrives, squeezing through the narrow crack in the stump.");

    return 1;
} /* enter_crack */

/*
 * Funciton name: init
 * Description  : add actions for the player
 */
void
init()
{
    ::init();

    add_action(enter_crack, "enter");
    add_action(enter_crack, "climb");
} /* init */


/*
 * Function name:        describe
 * Description  :        provide a description for the room.
 * Returns      :        string - the room description
 */
public string
describe()
{
    string txt = "The forest appears to have reached its westernmost"
               + " point here as it traces the borders of the lake"
               + " running north to south. A tall hollow tree stump"
               + " rises from the bushes nearby.";

    if (!query_beacon())
    {
        return txt;
    }

    if (MANAGER->query_door_location(this_player()) == STUMP)
    {
        txt += " A large shadow extends into the area here, its point"
             + " ending directly over the stump.";
    }

    return txt;
} /* describe */


/*
 * Function name:        maeltars_finger
 * Description  :        provide a description for the shadow
 * Returns      :        string - the description
 */
public string
maeltars_finger()
{
    if (!query_beacon())
    {
        return "You find no " + Exa_arg + ".\n";
    }

    if (MANAGER->query_door_location(this_player()) != STUMP)
    {
        return "The shadows which are cast by the brilliant illumination"
             + " all point west northwest, as if the source of the light"
             + " were coming from the southeastern end of the lake.\n";
    }

    return "The shadow extends into the area like a vast finger. It"
         + " is pointing directly at the stump.\n";
} /* maeltars_finger */

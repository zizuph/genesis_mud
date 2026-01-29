/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/w_wood4b.c
 *
 *  This area of the forest is near to the westernmost cliffs which
 *  ring the lake of Del Rimmon in the Blackwall Mountains. Some
 *  marauding orc has left his dagger stuck in a nearby tree.
 *
 *  Copyright (c) May 12 1998, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
 * Global Variables
 */
public int    Dagger = 1;   /* True if dagger is stuck in tree */

public void  set_dagger(int i) { Dagger = i; }
public int   query_dagger() { return Dagger; }

/*
 * Prototypes
 */
public mixed   dagger_cmd_item();
public mixed   exa_hilt();
public string  exa_dagger();
public string  exa_trunk();
public string  room_describe();
public int     get_dagger(string str);
public void    init();
public void    reset_room();

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with master presets
 */
void
create_tree_room()
{
    set_loc(2);
    set_side("west");

    set_extraline(room_describe);

    add_item( ({"ridge", "ridges"}), BSN(
        "Somewhat to the north, a ridge rises steeply from the slope"
      + " of the hillside, breaking the gradual climb from the lake"
      + " with its more extreme embankment."));
    add_item( ({"embankment", "extreme embankment"}), BSN(
        "The ridge to the north looks as if it would require a"
      + " difficult climb to navigate."));
    add_item( ({"weapon", "dagger", "knife"}), exa_dagger);
    add_item( ({"tree", "nearby tree", "trunk"}), exa_trunk);
    add_item( ({"hilt", "dagger hilt", "hilt of the dagger"}),
             exa_hilt);

    add_cmd_item( ({"tree", "weapon", "dagger", "knife"}),
                  ({"search"}), dagger_cmd_item);

    add_exit(DELRIMMON_DIR + "lakeside/w_wood5b", "north",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood5", "northeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood4", "east",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3", "southeast",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_wood3b", "south",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff3", "southwest",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff4", "west",
             check_sitting, 1, 1);
    add_exit(DELRIMMON_DIR + "lakeside/w_cliff5", "northwest",
             check_sitting, 1, 1);
} /* create_tree_room */

/*
 * Function name: room_describe
 * Description  : alters the room description based on global vars
 * Arguments    : none
 * Returns      : room description (string)
 */
public string
room_describe()
{
    string rtxt = "The slope steepens to the north, where a ridge"
               + " rises abruptly to face the lake shore.";

    if (Dagger)
    {
        rtxt += " A dagger of some kind has been stabbed into"
              + " the trunk of a nearby tree.";
    }

    return rtxt;
} /* room_describe */

/*
 * Function name: dagger_cmd_item
 * Description  : gives a desc based on global var Dagger
 * Returns      : description of the dagger (if Dagger is true)
 */
public mixed
dagger_cmd_item()
{
    if (Dagger)
    {
        return BSN("It seems as if the dagger has been stabbed"
                 + " deeply into the trunk of the tree. It is"
                 + " probably not embedded too deeply to pull"
                 + " out, however.");
    }

    return 0;
} /* dagger_cmd_item */

/*
 * Function name: exa_trunk
 * Description  : gives a desc based on the global var Dagger
 * Returns      : description of the tree trunk
 */
public string
exa_trunk()
{
    string ttxt = "This tree grows quite nearby with a few low branches"
                + " extending from its base.";

    if (Dagger)
    {
        ttxt += " A dagger has been plunged deeply into the trunk"
              + " of the tree.";
    }

    return BSN(ttxt);
} /* exa_trunk */

/*
 * Function name: exa_dagger
 * Description  : gives a desc based on the global var Dagger
 * Returns      : description of the dagger (if Dagger is true)
 */
public mixed
exa_dagger()
{
    if (Dagger)
    {
        return BSN("The dagger is plunged deeply into the trunk of"
                 + " a nearby tree, so that only the hilt is visible"
                 + " protruding from the surface.");
    }

    return 0;
} /* exa_dagger */

/*
 * Function name: exa_hilt
 * Description  : gives a desc based on the global var Dagger
 * Returns      : description of the dagger hilt (if Dagger is true)
 */
public mixed
exa_hilt()
{
    if (Dagger)
    {
        return BSN("The hilt of the dagger is all that can be seen of"
                 + " the weapon, which is clearly buried deep in the"
                 + " trunk of the tree.");
    }

    return 0;
} /* exa_hilt */

/*
 * Function name: get_dagger
 * Description  : allows a player to get the dagger from the tree
 * Arguments    : str - what the player typed
 * Returns      : 1 - success, 0 - failed
 */
public int
get_dagger(string str)
{
    object  dweapon;

    if (!strlen(str))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    if (!Dagger)
    {
        return 0;
    }

    if (!parse_command(str, ({ }),
    "[out] [the] 'dagger' / 'knife' / 'weapon' [from] [the] [tree]"))
    {
        NFN0("What do you wish to " +query_verb()+ " from where?");
    }

    WRITE("You pull the dagger from the trunk of the tree.");
    SAY(" pulls the dagger out of the tree trunk.");

    FIX_EUID

    dweapon = clone_object(DELRIMMON_DIR + "obj/wep/dagger")->move(TP);
    Dagger = 0;
    set_show_area_desc();  /* Make the room desc longer now */

    return 1;
} /* get_dagger */

/*
 * Function name: init
 * Description  : add actions to the player
 */
void
init()
{
    ::init();

    add_action(get_dagger, "get");
    add_action(get_dagger, "pull");
} /* init */


/*
 * Function name:        reset_room
 * Description  :        make sure the knife reappears on resets
 */
public void
reset_room()
{
    tell_room(TO, "A dagger suddenly flies through the trees, and lands"
                + " with a thunk in the bark of a nearby trunk. You hear"
                + " some cruel laughter from the northwest.\n");
    Dagger = 1;
} /* reset_room */

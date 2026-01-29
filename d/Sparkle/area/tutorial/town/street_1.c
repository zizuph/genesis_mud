/*
 *  /d/Sparkle/area/tutorial/town/street_1.c
 *
 *  A road at the southern end of Greenhollow. This room
 *  gives the player advice on what to do first off.
 *
 *  Created June 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    15  /* the chapter for the sign */

/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("in southern Greenhollow near the Adventurer's Guild");
    set_long("A dirt road travels through the southern end of a small"
      + " village here, making its way through town east and west of"
      + " here. This is Greenhollow, perhaps one of the most friendly"
      + " and helpful places in all of Genesis. A sense of well-being"
      + " positively springs from every corner of this serene little"
      + " town. To the south, the road winds toward a distant"
      + " hilltop. Directly to the north, a tall red building"
      + " attracts your attention.\n\n");

    add_road_items();
    add_outdoor_items();
    add_town_items();

    add_item( ({ "red building", "tall building", "tall red building",
                 "north", "guild", "adventurer guild",
                 "adventurers guild", "adventurer's guild" }),
        "North of the road, a tall red building gleams in the bright"
      + " sunlight. A banner hangs above the door. You may"
      + " <exa banner> or <read banner> for more information.\n");
    add_item( ({ "grass", "green grass", "grasses", "green grasses" }),
        "Grass grows green and brilliant to the south beneath and"
      + " along the slopes of a distant hilltop.\n");
    add_item( ({ "hill", "base", "base of a hill", "hill base",
                 "base of the hill", "slope", "slopes", "green slope",
                 "green slopes", "horizon", "south", "hilltop",
                 "distant hilltop" }),
        "A ways to the south, a hill rises up to meet with the blue sky."
      + " Its green slopes are a pleasant sight against the horizon.\n");

    add_cmd_item( ({ "banner", "at banner" }),
                  ({ "read", "exa", "look", "examine" }),
        "The banner reads: 'The Adventurers Guild'\n");

    prevent_attacks();
    reset_room();

    add_exit("street_2", "west");
    add_exit("adv_guild", "north");
    add_exit("street_3", "east");
    add_exit("road_1", "south");
} /* create_silverdell */




/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("A hint, sure ... the sign here gives you a good idea of"
      + " what you should be focusing on to get started. Go north"
      + " into the adventurers guild and spend your money on a few"
      + " combat skills to get started. Then, explore the town, and"
      + " keep reading signs.\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */



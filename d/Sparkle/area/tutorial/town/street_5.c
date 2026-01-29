/*
 *  /d/Sparkle/area/tutorial/town/street_5.c
 *
 *  This road heads through northern Greenhollow. This
 *  room teaches about roleplay and emotions.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    27  /* the chapter for the sign */


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
    set_short("in northern Greenhollow between the Town Hall and Mayor");
    set_long("You are on a road in northern Greenhollow. Here, the road"
      + " passes north out of town, travelling into a grove of trees."
      + " West of the road is the house of the Mayor, who is always"
      + " worth visiting. The Town Hall rises east of the road. To the"
      + " south, the road travels into town.\n\n");

    add_road_items();
    add_outdoor_items();
    add_town_items();

    add_item( ({ "northern greenhollow", "north greenhollow" }),
        "Northern Greenhollow contains many of the most important"
      + " buildings in town.\n");
    add_item( ({ "tree", "trees", "grove", "grove of trees", "north" }),
        "North, the road passes out of town, heading into a grove of"
      + " trees that is visible in the distance.\n");
    add_item( ({ "west", "mayor", "house", "house of the mayor",
                 "mayor house", "mayors house", "mayor's house",
                 "home", "home of the mayor" }),
        "The mayor's house looks very elegant indeed. If you have not"
      + " yet paid him a visit, he is worth talking to. He can give"
      + " you a few quests!\n");
    add_item( ({ "east", "hall", "town hall" }),
        "The Town Hall is just east of the road here. Inside, there is"
      + " a bulletin board that you will be able to read.\n");

    prevent_attacks();
    reset_room();

    add_exit("street_6", "north");
    add_exit("board_room", "east");
    add_exit("street_4", "south");
    add_exit("mayors_house", "west");
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
    write("Sure, here's a hint. You should go west and see what quests"
      + " the Mayor has available. Quest experience is the best kind you"
      + " can get!\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


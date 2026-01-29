/*
 *  /d/Sparkle/area/tutorial/town/street_2.c
 *
 *  This is Greenhollow Square in the Newbie Area. This
 *  room teaches about quitting and its effects on your
 *  inventory, etcetera.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <macros.h>

/* definitions */
#define  TUTORIAL_CHAPTER    37  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public void        do_drink(string str);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("between the Library, Tavern, and Inn in southern"
      + " Greenhollow");
    set_long("The road opens onto a wide paved area here. This is"
      + " Greenhollow Square, which rests beneath a few of the more"
      + " popular establishments of town. North of here is the"
      + " Greenhollow Inn. To the west is the Library. South of here"
      + " you can hear laughter and merriment coming from the"
      + " Red Weasel - Greenhollow's famous tavern. The road leads"
      + " out of the square to the east.\n\n");

    add_road_items();
    add_outdoor_items();
    add_town_items();

    add_item( ({ "square", "greenhollow square", "area", "paved area",
                 "wide paved area", "here" }),
        "At the center of the square, a little fountain sends water"
      + " flowing into a clear basin.\n");
    add_item( ({ "fountain", "little fountain", "water", "basin",
                 "clear basin", "fish", "tall fish" }),
        "The fountain is in the shape of a tall fish shooting water"
      + " from its mouth into the air, where it falls into a clear"
      + " basin below.\n");
    add_item( ({ "establishment", "establishments",
                 "popular establishment", "popular establishments",
                 "building", "buildings" }),
        "The inn to the north and tavern to the south are some of"
      + " the most popular places in town. Though not nearly as"
      + " popular, the library is west of here.\n");
    add_item( ({ "north", "inn", "greenhollow inn", "white building",
                 "tall white building", "inn of greenhollow" }),
        "North of here stands a tall white building which is the"
      + " Greenhollow Inn. People from all over these parts are known"
      + " to spend a weary evening beneath its safe roof. It is also"
      + " known to be a fine eating establishment.\n");
    add_item( ({ "west", "library", "imposing building",
                 "greenhollow library", "library of greenhollow" }),
        "To the west, a rather imposing building looms over the square."
      + " This is the Library of Greenhollow, which contains much useful"
      + " knowledge for the information seeker.\n");
    add_item( ({ "south", "tavern", "weasel", "red weasel",
                 "red weasel tavern", "famous tavern" }),
        "The Red Weasel tavern is an excellent place to socialize and"
      + " meet up with some of the local characters. It is also said to"
      + " have the finest beer in town!\n");

    prevent_attacks();
    reset_room();

    add_exit("inn", "north");
    add_exit("street_1", "east");
    add_exit("tavern", "south");
    add_exit("library", "west");
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
    add_action(do_drink, "drink");
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
    write("A hint? Well, at this point try not to get overwhelmed by"
      + " all of the information you are learning. Take it slow, and"
      + " read as much as you feel comfortable with. When all else fails"
      + " do what feels fun!\n");

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


/*
 * Function name:        do_drink
 * Description  :        let players drink from the fountain
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[the] [water] [from] [the] 'fountain' / 'basin'"))
    {
        notify_fail("What do you wish to drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("Feeling somewhat awkward, you dip your hand"
             + " in the basin and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You seem to have drunk your fill.\n");
    }
    else
    {
        write("Feeling somewhat awkward, you dip your hand"
             + " in the basin and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the"
        + " fountain.\n");

    return 1;
} /* do_drink */

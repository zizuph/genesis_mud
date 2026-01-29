/*
 *  /d/Sparkle/area/tutorial/town/adv_guild2.c
 *
 *  The second floor of the Greenhollow Adventurer's Guild.
 *  This room teaches about skills, and leads to the
 *  training rooms.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    13  /* the chapter for the sign */


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
    set_short("the second floor of the Adventurers Guild of Greenhollow");
    set_long("Here on the second level of the Adventurer's Guild,"
      + " each wall has a separate door leading to a different"
      + " training room for the four main types of skills you"
      + " can learn in Genesis. As always, the tutorial sign"
      + " is here to explain things further.\n\n");

    add_item( ({ "second level", "second floor" }),
        "This second floor of the guild seems devoted to skill"
      + " training.\n");
    add_item( ({ "door", "doors", "doorway", "doorways",
                 "wall", "walls" }),
        "Which wall do you wish to examine? North, south, east,"
      + " and west - each has a separate doorway leading into a"
      + " training area beyond this room. Words are written above"
      + " each door indicating the type of skill trained within.\n");
    add_item( ({ "north", "north door", "northern door",
                 "northern doorway", "north doorway",
                 "north wall", "northern wall" }),
        "Above the northern doorway, the word 'Fighting' has been"
      + " written.\n");
    add_item( ({ "south", "south door", "southern door",
                 "southern doorway", "south doorway",
                 "south wall", "southern wall" }),
        "Above the southern doorway, the word 'Magic' has been"
      + " written.\n");
    add_item( ({ "east", "east door", "eastern door",
                 "eastern doorway", "east doorway",
                 "east wall", "eastern wall" }),
        "Above the eastern doorway, the word 'General' has been"
      + " written.\n");
    add_item( ({ "west", "west door", "western door",
                 "western doorway", "west doorway",
                 "west wall", "western wall" }),
        "Above the western doorway, the word 'Thief' has been"
      + " written.\n");
    add_item( ({ "training area", "training areas" }),
        "The training areas lie beyond the doors in each of the"
      + " four walls of this room.\n");

    add_item( ({ "stair", "stairs", "stairway" }),
        "The stairs lead down to the first floor of this building. You"
      + " can use the <d>own exit to travel there.\n");
    add_item( ({ "here", "area", "guild", "adventurers guild",
                 "room", "building" }), long);

    add_cmd_item( ({ "word", "words" }),
                  ({ "read", "exa" }),
        "Above each door, words are written. 'Fighting' is to the"
      + " north, 'General' is to the east, 'Magic' is to the south,"
      + " and 'Thief' is to the west.\n");


    add_indoor_items();

    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("adv_guild3", "north");
    add_exit("adv_guild4", "east");
    add_exit("adv_guild5", "south");
    add_exit("adv_guild6", "west");
    add_exit("adv_guild", "down");
} /* create_silverdell */


/*
 * Function name:        do_climb
 * Description  :        allow players to climb the stairs
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to climb?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] 'stair' / 'stairs' / 'stairway'"))
    {
        return 0; /* let the mudlib handle it */
    }

    write("You climb back down the stairs to the ground floor.\n");
    if (this_player()->query_wiz_level())
    {
        write("Here, we normally move the player 'down' using"
          + " command(). Since you are a wizard, that won't"
          + " work. Simply move yourself <down> manually.\n");
    }

    this_player()->command("$down");
    return 1;
} /* do_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(hint, "hint");
    add_action(do_climb, "climb");
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
    write("Need a hint? No problem ... through the doors leading"
      + " from this room are various skill training areas. You can"
      + " examine each wall to see which type of skills are trained"
      + " in each room. Going <d>own will take you back to the first"
      + " floor.\n");
 
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

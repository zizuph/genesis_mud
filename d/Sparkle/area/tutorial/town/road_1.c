/*
 *  /d/Sparkle/area/tutorial/town/road_1.c
 *
 *  This room teaches about npcs and conversation commands.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 *
 *  Updated August 2015, by Bart Freeman (Tedare)
 *  Changed to allow npc Hetzel to block the north exit until
 *  new characters ask at least one quest related question.
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    10  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public int         hint(string arg);
public void        reset_room();
public int		   check_exit(string exit);
public int		   index;
/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("a dirt road at the base of a hill");
    set_long("Green grass grows thickly here at the base of a hill"
      + " which rises to the south. A dirt path runs down from the"
      + " hill and continues north toward a town, whose first"
      + " rooftops can be seen in the distance.\n\n");

    add_road_items();
    add_outdoor_items();

    add_item( ({ "grass", "green grass", "grasses", "green grasses" }),
        "Grass grows all along the hillside and spreads out beside the"
      + " path as it travels to the north.\n");
    add_item( ({ "hill", "base", "base of a hill", "hill base",
                 "base of the hill" }),
        "Just to the south, a hill rises up to meet with the blue sky,"
      + " its green grasses contrasting vividly with the open air.\n");
    add_item( ({ "town", "greenhollow", "roof", "rooftop", "roofs",
                 "rooftops", "first rooftops", "building", "buildings",
                 "town of greenhollow" }),
        "To the north, a number of buildings are visible rising over the"
      + " grass. This path leads toward the town of Greenhollow.\n");

    prevent_attacks();
    reset_room();

    add_exit("road_0", "south");
    add_exit("street_1", "north", &check_exit("street_1"), 1, 0);
} /* create_silverdell */

/*
 * Function name:        init
 * Description  :        add some commands to the player
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
    if (arg == "full")
    {
        write("Here's what you should do:\n\n"
          + "    <ask hetzel quest>\n"
          + "    <ask hetzel mayor>\n"
          + "    <ask hetzel baron>\n"
          + "Hints will not be full givaways in the game"
          + " like they were in the tutorial.\n");

        return 1;
    }

    write("Sure, here's a hint. Conversations with an intelligent"
      + " NPC are similar to looking for deeper room descriptions."
      + " So, for instance, if an NPC mentions fishing, you might"
      + " <ask npc fishing>. If he then mentions needing bait, you"
      + " might <ask npc bait> and so on. To start off with, you"
      + " can ask this fellow about the mayor. If you still need more"
      + " help, type <hint full>.\n");

    return 1;
} /* hint */

/*
 * Function name:        check_exit
 * Description  :        only allow the player to pass hetzel if
 *                       they have gotten main quest info
 * Arguments    :        string exit - which exit are we checking?
 * Returns      :        int 1 - prevent, 0 - allow
 */
public int
check_exit(string exit)
{
    if (exit == "street_1")
    {
 
		if (CHECK_TUTORIAL_BIT(BEGINNER_BIT))
		{
			return 0;
		}
		
		for (index = 0; index < 70; index++) 
		{
			if(index != 9 | index != 10 | index != 11)
			{
				if(CHECK_TUTORIAL_BIT(index))
					return 0;
			}
		}
		
	}
	

    write("Hetzel stands in your way, blocking you from going north.\n");
	write("Hetzel says: Please don't rush off, I need to talk to you.\n");
	write("Hetzel says: The Mayor has a quest for you!\n");
	write("<ask hetzel mayor> for information about the Mayor's quest.\n");
    return 1;
} /* check_exit */

/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object   npc;

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    if (!present("hetzel"))
    {
        npc = clone_object(NPC_DIR + "hetzel")->move(this_object());
    }
} /* reset_room */



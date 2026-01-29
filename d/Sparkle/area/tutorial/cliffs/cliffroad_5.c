/*
 *  /d/Sparkle/area/tutorial/cliffs/cliffroad_5.c
 *
 *  A road in the cliffs leading toward Krolock's castle.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* prototypes */
public void        create_silverdell();
public string      exa_castle();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("on a narrow path leading up through the cliffs");
    set_long("A switchback turns the path suddenly northwest on its"
      + " way up the steep slope of these cliffs. The view of the"
      + " castle improves as the plateau on which it is built"
      + " comes nearer.\n\n");

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "plateau" }),
        "The plateau, though still high above, provides a good view"
      + " of a dark castle which has been built upon it.\n");
    add_item( ({ "castle", "dark castle" }), exa_castle);

    add_exit("cliffroad_4", "north");
    add_exit("cliffroad_6", "northwest");

    add_npc(NPC_DIR + "lion", 1, &->arm_me());

    //This room is instanced.
    instance_entrance = 0;
} /* create_silverdell */


/*
 * Function name:        exa_castle
 * Description  :        provide a state-dependant description for the
 *                       castle
 */
public string
exa_castle()
{
    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "The castle which rests upon the plateau lies completely"
          + " in ruin. Your good deeds have prevailed in these"
          + " lands.\n";
    }

    return "The castle of Baron von Krolock looms darkly over the"
      + " landscape above. The malevolence which emanates from the"
      + " structure is almost palpable even from this distance.\n";
} /* exa_castle */

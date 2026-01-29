/* qpath3.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal;

void
reset_qualinesti_room()
{
    if ( !animal )
    {
        animal = clone_object(NPC + "squirrel");
        animal->move(TO, 1);
    } 
}

void
create_forest()
{
    set_long_desc("You continue following the strange path. It does not " +
        "change much and it is really hard not to find it. Looking back, " +
        "you notice how clear track you leave behind you. Good, you will " +
        "not have a problem to find your way back too.");
    add_my_desc("\n");
    add_item("path",
        "The path doesnt change much. It still leads from west to east.\n");
    add_item(({ "track", "trail" }),
        "You leave a quite visible trail behind you. At least you should " +
        "not have a problems with finding a way back.\n");
    add_item("sky",
        "The sky is still barely visible through the green roof above your " +
        "head.\n");
            
    OUTSIDE;

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    add_exit(FDIR + "qpath4.c", "west", 0, 2);
    add_exit(FDIR + "qpath2.c", "east", 0, 2);

    reset_qualinesti_room();
}

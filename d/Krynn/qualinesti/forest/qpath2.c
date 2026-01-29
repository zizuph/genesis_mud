/* qpath2.c
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
        animal = random_animal();
        animal->move(TO, 1);
    }
}

void
create_forest()
{
    set_long_desc("You continue following the path, that leads you deeper " +
        "into the forest, which is not so dense here. Even if the branches " +
        "above your head do not create so thick roof, you still have a " +
        "feeling it is some sort of tunnel. The path leading west and " +
        "east is easier to find now.");
    add_my_desc("\n");
    add_item("path",
        "This strange path is leading from east to west.\n");
    add_item(({"roof", "branches"}),
        "The green roof above your head is not so dense here yet skill " +
        "the sky is barely visible through it.\n");
    add_item("sky",
        "It is barely visible through the thick mass of branches.\n");
    add_item(({"tunnel", "wall"}),
        "This path create sort of tunnel. It would be really difficult to " +
        "force your way through the thick wall of bushes.\n");    
     
    OUTSIDE;

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    add_exit(FDIR + "qpath3.c", "west", 0, 2);
    add_exit(FDIR + "qpath1.c", "east", 0, 2);

    reset_qualinesti_room();
}

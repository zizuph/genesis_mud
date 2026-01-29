/* qpath1.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object elf;

void
reset_qualinesti_room()
{
if ( !elf )
    {
        elf = clone_object(STD + "scout_base");
        elf->move(TO, 1);
        elf->command("hide");
    }

}

void
create_forest()
{
    set_long_desc("You are standing in a tunnel-like path leading through " +
        "the forest. You are not surprised you could not find it before, " +
        "as it is well hidden and if you were not given a hint you " +
        "would never find this place. The trees and bushes create " +
        "a really thick mass above your head, so it is hard to see even the " +
        "sky from here. The path leads west.");  
    add_my_desc("\n");
    add_item(({"tunnel", "mass"}),
        "The trees are creating sort of tunnel, stretching their branches " +
        "widely above your head.\n");
    add_item("sky",
        "The sky is barely visible through the thick branches.\n");
    add_item("path",
        "This path is well hidden and if you were not given a hint you " +
        "would have a real problems with finding it.\n");        
    
    OUTSIDE;

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    add_exit(FDIR + "forest43.c", "northeast", 0, 2);
    add_exit(FDIR + "qpath2.c", "west", 0, 2);

    reset_qualinesti_room();
}

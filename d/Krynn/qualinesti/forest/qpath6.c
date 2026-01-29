/* qpath6.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;
object animal, elf;

void
reset_qualinesti_room()
{
    if ( !elf )
    {
        elf = clone_object(STD + "scout_base");
        elf->move(TO, 1);
        elf->command("hide");
    }

    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }
}

void
create_forest()
{
    set_long_desc("The area changes a bit. To the north and east the " +
        "trees are creating a tall green wall, but to the southwest you " +
        "notice something what might be a bigger clearing. However, " +
        "because of the really thickly growing bushes it is impossible " +
        "to go there and check. It seems you will have to follow the path."); 
    add_my_desc("\n");
    add_item("area",
        "The trees in this area are not growing so densely as in the other " +
        "parts of the forest.\n");
    add_item(({ "bushes", "bush"}),
        "Thickly growing bushes, south of you block your way, making it " +
        "to go in that direction.\n");
    add_item("path",
        "Since you cannot go staright south, you have to follow the path " +
        "either west or in the east direction.\n");
    add_item("clearing",
        "There seem to be some soft of clearing, not so far to the " +
        "southwest. You are curious to check it.\n");
    add_item("wall",
        "The trees of different types, growing around you, are creating a " +
        "tall green wall, which seem to be impossible to move.\n");           
    
    
    OUTSIDE;

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    add_exit(FDIR + "qpath5.c", "east", 0, 2);
    add_exit(FDIR + "cityview.c", "west", 0, 2);

    reset_qualinesti_room();
}

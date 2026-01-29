/* File : room1.c
 * Somewhere in the Qualinesti forest. A location where a battle between
 * elves and draconians took place. A wounded scout is here.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

#define LOST_SCOUTS    "_lost_scouts"

void   reveal_deorl();
void   hide_again(object scout);

object scout;

void
reset_qualinesti_room()
{

    if ( !(scout = present("deorl", TO)) )
    {
        scout = clone_object(NPC + "deorl");
        scout->move(TO);
        scout->command("hide");
    }    
    
}

void
create_forest()
{
     set_long_desc("The trees are not growing so thick here and it seems " +
        "the edge of the forest is quite close. Suddenly, your attention " +
        "is drawn to something else. Among the fallen branches laying on " +
        "the ground, you notice a few heaps of strange stones. Also the " +
        "foliage seems to be burned here and there. Maybe you should " +
        "take a closer look at it.");

    add_my_desc("\n");
    
    add_item(({ "foliage", "leaves" }),
        "The foliage is burned in a few places. It could be caused " +
        "by fire or acid. Some rusty pieces of metal, that lay here, " +
        "seem to confirm that. You also notice several blood marks.\n");
    add_item(({ "forest", "woods", "trees", "tree" }),
        "The forest is not so thick here bu you still have a feeling " +
        "of being observed. It seems the edge of the forest is not so " +
        "far to the east.\n");
    add_item(({ "branch", "branches", "fallen branches" }),
        "There are many fallen branches on the ground. A few heaps of " +
        "stones are laying among them.\n");
    add_item(({ "heaps", "stones", "heap", "heap of stones" }),
        "A few heaps of stones may be found among the branches. They " +
        "look like remains of dead draconians.\n");
    add_item(({ "blood", "marks", "bloodmarks" }),
        "The blood does not belong to a draconian for sure. You are " +
        "willing to think it is an elven blood.\n");
    add_item(({ "rusty pieces", "pieces", "metal", "rusty items", 
        "pieces of metal" }), 
        "These things look like swords and parts of armours, but they " +
        "are covered with rust and almost completely destroyed, probably " +
        "by acid.\n");       
     
    add_search(({ "rusty pieces", "pieces", "rusty items", "pieces of metal"}),
        5, "You find nothing interesting among these items.\n");
    add_search(({ "foliage", "leaves" }), 4, "You search through the " +
        "foliage, but find nothing interesting.\n");
    add_search(({ "branches", "fallen branches" }), 3, "There are few " +
        "heaps of strange stones among them.\n");
  
    OUTSIDE;

    add_exit(FDIR + "path13.c", "southwest", 0, 2);
/*
    scout = clone_object(NPC + "deorl");
    scout->move(TO, 1);
 */
    reset_qualinesti_room();
    
}

void
enter_inv(object dest, object old)
{
    ::enter_inv(dest, old);
    
    if ( dest->query_prop(LOST_SCOUTS) )
        set_alarm(5.0, 0.0, &reveal_deorl());
}

void
leave_inv(object ob, object new)
{
    ::leave_inv(ob, new);
    
    if ( scout )
        set_alarm(5.0, 0.0, &hide_again(scout));
}
        
void
reveal_deorl()
{
    if ( present("deorl", TO) )
    {
        scout->command("say Wait...");
        scout->command("choke");
        scout->command("reveal me");
    }

}

void
hide_again(object scout)
{
    scout->command("hide");
}
    
/*  
 * Telseron northern gate main file
 * Coded Finwe, September 1996
 */
 
#pragma strict_types
 
#include <stdproperties.h>
#include "/d/Emerald/defs.h"
 
inherit "/std/room";
 
void
create_room()
{
    object gate;

    ::create_room();
    catch(call_other(TELSERON_DIR + "clone_handler", "??"));
 
    set_short("North gate of Telseron");
    set_long("The North Gate.\n" +
        "   Before you is the northern gate of Telseron. It " +
        "is tall and magnificent, to the tops of the trees. " +
        "When you you examine it, you notice the gate is made " +
        "from a steel-like metal. It is durable and and doesn't " +
        "show any signs of battle. The gate often stays open. " +
        "The elves of the city haven't shut them in countless " +
        "ages. This seems odd, but then elves are an odd race; " +
        "there's no telling what protects these strange folks. " +
        "For all you know, these gates could be purely " +
        "ornamental, but you're not sure. \n\n");
 
   add_item(({"walls","wall"}), "The walls of Telseron are " +
        "unlike anything you've ever encounterd. They are nothing " +
        "but trees. Yet, these are the tallest and strongest " +
        "trees you've ever seen. They are taller than the gates " +
        "and offer an impenetrable defense to the city.\n");
   add_item("road", 
        "The road is made from solid blocks of stone. It is clean " +
        "and well travelled. Nevertheless, it is clean and shows " +
        "no sign of use.\n");
   add_item(({"bush", "bushes"}), 
        "Various bushes growing along the road.\n");
   add_item(({"tree", "trees"}), 
        "The trees are giant both in size and in girth. They are " +
        "of a type you have never seen before. It would take at " +
        "at least six men to encircle one tree with their arms " +
        "outstretched.\n");
 
   add_exit( TOWNSHIP_DIR + "forest_edge", "northwest");
 
/* the door file */ 
   gate = clone_object( TOWNSHIP_DIR + "doors/gate_in");
 
   gate->move(this_object());
//   reset_room();
 
}

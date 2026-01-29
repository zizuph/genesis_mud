/*
 * The Garden
 * Coded Finwe
 * September 1996
 */
 
inherit "/d/Emerald/telseron/garden/garden_base.c";
#include "/d/Emerald/defs.h"
#include "garden.h"
 
void
create_garden()
{
    object gate;
    add_my_desc( "Various statues are hidden among the plants. They " +
        "watch over this part of the garden.\n\n");
   
    add_item(({"statue", "statues"}),
        "The statues are carved from marble. Some are smiling while " +
        "others have a solemn look about them.\n");
 
    add_exit( GARDEN_DIR + "path03", "southwest");
    add_exit( GARDEN_DIR + "path04", "south"); 
    add_exit( GARDEN_DIR + "path05", "southeast");
       
    gate = clone_object( TOWNSHIP_DIR + "doors/gate_gar_out");
    gate->move(this_object());
}

/* nentrance.c
 * An entrance to the Qualinesti forest from the Newports-Pax Tharkas road.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
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
    add_my_desc("The trees thin out towards the edge of the forest and " +
        "you notice something, what might be an animal trail leading " +
        "into the woods. The road to Newports is to the east.\n");
    
    add_item(({"trail", "woods" }),
        "A barely noticable animal trail is leading northwest, deep into " +
        "Qualinesti.\n"); 
    add_item("road", 
    	"Not so far to the east you see the road leading to Newports and " +
    	"Pax Tharkas.\n");	
	
    OUTSIDE;
	
    add_exit(FDIR + "path14.c", "northwest", 0, 3);
    add_exit(FDIR + "forest25.c", "north", 0, 2); 
    add_exit(FDIR + "forest54.c", "west", 0, 2); 
    
// Connect with a road Newports-Pax Tharkas.    
    add_exit("/d/Krynn/pax/road/road3", "east", 0, 2);
    
    reset_qualinesti_room();

}

	    
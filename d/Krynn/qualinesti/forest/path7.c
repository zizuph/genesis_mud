/* path7.c
 * The path leading to the elf camp.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

string my_desc();
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
    add_my_desc("@@my_desc");
	
    add_item("trail", 
    	"A barely noticable animal trail, leading through the forest.\n");	
	
    OUTSIDE;
	
    add_exit(FDIR + "path6.c", "west", 0, 2);
    add_exit(FDIR + "path8.c", "southeast", 0, 2);
    add_exit(FDIR + "forest7.c", "northwest", 0, 2);
    add_exit(FDIR + "forest8.c", "north", 0, 2);
    add_exit(FDIR + "forest9.c", "northeast", 0, 2);
    add_exit(FDIR + "forest33.c", "southwest", 0, 2);
    add_exit(FDIR + "forest34.c", "south", 0, 2);

    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nFollowing the animal trail you start to wonder if it " +
    	    "makes any sense to go further, since the forest here becomes " +
    	    "really thick. The path leads back to the west but you also " +
    	    "may continue your trek by going southeastwards.\n";
    }
    
    return "\n";
}

	    
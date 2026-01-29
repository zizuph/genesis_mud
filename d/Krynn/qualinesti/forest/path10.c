/* path10.c
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
	
    add_exit(FDIR + "path9.c", "northwest", 0, 2);
    add_exit(FDIR + "path11.c", "east", 0, 2);
    add_exit(FDIR + "forest20.c", "northeast", 0, 2);
    add_exit(FDIR + "forest42.c", "west", 0, 2);
    add_exit(FDIR + "forest46.c", "south", 0, 2);
    add_exit(FDIR + "forest47.c", "southeast", 0, 2);
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nThe trail leads northwestwards but it also goes back " +
    	    "to the east.\n";   
    }
    
    return "\n";
}

	    
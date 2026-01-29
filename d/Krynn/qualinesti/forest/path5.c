/* path5.c
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
	
    add_exit(FDIR + "path4.c", "northwest", 0, 2);
    add_exit(FDIR + "path6.c", "east", 0, 2);
    add_exit(FDIR + "forest6.c", "north", 0, 2);
    add_exit(FDIR + "forest7.c", "northeast", 0, 2);
    add_exit(FDIR + "forest29.c", "west", 0, 2);
    add_exit(FDIR + "forest31.c", "southwest", 0, 2);
    add_exit(FDIR + "forest32.c", "south", 0, 2);
    add_exit(FDIR + "forest33.c", "southeast", 0, 2);
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nYour skilled eye notices something, what might be an " +
    	    "animal trail leading eastwards. It also goes into the " +
    	    "trees to the northwest.\n";
    }
    
    return "\n";
}

	    
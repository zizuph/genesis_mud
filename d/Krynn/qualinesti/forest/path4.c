/* path4.c
 * The path leading to the elf camp.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

string my_desc();
object animal, animal2;

void
reset_qualinesti_room()
{
    if ( !animal2 )
    {
        animal2 = random_animal();
        animal2->move(TO, 1);
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
    add_my_desc("@@my_desc");
	
    add_item("trail", 
    	"A barely noticable animal trail, leading through the forest.\n");	
	
    OUTSIDE;
	
    add_exit(FDIR + "path3.c", "west", 0, 2);
    add_exit(FDIR + "path5.c", "southeast", 0, 2);
    add_exit(FDIR + "forest3.c", "northwest", 0, 2);
    add_exit(FDIR + "forest4.c", "north", 0, 2);
    add_exit(FDIR + "forest5.c", "northeast", 0, 2);
    add_exit(FDIR + "forest6.c", "east", 0, 2);
    add_exit(FDIR + "forest28.c", "southwest", 0, 2);
    add_exit(FDIR + "forest29.c", "south", 0, 2);
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nYour skilled eye notices something, what might be an " +
    	    "animal trail leading to the southeast. It also goes west.\n";
    }
    
    return "\n";
}

	    
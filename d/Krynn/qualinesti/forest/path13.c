/* path13.c
 * The path leading to the elf camp.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

#define LOST_SCOUTS     "_lost_scouts"

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
	
    add_exit(FDIR + "path12.c", "west", 0, 2);
    add_exit(FDIR + "path14.c", "southeast", 0, 2);
    add_exit(FDIR + "forest21.c", "northwest", 0, 2);
    add_exit(FDIR + "forest22.c", "north", 0, 2);
    add_exit(FDIR + "forest23.c", "east", 0, 2);
    add_exit(FDIR + "forest48.c", "southwest", 0, 2);
    add_exit(FDIR + "forest49.c", "south", 0, 2);
    add_exit(FDIR + "room1.c", "northeast", "@@exit_check", 2);
    
    reset_qualinesti_room();
}

int
exit_check()
{
    if ( TP->query_prop(LOST_SCOUTS) ||
        TP->query_wiz_level() /* || TP->test_bit("Krynn", ?, ?) */ )
    {
        return 0;
    }
    else
    {
        write("You move slowly in that direction, forcing your way through " +
            "the bushes. However, after some time you find your own tracks " +
            "and you realize you have been walking around in circles.\n");
        return 1;
    }
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nYour skilled eye notices something, what might be an " +
    	    "animal trail, leading to the west. It also goes southeast.\n";
    }
    
    return "\n";
}

	    
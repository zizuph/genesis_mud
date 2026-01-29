/* path11.c
 * The path leading to the elf camp.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

string my_desc();
object elf;

void
reset_qualinesti_room()
{
    if ( !elf )
    {
        elf = clone_object(STD + "scout_base");
        elf->move(TO, 1);
        elf->command("hide");
    }
    
}
    
void
create_forest()
{
    add_my_desc("@@my_desc");
	
    add_item("trail", 
    	"A barely noticable animal trail, leading through the forest.\n");	
	
    OUTSIDE;
	
    add_exit(FDIR + "path10.c", "west", 0, 2);
    add_exit(FDIR + "path12.c", "east", 0, 2);
    add_exit(FDIR + "forest20.c", "north", 0, 2);
    add_exit(FDIR + "forest21.c", "northeast", 0, 2);
    add_exit(FDIR + "forest46.c", "southwest", 0, 2);
    add_exit(FDIR + "forest47.c", "south", 0, 2);
    add_exit(FDIR + "forest48.c", "southeast", 0, 2);
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "\nYou continue following the trail, that leads from the " +
    	    "east to the west.\n";

    }
    
    return "\n";
}

	    
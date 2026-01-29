/* path6.c
 * The path leading to the elf camp.
 *
 * Blizzard, 01/2003
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit FORESTBASE;

#include "stream_drink.h"
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
	
    add_item("stream",
        "The stream flows gently, circling among trees. " +
        "From time to time a small fish leaps from it, sending the drops of " +
        "water into the air.\n");
    add_item("water",
        "The water in the stream seems to be clear and cold.\n");
        
    add_cmd_item(({"stream", "water", "from stream"}),
        "drink", "@@drink_water");

    OUTSIDE;
    add_prop(OBJ_I_CONTAIN_WATER, -1);
	
    add_exit(FDIR + "path5.c", "west", 0, 2);
    add_exit(FDIR + "path7.c", "east", 0, 2);
    add_exit(FDIR + "forest6.c", "northwest", 0, 2);
    add_exit(FDIR + "forest7.c", "north", 0, 2);
    add_exit(FDIR + "forest8.c", "northeast", 0, 2);
    add_exit(FDIR + "forest32.c", "southwest", 0, 2);
    add_exit(FDIR + "forest33.c", "south", 0, 2);
    add_exit(FDIR + "forest34.c", "southeast", 0, 2);
    
    reset_qualinesti_room();
}

string
my_desc()
{	    
    
    if (skill_check(TP))
    {
    	return "There is a stream circling among trees and flowing " +
    	    "from north to southwest. " +
    	    "\nYour skilled eye notices something, what might be an " +
    	    "animal trail leading to the east, deep into the forest. " +
    	    "It also goes west.\n";
    }
    
    return "\n";
}

	    
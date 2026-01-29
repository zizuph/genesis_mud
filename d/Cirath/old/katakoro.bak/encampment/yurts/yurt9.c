/* Metalworker's Yurt
 * Chaos, 5 April 1995
 */

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Cirath/katakoro/"

void
create_room()
{
    
    set_short("Metalworker's yurt");
    set_long("This yurt is home to a metalworker.  Scattered about the "+
	"place are various metal items in differing stages of "+
	"completion.  There are sabers, arrowheads, and even a few "+
	"bows.  Along with these items there are some metal shavings "+
	"scattered about the room, a result of the smith's work.  "+
	"Towards the back of the room is a small rough hewn table and "+
	"chair.  There is also an exit to the north which leads to the "+
	"forge.\n");

    add_item("table","There is nothing really remarkable about the table "+
	"other than the fact that it is made of wood, a rare item in the "+
	"treeless steppe.  Sitting on the table there are some rings.\n");
    add_item("rings","These rings are yet another example of the skilled "+
	"craftsmanship found among these barbarians.  Each one is finely "+
	"crafted, with incredible detail.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PATH+"encampment/yurts/forge","north");
    add_exit(PATH+"encampment/camp16","out");
}


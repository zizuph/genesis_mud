inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in the very northen parts of a huge dryplain area. "+
	"As far as you can see there is nothing but grass and smnall hills to the south. To the west "+
	"you can see an large hill with a white tower on the edge. The tower though seems to have seen "+
	"its best days because it has lost one or two levels. To the east you can feel the fresh air "+
        "from the sea. North is nothing but grass. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpc2","south");
}

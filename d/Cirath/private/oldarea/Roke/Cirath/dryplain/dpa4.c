inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in a clearing. One path is going to the east but it"+
	"seems to be almost overgrown by nasty bushes. The west path ends up between two hills and   "+
	"to the north you can rest under a very old and lonely tree. The sun is shining right over your "+
	"head and maybe you shall go to the tree to take a nap. The ground is full av old equipment, "+
	"but it is so rusty that you can't pick it up before it breaks so you don't even think about "+
        "trying. The wind blows and your excellent nose feels something strange. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpa3","west");
	add_exit(DRYPLAIN+"dpa7","north");
	add_exit(DRYPLAIN+"dpa5","east");
}

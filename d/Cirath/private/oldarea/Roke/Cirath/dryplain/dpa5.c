inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

object warrior1,warrior2,warrior3;

reset_room()
{
	if(!(warrior1||warrior2||warrior3)) /* Make sure all are dead before all are dead*/
	{
	warrior1 = clone_object(MONSTER+"warrior");
	warrior2 = clone_object(MONSTER+"warrior");
	warrior3 = clone_object(MONSTER+"warrior");
	warrior1->move(TO);
	warrior2->move(TO);
	warrior3->move(TO);
	}
}

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are walking on an almost forgotten path and you think it might"+
	"end up in something strange and dangerous. This place gives you the creeps anyway. "+
	"There is a distinct smell of dead corpses. As you look down in the grass you can see some "+
	"fresh traces and some blood, everything seems quiet though. The sky somehow look peculiar "+
	"with a colour of dark brown. It almost looks like some smoke comeing from the north. "+
        "Why not figure it out after you have been thinking twice about it.\n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpa4","west");
	add_exit(DRYPLAIN+"dpa6","north");
reset_room();
}

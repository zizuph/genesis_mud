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
	set_long(break_string("You are standing in the middle of a grass ocean. The only thing you "+
	"you might be able to figure out is that there is a path going in east west direction. "+
	"You also see a small and tiny path to the south. Otherwise it is only grass. The sun is burning "+
	"your skin. High up in the sky a bird of prey is flying. Is it a Vulture? well you don't want "+
        "to figure that out, do you?. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpb5","west");
	add_exit(DRYPLAIN+"dpa8","south");
	add_exit(DRYPLAIN+"dpb2","east");
	reset_room();
}

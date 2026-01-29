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
	set_long(break_string("This is the southern parts of a huge area of dry plains. "+
	"The wind blows rather hard and as you look to the west you see some sort of jungle "+
	"and you hear many strange sounds from it. Far to northeast there are some large boulders "+
	"on some sort of hill. Apart from that it is nothing but plains in the whole sight of yours. "+
	"On the ground the grass seems to be very dry.\n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(JUNGLE+"f29","west");
	add_exit(DRYPLAIN+"dpa2","east");
	reset_room();	
}


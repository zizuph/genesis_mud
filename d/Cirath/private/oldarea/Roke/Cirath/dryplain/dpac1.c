inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Cave dungeon");
	set_long(break_string("You are in a cave quite dark and with an enormous "+
	"noise that you are only lucky you can still think. Further to the east you realize "+
	"that you can see some light or at least you think so. But you are sure that the noise "+
	"comes from the east. The ground is coverd with old campfires and stuff. Tales are told"+
	"about this cave. Maybe you have found something interesting. \n",70));
	add_exit(DRYPLAIN+"dpac2","east");
	add_exit(DRYPLAIN+"dpa9","south");
	add_prop(ROOM_I_LIGHT, 0);
	add_prop(ROOM_I_INSIDE, 1);
}
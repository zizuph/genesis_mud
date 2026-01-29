inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in the middle of a grass ocean. The only thing you "+
	"you might be able to figure out is that there is a path going in west north direction. "+
	"Otherwise it is only grass. The sun is burning your skinn. further to north you notice that "+
	"the path bennds to the west after small hill. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpb1","west");
	add_exit(DRYPLAIN+"dpb3","north");
}

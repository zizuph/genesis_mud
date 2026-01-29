inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing between two small hills. The road continues to "+
	"southwest and east. To the east the plains are growing larger and the path is almost overgrown "+
	"here. Far away to the north something reflects the sun. To the northeast you can see a lonely, "+
	"very old tree, it must be over thousand year. The ground is full of marks from some sort of. "+
	"battle long time ago. The sun is burning your skin so it might be smart to rest soon. "+
        "Suddenly you hear some noise far to the northeast or are you just imagining? \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpa2","southwest");
	add_exit(DRYPLAIN+"dpa4","east");	
}

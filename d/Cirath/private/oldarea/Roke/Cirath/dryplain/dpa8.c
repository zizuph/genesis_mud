inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in a wide open grass field with out any changes for "+
	"several miles it seems. To the southwest you might be able to figure out some kind of tree "+
	"Otherwise it is just grass and grass all over. The road or better path is going north and "+
	"southwest. But maybe you can figure out another way. The sun seem to be even harder now when "+
        "you are looking out over the huge landscape. No place to rest if you walk north. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpa7","southwest");
	add_exit(DRYPLAIN+"dpb1","north");
}

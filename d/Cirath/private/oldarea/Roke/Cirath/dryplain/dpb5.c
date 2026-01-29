inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are in the western parts of a huge grass field. The path "+
	"continues to the north and east. Northeast you see some small hills and far to the "+
	"north something reflects the sun, it might be a building. far to the southwest you"+
	"see the enormous jungle of Cirath. The only thing for you is to keep on moving because  "+
        "the sun is burning you all the time. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpb6","north");
	add_exit(DRYPLAIN+"dpb1","east");
}

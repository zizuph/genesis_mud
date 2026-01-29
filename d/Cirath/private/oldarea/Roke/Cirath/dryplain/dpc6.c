inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing on the path to a large hill in the northwest. "+
	"Just in front of the hill a huge tower stand on its post. The tower however seems to have "+
	"seen its best days. One or two leves is missing and it looks very unsafe to climb."+
	"To the south is only plains with some hills. If you continue north you will turn up "+
        "on the hill and south in the middle out of nowhere. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpc7","north");
	add_exit(DRYPLAIN+"dpc5","southeast");
}

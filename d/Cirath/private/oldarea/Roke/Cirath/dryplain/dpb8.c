inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string(" "+
	" "+
	" "+
	" "+
        " \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpb8","west");
	add_exit(DRYPLAIN+"dpb10","north");
	add_exit(DRYPLAIN+"dpb9","northeast");
}

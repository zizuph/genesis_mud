inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in the middle of a grass ocean. You really hate this"+
	"grass and you wish you never entered this area at all. To the west the path ends up in some "+
	"sort of dead end. But I might be worth a visit though. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpb4","west");
	add_exit(DRYPLAIN+"dpb2","south");
}

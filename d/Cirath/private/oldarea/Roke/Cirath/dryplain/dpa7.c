inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in a bend of the path under an old tree. To the "+
	"northeast it continue into a thick grass land and to the south into a clearing.  "+
	"This place seems to be perfect when you want to take a nap. But when you examine the tree "+
	"you notice that this tree must have been used as a tree to hang people in. The ground is covered "+
	"with old corpse parts and in the three some ropes is still hanging. There is also a rock for you "+
        "to rest on. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpa4","south");
	add_exit(DRYPLAIN+"dpa8","northeast");
}

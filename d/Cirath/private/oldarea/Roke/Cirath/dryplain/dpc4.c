inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in a valley by the north side of the main path "+
	"To the northwest you can see the path continue in to some sort of high hill with a  "+
	"high tower on the edge. The tower seem looks like a defence tower and it has lost  "+
	"one or two levels and it looks more than a ruin. The fasad however is reflecting "+
        "the sun into your eyes. The path itself seems to be a dead end. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpc2","east");
}

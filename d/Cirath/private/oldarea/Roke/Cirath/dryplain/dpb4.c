inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in a dead end between two small hills."+
	"Back to your east is the only way to go and you better do that fast, since the remains "+
	"on the ground shows that one or two humans finished their lives here a couple of days ago. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpb3","east");
}

inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in a north south leading path in a large grass "+
	"field. Some tracks on the ground shows that there has been a fight here not that long ago. "+
	"Further to the north your eyes can make out a sort of clearing and to the south you only "+
	"notice hills and grass. The sky is clear and blue. You don't know why but you feel observed. "+
        "Maybe you should take it easy on your travel throught theses areas. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpc3","north");
	add_exit(DRYPLAIN+"dpb9","south");
}

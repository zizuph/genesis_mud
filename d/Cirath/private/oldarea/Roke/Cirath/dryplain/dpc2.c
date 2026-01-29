inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("you are standing in the northen parts of the dangerous dryplains. "+
	"To the east you can see the whole ocean and to the north nothing but grass. To the south "+
	"and southwest many small hills are the only landmarks in the landscape. Further to the west "+
	"a large tower is standing just before a large hill. This place seem to be some sort of clearing "+
        "but only the south and southwest path seems used. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpc4","west");
	add_exit(DRYPLAIN+"dpc5","southwest");
	add_exit(DRYPLAIN+"dpc1","south");
	add_exit(DRYPLAIN+"dpc3","north");
}

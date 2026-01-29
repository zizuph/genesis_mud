inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("This is the southern parts of a huge area of dry plains. "+
	"The road continues from the jungle in the west and through an endless land to northeast. "+
	"Somehow you feel that there is something strange with this plain. A long time a ago this "+
	"field served as battle field and the signs after it are not overgrown completely. Old and rusty "+
	"armours are lying everywhere, and some old remains of unburried skeletons tells you that this "+
        "wasn't so far away. Maybe you have entered some enemy area.\n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpa1","west");
	add_exit(DRYPLAIN+"dpa3","northeast");	
}

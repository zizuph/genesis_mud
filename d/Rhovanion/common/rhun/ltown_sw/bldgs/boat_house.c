
#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/farlong.h"

init()
{
	::init();
	add_action("wood_chips_search","search");
}

create_room()
{
set_short("Boat House");
set_long(break_string("This is a large wooden building where the local"
	+" shipwright apparently does his planning and construction."
	+"  Shards of various types of wood are scattered across the"
	+" floor, along with mounds of sawdust."
	+"  In the corner stands a pile of wood chips."
	+"  The proprietor, however,"
	+" is apparently not here right now.  The only exit is back onto"
	+" the street to the"
	+" west."
	+"\n",75));

AE(RHUN+"ltown_sw/streets/st8","west",0);

add_prop(ROOM_I_LIGHT,1);IN

add_item("sawdust",break_string("The sawdust covers the floor in a"
	+" thick layer.  It makes you want to sneeze... ACHOO!!",75));
add_item(({"shards","shard","wood"}),break_string("The wood comprises"
	+" the shipwright's half-finished projects.  It is of no real"
	+" interest, though.\n",75));
add_item(({"pile","chips","wood chips"}),break_string("There seems to be"
	+" something odd about this pile of wood chips.\n",75));

}

int
wood_chips_search(string str)
{
	NF("Search what?\n");
	if(!strlen(str)) return 0;
	if(!((str=="chips")||(str=="wood chips"))) return 0;
	
	write("You search through the pile of wood chips.\n"
		+"There is nothing here now; perhaps you should"
		+" return at some time in the future?\n");
	return 1;
/* When Rhosgobel quests are coded, the arm armour for
 * the Equipment Quest will be here. 
 */

}

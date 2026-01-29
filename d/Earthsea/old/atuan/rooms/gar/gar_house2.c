inherit "/d/Earthsea/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Earthsea/atuan/defs.h"

object old_woman;

void
create_earthsea_room()
{
	set_short("Inside a small wooden house.");
	set_long(BS("This is a small, well tended house which has obviously had a"+
		" lot of thought put into it's decor. As well as the beautiful flowerbed"+
		" outside, the inside is immaculate. A small table has two place settings"+
		" on a finely woven blue and white chequered tablecloth. A workbench"+
		" has a number of utensils, all hanging neatly from hooks. An unlit fireplace"+
		" is well stocked with firewood, and a heavy cauldron sits in it. A pair of thick"+
		" curtains are tied back by the window, and all around the room are small"+
		" planters containing many varieties of flowers. It smells fresh, like baked"+
		" bread, with a sweetness eminating from the flowers. A small doorway lies east"+
		" which leads to the bedroom.",70));
		 	
	INSIDE;
	
	add_item(({"flowerbed"}),"A small but well tended flowerbed containing at least"+
		" ten varieties of flower.");
	add_item(({"table","small table"}),"It is a small table constructed from what you"+
		" believe to be mahogany with two place settings.");
	add_item(({"chair","simple chair"}),"It is a simple chair constructed from mahogany.");
	add_item(({"tablecloth","cloth","chequered tablecloth"}),"A well made, thick tablecloth.");
	add_item(({"fireplace","cauldron"}),"A large fireplace which contains plenty of"+
		" firewood, and is ready to be lit. The cauldron rests over the firewood and"+
		" is empty.");
	add_item(({"curtains","thick curtains"}),"A pair of thick, blue and white chequered"+
		" curtains.");
	add_item(({"workbench","utensils"}),"A long wooden worktop which has a number of cooking"+
		" utensils hanging over it.");


add_exit(GAR + "gar_road2","northwest",0);
add_exit(GAR + "house2_bed","east",0);

reset_room();

}

reset_room()
{
if (!old_woman)
        {
old_woman = clone_object(LIVING + "old_woman");
old_woman->move_living("xxx", TO);
        }
}



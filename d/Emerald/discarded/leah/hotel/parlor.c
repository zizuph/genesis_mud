inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
	set_short("Hotel's Parlor");
	set_long("   The Hotel's parlor has a large fireplace with a "+
		"woven rug placed in front of it. There is a large couch "+
		"on the western wall. And a piano on the northern wall. "+
		"There are two chairs sitting in the corners with a small "+
		"table beside them. There are lamps sitting on the table. "+
		"There are double doors leading out into the entrance of "+
		"the hotel and another set of double doors leading into the "+
		"dinning room.\n\n");  

    	add_item("rug", "It's a rather large woven rug, it is smooth and "+
		"soft to the touch. The colors of the rug match the "+
		"room perfectly.\n");
    	add_item("fireplace", "The fireplace is located on the southern "+
		"wall. There is a copper basket sitting beside it, with "+
		"a matching poker set on the other side.\n");
    	add_item("basket", "The basket is made of copper, it is very "+
		"sturdy. It currently is full of wood.\n");
    	add_item("poker", "The poker set is hand crafted. It looks like "+
		"it keep this hotel warm for a long time.\n");
    	add_item("wood", "The wood is neatly stacked in the basket.  You "+
		"can smell the fresh cut oak.\n");
	add_item("couch", "The couch is simple designed with wood crafted "+
		"legs. The colour of flowers used in the cloth is of exquite "+
		"design.\n");
	add_item("piano", "It looks as if the piano is played very little. "+
		"Perhaps they have someone come in and play for the customers "+
		"of this fine hotel.\n");
	add_item(({"chair", "chairs"}), "The chairs match the couch.  The floral "+
		"print is the same. They are very big and comfy.\n");
	add_item("table", "These tables are matching.  They are round and tall. "+
		"perfect to have a lamp to read by.\n");
	add_item(({"lamp", "lamps"}), "The lamps sit upon the round tables. "+
		"they are tall, glass lamps.  There is a rose inside each "+
		"lamp.\n");
	add_item(({"doors", "double doors", "door"}), "There are two sets of "+
		"double doors one leading into the dinning room, and another "+
		"leading out into the entrance.  The doors are of heavy wood. "+
		"The doors have engraved designes of vines and roses.\n");
   
	add_prop(ROOM_I_INSIDE, 1);

	add_exit(VILLAGE_DIR + "hotel/entrance", "south");
	add_exit(VILLAGE_DIR + "hotel/dining", "west");
}

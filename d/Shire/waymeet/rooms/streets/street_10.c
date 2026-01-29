/* Outdoors in Waymeet
 * Raymundo, Feb 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/waymeet/defs.h"
#include "/d/Shire/eastroad/western/local.h"
#include "/d/Shire/waymeet/lib/hobbitmaker.h"
inherit WAYM_LIB_DIR + "base_waymeet.c";

void add_hobbit();
object hobbit;



void reset_shire_room();

//It seems like a bad idea to have a torch in a fireworks shop, 
//So we'll prevent that from happening. :)
int
block_people()
{
	 object *inv;
	 int i = 0;
	 inv = all_inventory(this_player());
	 
	 for (i=0; i<sizeof(inv); i++)
	 {
		 if(inv[i]->id("torch"))
		 {
			 write("You can't go into the fireworks shop with a torch. "
				+ "One careless spark could kill everyone!\n");
			return 1;
		 }
		 if(inv[i]->id("lamp"))
		 {
			 write("You can't go into the fireworks shop with a lamp. "
				+ "One careless spark could kill everyone!\n");
			 return 1;
		 }
	 }
	 return 0;
	 
 }

void
create_waymeet_room()
{
	extraline = ("North of here is the famous Foaming Mug, an inn of "
		+ "great repute! To the west you see a bright orange building, "
		+ "and to the east you see a post office.\n");
	add_item( ({"building", "orange building", "bright orange building"}),
		"This building is painted a particularly garish shade of orange. "
		+ "It's so bright that you could probably see it in the very "
		+ "black of night. A small sign hangs over the door.\n");
	add_item("door", "It is open. Looks like you can enter.\n");
	add_item("orange", "It's really over the top, this orange. Why "
		+ "not yellow or green like normal hobbits?\n");
	add_item( ({"sign", "small sign"}), "@@exa_sign@@");
	add_item( ({"office", "post office"}), "The post office is to the east.\n");
	add_item( ({"inn", "mug", "foaming mug"}), "The Foaming Mug Inn is to "
		+ "the north. It sounds lively and fun--but perhaps too lively and "
		+ "too fun. It seems like the kind of place where people would get "
		+ "drunk and puke on the floor!\n");
	
	add_cmd_item( ({"sign", "small sign"}), "read", "@@exa_sign@@");
	add_street(0);
	add_hobbit();
	
	add_exit(WAYM_STREET_DIR + "street_9", "north", gravel_sound, 0, 0);
	add_exit(WAYM_SHOP_DIR + "firework_shop", "west", block_people, 0, 0);
	add_exit(WAYM_SHOP_DIR + "post", "east", gravel_sound, 0,0);
    add_exit("/d/Shire/ns_road/rooms/road22", "south", gravel_sound, 0, 0);
	
	
}
void
reset_shire_room()
{
	add_hobbit();
}



void
init()
{
	::init();


}

string
exa_sign()
{
	return(""
	+ " +~~~~~~~~~~~~~~~~~~~~~~~~+\n"
	+ " |     .;*;;.             |\n"
	+ " |  .;;*;;'' '*;.         |\n"
    + " |           .;'          |\n"
    + " |          '*.           |\n"
    + " |          .;*'          |\n"
    + " |    _.---';:.-----.._   |\n"
    + " | / .-```  *;.``--..  @  |\n"
    + " | @ '._   .;*'    _.' /  |\n"
    + " |  '-._``--.._.--'_.-'|  |\n"
    + " |  |   ``--------'   .|  |\n"
    + " |  |   .' Y E      .' |  |\n"
    + " |  | .' O L D E  .'   |  |\n"
    + " |  |'F I R E W O R K S|  |\n"
    + " |  |  S H O P P E  .' |  |\n"
    + " |  | .'  ` .'    .'   |  |\n"
    + " |  |'   _'.    .'    .|  |\n" 
    + " |  |   . .--'.'    .' |  |\n"
    + " |  | .'  ....... .'   |  |\n"
    + " |  |'  .             .|  |\n"
    + " |  | .'          .'   |  |\n"
    + " |  |'     ------`     |  |\n"
    + " |  '---...______...---'  |\n"
	+ " |                        |\n"
	+ " +~~~~~~~~~~~~~~~~~~~~~~~~+\n\n");
}

void
add_hobbit()
{
	   if (!present(hobbit))
	   {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(ELDER);
	hobbit->set_gender(1);
    hobbit->arm_hobbit();
	hobbit->move(TO);
	   }
	   return ;
	
}
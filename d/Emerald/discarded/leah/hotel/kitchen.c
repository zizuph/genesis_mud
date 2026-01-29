inherit "/std/room";
 
#include "/d/Emerald/defs.h"

int smell(string str);

void
create_room()
{
	set_short("Castle kitchen");
	set_long("   You are in a rather large kitchen. From the "+
	     "smell of food, you think there might have been a party here "+
	     "recently.\n\n" );
 
	add_prop(ROOM_I_INSIDE, 1);
 
	add_exit(VILLAGE_DIR + "hotel/entrance", "east");
	add_exit(VILLAGE_DIR + "hotel/dining", "north");
}
 
void
init()
{
	::init();
	add_action(smell, "smell");
	add_action(smell, "sniff");
}
 
int
smell(string str)
{
	notify_fail(capitalize(query_verb()) + " what?\n");
	if (str && str != "food")
	return 0;
	write("It smells like some kind of roast. Lots of it.\n");
	return 1;
}

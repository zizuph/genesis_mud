inherit "/std/room";
#include "tunnel.h"

reset_room()
{
}
 
create_room()
{
    object key;
	set_noshow_obvious(1);

    set_short("Junction in tunnel");
	set_long(BSS("The tunnel widens up to a small junction, "+
		"with exits leading north, east and west.\n"));
 
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(TUNN_D+"e_junc","east",0);
	add_exit(TUNN_D+"w_junc","west",0);
	add_exit(TUNN_D+"tunnel1","north",0);

	add_item(({"tunnels","tunnel"}),BSS(
			"These tunnels are so small you have to crawl "+
			"your way through. You suspect some small "+
			"creature have made them.\n"));

}

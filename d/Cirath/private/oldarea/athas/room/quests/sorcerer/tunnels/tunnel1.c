inherit "/std/room";
#include "tunnel.h"

reset_room()
{
}
 
create_room()
{
    object key;
	set_noshow_obvious(1);

    set_short("Tunnel");
	set_long(BSS("This is a tunnel, with exits "+
		"leading north and south. To the south you see a small "+
		"junction and to the north you see the tunnel go on into darkness.\n"));
 
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(TUNN_D+"junction","south",0);
	add_exit(TUNN_D+"tunnel2","north",0);


	add_item(({"tunnels","tunnel"}),BSS(
			"These tunnels are so small you have to crawl "+
			"your way through. You suspect some small "+
			"creature have made them.\n"));
	add_item(({"junction","small junction"}),BSS(
		"The junction looks like it could crumble at any "+
		"time, maybe you should reconsider going that way ?"));

}

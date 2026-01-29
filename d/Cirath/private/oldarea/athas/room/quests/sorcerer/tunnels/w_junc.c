inherit "/std/room";
#include "tunnel.h"

reset_room()
{
}
 
create_room()
{
    object key;
	set_noshow_obvious(1);

    set_short("Bend in tunnel");
	set_long(BSS("This is a bend in the tunnels, with exits "+
		"leading east and south. To the east you see a small "+
		"junction and to the south you see some tunnels.\n"));
 
    add_prop(ROOM_I_INSIDE, 1);

	add_exit(TUNN_D+"junction","east",0);
	add_exit(TUNN_D+"rat_hole2","south",0);


	add_item(({"tunnels","tunnel"}),BSS(
			"These tunnels are so small you have to crawl "+
			"your way through. You suspect some small "+
			"creature have made them.\n"));
	add_item(({"junction","small junction"}),BSS(
		"The junction looks like it could crumble at any "+
		"time, maybe you should reconsider going that way ?"));

}

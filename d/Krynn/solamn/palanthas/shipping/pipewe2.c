/* created by Aridor 12/14/93 */

#include "windpipe.h"

inherit SHIP_ROOMBASE;

void
create_palan_room()
{
    set_short("In a long horizontal pipe");
    set_long("You are in a horizontal pipe. The shaft is quite high " +
		"and you can walk south or north along the bottom." +
		" The walls of the pipe seem to glow a little.\n");

    add_exit(SHIP + "pipewe1","north",-30,1);
    add_exit(SHIP + "pipe3","south",0,1);

    LIGHT;
    add_item(({"shaft","pipe"}),
	     "The pipe is a round pipe and it is very wide, you can hardly see the " +
	     "top of it. You wonder what the purpose of the pipe is.\n");
    add_item(({"floor","roof","top","wall","walls"}),
	     "The walls are made from some unkown material. They are very smooth and " +
	     "give off a strange glow, illuminating the pipe.\n");
}


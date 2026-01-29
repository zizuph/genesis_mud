/* created by Aridor 12/14/93 */

#include "windpipe.h"

inherit SHIP_ROOMBASE;

void
create_palan_room()
{
    set_short("Inside a pipe");
    set_long("You are in a vertical shaft. The shaft is quite wide " +
		"and you can climb down or up on the ladder which is " +
		"bolted to the wall. The walls of the shaft seem to glow a little.\n");

    add_exit(SHIP + "pipeud1","up",-10,5);
    add_exit(SHIP + "pipe2","down",0,1);

    LIGHT;

    add_item(({"shaft"}),
	     "The shaft is a round shaft and it is very wide, you can hardly see the " +
	     "wall on the other side. You wonder what the purpose of the shaft is.\n");
    add_item(({"wall","walls"}),
	     "The wall close to you is made from some unkown material. It is very smooth " +
	     "and the ladder you are standing on is bolted to the wall. You can hardly " +
	     "make out the wall on the other side of the shaft though. The wall give off " +
	     "a strange glow, illuminating the shaft.\n");
    add_item("ladder",
	     "It's a very long ladder going up and down made from iron. You cannot see " +
	     "either end of it.\n");
}


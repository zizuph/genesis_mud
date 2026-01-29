/* created by Aridor 12/14/93 */

#include "windpipe.h"

inherit SHIP_ROOMBASE;

void
create_palan_room()
{
    set_short("In a long horizontal shaft");
    set_long("You are in a horizontal shaft. The shaft is quite high " +
		"and you can walk south or north along the bottom." +
		" The walls of the shaft seem to glow a little.\n");

    add_exit(SHIP + "pipe2","north",-30,1);
    add_exit(SHIP + "pipe3","south",-30,1);

    LIGHT;
}


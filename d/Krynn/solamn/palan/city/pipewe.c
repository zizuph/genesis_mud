/* created by Aridor 12/14/93 */

#include "windpipe.h"

inherit ROOM_BASE

void
create_palan_room()
{
    set_short("In a long horizontal shaft");
    set_long(BS("You are in a horizontal shaft. The shaft is quite high " +
		"and you can walk south or north along the bottom." +
		" The walls of the shaft seem to glow a little.",SL));

    add_exit(ROOM + "pipe2","north",-30,1);
    add_exit(ROOM + "pipe3","south",-30,1);

    LIGHT;
}


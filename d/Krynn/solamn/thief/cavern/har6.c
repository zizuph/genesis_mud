/* created by Aridor 03/09/94 */

#include "../local.h"
#include <macros.h>

inherit ROOM_BASE

object ship;

void add_ship();

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a pier in a cavern. There is an underground bay " +
	     "opening up to the north from here. The pier continues " +
	     "west and north" +
	     "east. You can see a faint light coming from somewhere " +
	     "around a corner in the north.\n");
    
    add_exit(CAVERN + "har5","west");
    add_exit(CAVERN + "har7","northeast");
    
    DARK;
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_ship();
}

void
add_ship()
{
    if (!ship)
    {
	(ship = clone_object("/d/Krynn/solamn/thief/ship/ship"))->move(TO,1);
	/*ship->start_ship();*/
	(ship->query_captain())->move_living("xx",TO);
	(ship->query_captain())->set_ship(ship);
    }
}


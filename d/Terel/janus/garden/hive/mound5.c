/* mound 5 */
/* janus 921111 */
/*
 * Lucius - Jan 2021
 *    Cleaned up and modernized.
 */
inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()

public void
create_room()
{
    set_short("tunnel");
    set_long("The tunnel appears to slope slightly upwards.\n");

    add_item(({"ground","floor","walls"}),
        "The walls, floor and ceiling are warm to the touch.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(JANUSDIR + "garden/hive/mound3","southwest",0,0);
    add_exit(JANUSDIR + "garden/hive/mound7","east",0,0);
}

public string
do_search()
{
    if (!CAN_SEE_IN_ROOM(TP))
    {
	return "You are blind as a bat in the darkness, so you'd better " +
	  "get some light if you want to search here.\n";
    }
    return "There is nothing of value here.\n";
}

/*
 * Overlook in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>


public void
union_room(void)
{
    set_short("overhang");
    set_long("The southern corridor widens suddenly here, "+
	"and ends at a precarious chasm ledge overlooking a "+
	"vast lake of yellow molten rock. Far to the north, "+
	"the opposite wall of the chasm rises up into the "+
	"darkness, at the top of which you can just make out "+
	"a large stone bridge. The ledge follows the chasm "+
	"wall at a gentle incline to the northwest.\n");

    add_item(({"lake","molten rock","lava","chasm","chasm wall"}),
	"@@exa_chasm@@");
    add_item("bridge","The bridge is about a hundred feet "+
	"up, spanning the entire chasm.\n");
    add_item(({"wall","walls","rock"}),"The walls from the corridor "+
	"to the south widen here, making the ledge quite wide.\n");

    add_exit("overhang_nw", "northwest");
    add_exit("hall_n3", "south");
}

public void
init(void)
{
    ::init();
    add_action(jump_ledge, "jump");
    add_action(jump_ledge, "leap");
}

public void
leave_inv(object ob, object where)
{
    ::leave_inv(ob, where);
    remove_warned(ob);
}

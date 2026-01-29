/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

public object hyacinth, door;


public void
reset_room(void)
{
    /* If the NPC has been slain, then the "union_o_corpse_of_<npc>" */
    /* prop will be set in this room (from the make_corpse())        */
    /* function in NPC + "npc.c". Until the corpse is destroyed,     */
    /* the Union member will not reset.                              */

    if (!hyacinth)
    {
	if (!objectp(query_prop(UCORPSE_PROP("hyacinth"))))
	    hyacinth = clone_here(NPC + "hyacinth");
    }

    if (hyacinth && !present(hyacinth))
	hyacinth->move_living("away", TO);
}

public void
union_room(void)
{
    set_short("wide corridor");
    set_long("Smooth walls of pale jade-coloured stone rise up, "+
	"framing this short corridor in a gentle glow. The corridor "+
	"ends abruptly here, leading to a tall pine door. A hot breeze "+
	"drifts down the hall from the east, brushing up against the "+
	"unadorned door to the west.\n");

    add_item(({"wall","walls"}),
	"They are a luminous green colour, almost like jade.\n");
    add_item(({"floor","ground"}),
	"It is smooth.\n");

    add_exit("hall_n3", "east");

    add_object(OBJ +"c_door_e");
    reset_room();
}

static void
update_vars(void)	{ door = present("_union_door"); }

private void
shut(void)
{
    if (!door->query_open())
	return;

    door->do_close_door("The tall pine door swings shut.\n");
    door->query_other_door()->do_close_door("The tall pine door swings shut.\n");
    door->do_lock_door("");
}

public void
leave_inv(object ob, object from)
{
    ::leave_inv(ob, from);

    if (door->query_open())
	set_alarm(1.0, 0.0, shut);
}

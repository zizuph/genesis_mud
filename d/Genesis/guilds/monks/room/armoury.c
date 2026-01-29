/*
 * File:     armoury
 * Created:  Cirion
 * Purpose:  Armoury for the Oranea Monks
 * Modification Log:
 *
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>
#include <language.h>
#include <std.h>

inherit ROOMBASE;

private static object last_mover = 0;
private static object *last_taken_objects = ({ });
private static object *last_dropped_objects = ({ });
private static object guardian;

public void reset_room ();

void
create_room()
{
    set_short("armoury");
    set_long("Bare white stone walls without windows surround this stark, "
        + "clean room.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("dorm", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("north", "You enter into the cool, dark armoury.\n");

	reset_room ();
}

public void
log_move (object who, object *stuff, string which_way)
{
	string			name, message;

	if (guardian == 0 || !present (guardian))
		return;

	if (!who || !living (who)
		|| !(CAN_SEE(guardian, who)) || !(CAN_SEE_IN_ROOM(guardian))
		|| who->query_wiz_level ())
		name = "Someone";
	else if (!m_query_monk (who))
		name = LANG_ADDART (who->query_nonmet_name ());
	else
		name = who->query_name ();

	message = name + " " + which_way + " "
		+ COMPOSITE_DEAD (stuff) + ".";

	guardian->note_message (message);
}

public void
flush_last_moved ()
{

	last_taken_objects = filter (last_taken_objects, objectp);
	last_dropped_objects = filter (last_dropped_objects, objectp);
	
	if (sizeof (last_taken_objects) > 0)
		log_move (last_mover, last_taken_objects, "took");


	if (sizeof (last_dropped_objects) > 0)
		log_move (last_mover, last_dropped_objects, "left");

	last_mover = 0;
	last_dropped_objects = ({ });
	last_taken_objects = ({ });
}

public void 
leave_inv (object ob, object to)
{
	::leave_inv (ob, to);

	if (ob == 0)
		return;

	if (living (ob) && last_mover == ob)
		flush_last_moved ();

	if (living (ob) || !living (to))
		return;

	if (last_mover != to && last_mover != 0)
		flush_last_moved ();

	last_mover = to;

	if (member_array (ob, last_dropped_objects) >= 0)
		last_dropped_objects -= ({ ob });
	else
		last_taken_objects += ({ ob });
}

public void 
enter_inv (object ob, object from)
{
	::enter_inv (ob, from);

	if (living (ob) || !(living (from)))
		return;

	if (last_mover != from && last_mover != 0)
		flush_last_moved ();

	last_mover = from;

	if (member_array (ob, last_taken_objects) >= 0)
		last_taken_objects -= ({ ob });
	else
		last_dropped_objects += ({ ob });
}

public void
reset_room ()
{
	if (!guardian)
		guardian = clone_object (MONK_NPC + "shisa");

	if (!present(guardian))
		guardian->move_living("away", TO);
}



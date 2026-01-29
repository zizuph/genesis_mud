/*
  /room/void.c

  This object should always load and work.
  We must inherit /std/object to be allowed to enter it.

*/
#pragma save_binary

inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/secure/std.h"

void
create_object()
{
    set_name("void");
    set_short("The void");
    set_long(short() + ".\n" +
	     "You come to the void if you fall out of a room,"+
	     " and have nowhere to go.\n");
    add_prop(ROOM_I_IS, 1);
    add_prop(CONT_I_IN, 1);
    add_prop(OBJ_I_LIGHT, 1);
}

init()
{
    string last_room;

    last_room = SECURITY->wiz_home(this_player());
    call_out("kick_out",1,({ this_player(), last_room }) );

}


kick_out(arg)
{
    object tp, room;

    tp = arg[0];
    room = arg[1];

    if (environment(tp) != this_object()) {
	return;
    }

    tell_object(tp, "\nYou are transfered out of the void to: " +
		room->short() + ".\n");

    if (tp->move_living("X",room))
	tp->move_living("X",DEFAULT_START);
}
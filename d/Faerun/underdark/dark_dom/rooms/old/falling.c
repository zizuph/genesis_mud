/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

void
create_tunnel()
{
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("Falling");
    set_long("You are falling rapidly towards the ground, arms and legs flailing everywhere.\n");

    add_prop(ROOM_M_NO_ATTACK, "You cannot fight while falling.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
}


void
land(object ob)
{
string str;

    if (!ob || !present(ob, this_object()))
	return;

    str = "You hear a horrible noise from above, suddenly you see ";

    if (living(ob))
    {
	tell_room(TUN_DIR + "u07", str + QTNAME(ob) +
	  " slams into the ground.\n");
	ob->move_living("M", TUN_DIR + "u07");

	tell_object(ob, "You slam into the ground with terrible force!\n");
	ob->heal_hp(-600);
	ob->remove_prop(LIVE_S_EXTRA_SHORT);

	if (ob->query_hp() < 1)
	    ob->do_die(this_object());
    }
    else
    {
	tell_room(TUN_DIR + "u07", str + LANG_ASHORT(ob)+" falls down.\n");
	ob->move(TUN_DIR + "u07");
    }
}

void
halfway(object ob)
{
    string str;

    if (!ob || !present(ob, this_object()))
	return;

    str = "You hear a loud noise and suddenly see ";

    if (living(ob))
    {
	tell_object(ob, "The ground is getting closer.\n\n");
	str += QTNAME(ob);
    }
    else
	str += LANG_ASHORT(ob);

    tell_room(TUN_DIR + "u06", 
      str + " fall through the shaft and continue down.\n");

    set_alarm(3.0, 0.0, &land(ob));
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
	tell_object(ob, "Suddenly the ground disappears from beneath you.\n\n");
	add_prop(LIVE_S_EXTRA_SHORT, " is also falling.\n");
    }

    set_alarm(5.0, 0.0, &halfway(ob));
}

int
quit(string str)
{
    write("You're too distracted to do that.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(quit, "quit");/* Don't let anyone quit himself out. */
}

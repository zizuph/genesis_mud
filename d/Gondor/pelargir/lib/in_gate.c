/*
 *	/d/Gondor/pelargir/lib/in_gate.c
 *
 *	Inner city gate for Pelargir
 *
 *	Olorin, June 1995
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int     close_gate_id;

object  gate,
        other_gate;

void
create_gate(string which)
{
    string  swhich = which[0..0];

    set_short("inside the "+which+" gate of Pelargir");

    add_prop(ROOM_I_INSIDE,1);

    add_item(({"gatehouse", "gatehouses", "archway", }), BSN(
        "You are standing at the "+which+" gate of Pelargir in an "
      + "archway formed by a broad tower to each side and a wide "
      + "arch above your head connecting both tower. At the "+which
      + " end of the archway are the two wings of the gate. A narrow "
      + "doorway leads into each of the towers from here, probably "
      + "into gatehouses where the guards spend their time."));
    add_item(({"arch"}), BSN(
        "High above you, you can see the large, grey stone blocks "
      + "which have been expertly fitted together to form the wide "
      + "arch that spans above the towers on the sides of the gate."));
    add_item(({"tower", "towers", }), BSN(
        "On both sides of the gate, the city wall ends in a "
      + "large round tower. The towers are just little higher than "
      + "the tops of the city wall and were built from the same "
      + "grey stone blocks as the walls. From inside this archway "
      + "one can enter gatehouses in each of the two towers."));

    gate = clone_object(PELAR_DIR + "lib/gate_in");
    gate->set_door_id("Pelargir_Gate_"+CAP(which));
    gate->set_pass_command(({swhich, which}));
    gate->set_door_name(({"city gate", which+" gate","gate","citygate"}));
    gate->set_other_room(PELAR_DIR + "streets/"+swhich+"_gate_out");
    gate->move(TO);
}

void
init()
{
    ::init();
    add_action("do_knock","knock");
    add_action("do_knock","pound");
}

int
do_knock(string str)
{
    string      vb = QVB;
    NFN(CAP(vb)+" on what?");

    if (str != "gate" && str != "on gate")
        return 0;

    TP->reveal_me(1);

    other_gate = gate->query_other_door();

    if (gate->query_open())
    {
        write("You "+vb+" on the open gate. Stupid, isn't it?\n");
        say(QCTNAME(TP)+" "+vb+"s on the open gate. Stupid, isn't it?\n");
    }
    else
    {
        write("You "+vb+" on the gate.\n");
        say(QCTNAME(TP)+" "+vb+"s on the gate.\n");

        tell_room(TO, "From the room to the east, someone shouts: "
          + "Open the gate, someone wants to leave!\n");
        tell_room(gate->query_other_room(), 
            "You hear a muffled shout from the other side of the gate.\n");

        other_gate->do_unlock_door("You hear something heavy moving on the other side of the gate.\n");
        gate->do_unlock_door("Suddenly, the wooden beam blocking the door starts moving.\n");
        other_gate->do_open_door("The gate opens as the iron doors swing inwards.\n");
        gate->do_open_door("The gate opens as the iron doors swing inwards.\n");
    }
    return 1;
}

void
close_gate() 
{ 
    other_gate = gate->query_other_door();

    if (!gate->query_open())
        return;

    gate->do_close_door("The iron doors swing back to close the gate again.\n");
    other_gate->do_close_door("The iron doors swing back to close the gate again.\n");

    gate->do_lock_door("The beam moves back into position, blocking the gate.\n");
    other_gate->do_lock_door("You hear something heavy moving on the other side of the gate.\n");
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(ob) || !objectp(to))
        return;

    if(!living(ob))
        return;

    if (gate->query_open())
    {
        remove_alarm(close_gate_id);
        close_gate_id = set_alarm(2.0 + rnd() * 2.0, 0.0, close_gate);
    }
}

object  query_gate() { return gate; }


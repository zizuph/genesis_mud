/*
 *	/d/Gondor/pelargir/lib/out_gate.c
 *
 *	Outer city gate for Pelargir
 *
 *	Olorin, June 1995
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/defs.h"

int     close_gate_id;

object  gate,
        other_gate;

void
create_gate(string which)
{
    string  dir,
            sdir;

    switch (which)
    {
        case "north":
            dir = "south";
            sdir = "s";
            break;
        case "south":
            dir = "north";
            sdir = "n";
            break;
    }

    add_item(({"tower", "towers", }), BSN(
        "On each side of the gate, the city wall ends in a "
      + "large round tower. The towers are just little higher than "
      + "the tops of the city wall and were built from the same "
      + "grey stone blocks as the walls. From the top of the towers "
      + "soldiers can easily command the wide plain in front of "
      + "the city walls."));
    add_item(({"wall", "walls", "city wall", "city walls", }), BSN(
        "The city walls of Pelargir tower high above the fields and "
      + "meadows outside the city. They were built from mighty grey "
      + "stone boulders, hewn and fitted together with great care "
      + "and expertise. But in several places there are signs of "
      + "decay. While a few repairs have been made recently, "
      + "they were made with less competence than the original "
      + "construction."));

    add_item("battlements", BSN("The battlements upon the walls "
      + "crenelated walls in front, so that the guards are "
      + "protected from arrows and other missiles."));

    add_item("guards","You do not really see any, but you guess they are there.\n");
    add_item(({"doors","door"}), BSN(
        "The two doors of the gate are made of strong iron, each held "
      + "up by a steel post."));
    add_item(({"post","posts"}), BSN(
        "These steel posts hold the gates open to allow entry into "
      + "the city. They are very sturdy and can hold the gate easily."));

    gate = clone_object(PELAR_DIR + "lib/gate_out");
    gate->set_door_id("Pelargir_Gate_"+CAP(which));
    gate->set_pass_command(({sdir, dir}));
    gate->set_door_name(({"city gate", which+" gate","gate","citygate"}));
    gate->set_other_room(PELAR_DIR + "streets/"+which[0..0]+"_gate_in");
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

        if (tod() == "night")
        {
            tell_room(TO, "From the top of a tower, someone shouts: "
              + "We do not let anyone into the city at night, come back in the morning!\n");
            tell_room(gate->query_other_room(),
                "From the top of a tower, someone shouts: "
              + "We do not let anyone into the city at night, come back in the morning!\n");
        }
        else if (TP->query_prop(PEL_I_DID_ATTACK))
        {
            tell_room(TO, "From the top of a tower, someone shouts: "
              + "Go away, you murdering bastard!\n");
            tell_room(gate->query_other_room(),
                "From the tope of a tower, someone shouts: "
              + "Go away, you murdering bastard!\n");
        }
        else
        {
            tell_room(TO, "From the top of a tower, someone shouts: "
              + "Open the gate, someone wants to enter!\n");
            tell_room(gate->query_other_room(),
                "From the top of a tower, someone shouts: "
              + "Open the gate, someone wants to enter!\n");

            gate->do_unlock_door("You hear something heavy moving on the other side of the gate.\n");
            other_gate->do_unlock_door("Suddenly, the wooden beam blocking the door starts moving.\n");
            gate->do_open_door("The gate opens as the iron doors swing inwards.\n");
            other_gate->do_open_door("The gate opens as the iron doors swing inwards.\n");
        }
    }
    return 1;
}

void close_gate() { gate->query_other_room()->close_gate(); }

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



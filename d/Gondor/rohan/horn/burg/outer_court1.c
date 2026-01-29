/*
 * The do_knock function was taken from Olorin's do_knock in
 * /d/Gondor/morgul/city/i_ngate.c
 *
 */

inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

/* Prototypes */
int close_gate();

object guard1, guard2, guard3, gate, other_gate;

void create_helmsdeep_room()
{
    string location, extraline;

    location = "In the outer courtyard, just inside the great gate. ";
    extraline = "The courtyard stretches out to the south, "+
    	"where it turns west around the inner wall. ";
    extraline = location + LONGDESC1 + extraline;

    set_short_desc("The outer courtyard of the Hornburg");
    set_extra_long(extraline);
    set_inside_keep(1);

    GUARDS;
    WALL;
    TOWER;
    WINDOWS;
    COURTYARD;
    COBBLESTONES;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    BOTH_WALLS;

    add_exit(ROH_DIR + "horn/burg/outer_court2", "south", 0);
    add_exit(ROH_DIR + "horn/burg/outer_court3", "southwest", 0);

    gate = clone_object(ROH_DIR + "horn/doors/great_gate_out");
    gate->move(TO);
    reset_room();
}

public void
reset_room()
{
    close_gate();

    guard1 = clone_npc(guard1, (ROH_DIR + "horn/npc/g_guard"));
    guard2 = clone_npc(guard2, (ROH_DIR + "horn/npc/g_guard"));
    guard3 = clone_npc(guard3, (ROH_DIR + "horn/npc/g_guard"));

    guard3->team_join(guard1);
    guard3->team_join(guard2);
    guard3->set_random_move(15);
    guard3->set_restrain_path(ROH_DIR + "horn/burg/");
}

void init()
{
    ::init();
    add_action("do_knock", "knock");
    add_action("do_knock", "pound");
}

int do_knock(string str)
{
    object other_room;
    string vb = QVB;
 
    NF(CAP(vb)+" on what?\n");
    if (str != "gate" && str != "on gate")
        return 0;

    TP->reveal_me(1);

    other_gate = gate->query_other_door();
    other_room = ENV(other_gate);
      
    if(gate->query_open())
    {
        TP->catch_msg("You "+vb+" on the open gate. Stupid, isn't it?\n");
        say(QCTNAME(TP) + " "+vb+"s on the open gate. Stupid, isn't it?\n");
        return 1;
    }
    TP->catch_msg("You "+vb+" on the great gate.\n");
    say(QCTNAME(TP) + " "+vb+"s on the great gate.\n");

    if ( !sizeof(filter(all_inventory(other_room), &->id("guard"))) )
	/* no one there to answer the knock */
	return 1;

    if(!IS_EVIL(TP))
    {
        tell_room(TO, BSN("From the top of the walls, someone shouts: "+
        "Open the gate!"));
        tell_room(other_room, BSN("From the top of the walls, "+
        "someone shouts: Open the gate!"));

        other_gate->do_unlock_door(BSN("You hear something heavy moving "+
        "on the other side of the gate."));
        gate->do_unlock_door(BSN("Some guards remove the beam across the "+
        "gate."));
        other_gate->do_open_door(BSN("The great gate opens as someone pushes "+
        "the gate."));
        gate->do_open_door(BSN("The great gate opens as the guards "+
        "push the gate."));
    }
    else
    {
        tell_room(TO, BSN("From the top of the walls, someone shouts: "+
        "Alarm! Enemies inside the gate!"));
        tell_room(other_room, BSN("From the top of the walls, "+
        "someone shouts: Alarm! Enemies inside the gate!"));
    }
    return 1;
}

public void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!ob || !to)
        return;

    if(!living(ob))
        return;

    if(gate->query_open())
    {
  /*       remove_alarm(close_gate()); */
        set_alarm(3.0, 0.0, "close_gate");
    }
}

int close_gate() 
{ 
    other_gate = gate->query_other_door();

    if(!gate->query_open())
        return 0;

    gate->do_close_door("The great gate closes as someone pulls the gate.\n");
    other_gate->do_close_door(BSN("The great gate closes as someone pulls "+
    "the gate."));
    gate->do_lock_door("Some guards put back the beam across the gate.\n");
    other_gate->do_lock_door(BSN("You hear something heavy moving on the "+
    "other side of the gate."));
    return 1;
}

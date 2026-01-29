/*
 * The do_knock function was taken from Olorin's do_knock in
 * /d/Gondor/morgul/city/o_ngate.c
 *
 */

inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

object sentinel, gate, other_gate;

/* Prototypes */
void reset_room();
int close_gate();

void
create_helmsdeep_room()
{
    set_short_desc("Outside the great gate of the keep");
    set_extra_long("Outside the great gates of the keep. "+
    "Below, over the brink of the Rock, the rocky Deeping-stream "+
    "winds its course. A steep ramp goes down to the northeast, "+
    "and a small path goes west here. ");

    set_track_dir1("northeast");
    set_track_dir2("west");

    add_item(({ "ground", "track", "tracks", "footprints" }), find_tracks);
    BRINK;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("ramp", "A steep ramp leads down to the causeway.\n");
    add_item(({"rock"}), "The keep is built upon the Rock.\n");
    add_item("stream", "The Deeping-stream flows gently from the wall to "+
    "the dike.\n");
    add_item("path", "A rocky path winds close to the brink.\n");

    add_exit(ROH_DIR + "horn/gorge/ramp", "northeast", 0);
    add_exit(ROH_DIR + "horn/gorge/n_path1", "west", 0);

    gate = clone_object(ROH_DIR + "horn/doors/great_gate_in");
    gate->move(TO);
    reset_room();
}

void
reset_room()
{
    sentinel = clone_npc(sentinel, (ROH_DIR + "horn/npc/g_sentinel"));
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
        say(QCTNAME(TP)+" "+vb+"s on the open gate. Stupid, isn't it?\n");
        return 1;
    }
    TP->catch_msg("You "+vb+" on the great gate.\n");
    say(QCTNAME(TP)+" "+vb+"s on the great gate.\n");

    /* be generous about opening ... guard here or guard there will
     * suffice
     */
    if ( !present("guard", TO) &&
    !sizeof(filter(all_inventory(other_room), &->id("guard"))) )
	return 1;


    if(!IS_EVIL(TP))
    {
        tell_room(TO, BSN("From the top of the walls, someone shouts: "+
        "Open the gate!"));
        tell_room(other_room, BSN("From the top of the walls, "+
        "someone shouts: Open the gate!"));

        gate->do_unlock_door(BSN("You hear something heavy moving on the "+
        "other side of the gate."));
        other_gate->do_unlock_door(BSN("Some guards remove the beam "+
        "across the gate."));
        gate->do_open_door("The great gate opens as someone pushes the "+
        "gate.\n");
        other_gate->do_open_door("The great gate opens as the guards "+
        "push the gate.\n");
        set_alarm(12.0, 0.0, "close_gate");
    }
    else
    {
        tell_room(TO, BSN("From the top of the walls, someone shouts: "+
        "Alarm! Enemies outside the gate!"));
        tell_room(other_room, BSN("From the top of the walls, "+
        "someone shouts: Alarm! Enemies outside the gate!"));
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
 /*       remove_alarm("close_gate");     */
        set_alarm(3.0, 0.0, "close_gate");
    }
}

int close_gate() { gate->query_other_room()->close_gate(); }

void
close_gate_to_stop_invaders(object one_enemy)
{
    one_enemy->catch_msg(BSN("When you try to enter the gate, you hear a "+
    	"shout from the top of the wall."));
    tell_room(TO, BSN("When " + QTNAME(one_enemy) + " tries to enter the "+
    	"gate, you hear a shout from the top of the wall."), one_enemy);
    	tell_room(TO, "Someone shouts: Close the gate! Invaders!\n");
    close_gate();
}

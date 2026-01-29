/*
 * Victory room
 */
#pragma strict_types

inherit "/std/room";
inherit "/d/Avenir/inherit/quest";

#include "defs.h"
#include <macros.h>

public object winner, akram;
public int act_index, act_alarm = 0;


public string
door_desc(void)
{
    if (member_array("east", query_exit_cmds()) == -1)
	return "";

    return " An opening leads out to the east.";
}

public void
create_room(void)
{
    set_short("place of resting");
    set_long("A cold and barren room, the floor and walls are made from "+
	"soft, vaguely luminous granite.@@door_desc@@ Soft whispers can "+
	"be heard all around, the cries of the dead and forgotten, lives "+
	"lived rich in the halo of the shadows, dedicated to flames.\n");
}

private void
stop_acting(void)
{
    remove_alarm(act_alarm);
    act_alarm = act_index = winner = 0;
}

private int
next_action(int index)
{
    string name;

    if (!objectp(winner) || !query_interactive(winner) || !present(winner))
	return 0;

    name = winner->query_name();

    switch(index)
    {
        case 0:
            return 5;
        case 1:
            tell_room(TO, "The whispers grow to a deafening roar.\n");
            return 5;
        case 2:
            tell_room(TO, "All of a sudden, the roar subsides, leaving "+
		"the room veiled in the silence of a tomb.\n");
            return 4;
        case 3:
	    akram = clone_object(AKRAM);
            akram->move_living("M", TO);

	    if (!present(akram))
		return 0;

	    tell_room(TO, QCTNAME(akram) + " rises from the dust.\n");
	    return 2;
        case 4:
	    akram->command("present me");
	    return 4;
       case 5:
	    akram->command("say " + name + ", you have followed the "+
		"path of the Shadow Warrior to its apex.");
	    return 5;
       case 6:
	    akram->command("say You have proven your self as a warrior "+
		"of great strength and cunning.");
	    return 5;
       case 7:
	    akram->command("say The Flame has chosen you to enter the "+
		"ranks of the Elite, and you have followed well the course "+
		"laid out before you.");
	    return 5;
       case 8:
	    akram->command("say Beneath the symbol, you may enter into "+
		"the Darkness and walk with Beauty.");
	    return 5;
       case 9:
	    akram->command("say Walk with the Shadows, " + name + ".");
	    return 5;
       case 10:
	    winner->catch_msg(QCTNAME(akram) + " touches you lightly on "+
		"the forehead.\n");
	    reward_quest("Tomb of Akram", winner, GUILD_GROUP, TRAINING, GURU_EXP);
	    return 3;
       case 11:
	    if (akram)
		tell_room(TO, QCTNAME(akram) + " returns to dust.\n");
	    akram->remove_object();
	    return 6;
        case 12:
	    winner->catch_tell("The room fades to dust, you feel drawn "+
		"by ineffiable forces.\n");
	    winner->move_living("X", FALSE_TOMB);
	    /* reset the winner */
	    winner = act_index = 0;
	    return 2;
        default:
	    return 0;
     }
}

private void
do_act(void)
{
    int next;

    act_alarm = 0;

    if (!present(winner))
    {
        stop_acting();
        return;
    }

    next = next_action(act_index++);

    if (!next)
    {
       stop_acting();
       return;
    }

    act_alarm = set_alarm(itof(next), 0.0, do_act);
}

public void
start_acting(object who)
{
    if (act_alarm || objectp(winner))
       return;

    winner = who;
    act_alarm = set_alarm(1.0, 0.0, do_act);
}

public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);
    if (VALID_GURU(to) == 1)
       start_acting(to);
}

public void
leave_inv(object to, object dest)
{
    ::leave_inv(to, dest);

    if (winner == to)
    {
        winner = 0;
        stop_acting();
    }
}

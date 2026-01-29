inherit "/std/room";

#include "defs.h"
#include "/sys/tasks.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

int trap_open, hatch_open;

/* Prototypes */
void fall_in_trap(object ob);
void reset_room();

void
create_room()
{
    set_short("First floor of northern tower");
    set_long("@@room_long");

    add_item("stairs", "@@stairs_long");
    add_item("trapdoor", "@@trapdoor_long");
    add_item(({"hatch","small hatch"}), "@@hatch_long");

    /* Climbing the stairs is tiresome... */
    add_exit(STAND_DIR + "tower13", "up", "@@check_trap", 4);
    add_exit(STAND_DIR + "tower11", "down", 0, 4);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    reset_room();
}

void
reset_room()
{
    trap_open = 0;
    hatch_open = 0;
}

void
init()
{
    ::init();
    add_action("do_open", "open");
    add_action("do_cut", "cut");
    add_action("do_disarm", "disarm");
}

string
room_long()
{
    string str;
    object tp;

    str = "You have reached the first floor of the northern tower. "
	+ "It is quite dark here, and the air is damp. The tower "
	+ "has not been used for a very long time. Circular stairs "
	+ "lead up and down.";

    tp = this_player();

    if (trap_open)
    {
	str += " In the middle of the stairs going up is an open "
	     + "trap door.";
    }
    else
    {
	if (tp->resolve_task(TASK_ROUTINE, ({ SS_AWARENESS, SS_FR_TRAP })) > 0)
	{
	    str += " You notice that something is wrong with the stairs "
		 + "leading up.";
	}
    }
    if (hatch_open)
    {
	str += " There is a small niche in the wall.";
    }
    return break_string(str + "\n", 70);
}

string
stairs_long()
{
    object tp;
    string str;

    str = "The broad wooden staircase winds upwards to the second floor, "
	+ "and downwards to the ground level following the wall of the "
        + "tower. ";

    tp = this_player();

    if (tp->resolve_task(TASK_SIMPLE, ({ SS_AWARENESS, SS_FR_TRAP })) > 0)
    {
        str += "The stairs have been trapped. Looking more carefully "
	     + "around, you spot a hardly visible, small hatch in "
	     + "the wall.\n";
    }
    else
    {
	str += "Someone has tampered with the stairs. You cannot "
	     + "see what is wrong, though.\n";
    }
    return break_string(str, 70);
}

string
hatch_long()
{
    string str;

    str = "There is a very well hidden hatch on the wall. ";
    if (hatch_open)
    {
	str += "It has been opened to reveal the niche behind it. "
	     + "The nice has a thin line in it, which probably will "
	     + "trigger a trap. Unfortunately the thin line is "
	     + "surrounded by sharp edges. You will need steel nerves "
             + "and a steady hand in order to not wound yourself while "
             + "cutting the line with something.\n";
    }
    else
	str += "Perhaps you should open it, to see what is behind it?\n";

    return break_string(str, 70);
}

string
trapdoor_long()
{
    string str;
    object tp;

    if (!trap_open)
	str = "You find no trapdoor.\n";
    else
	str = "There is an open trapdoor in the middle of the stairs. "
	    + "Looking down in it, you see a pit furnished with pointed "
	    + "sticks. If you are careful, you can walk around it.\n";

    return break_string(str, 70);
}

int
check_trap()
{
    if (trap_open)
    {
	write("You carefully walk around the trap door.\n");
	return 0;
    }
    write("As you step forward you set of a trap!\n");
    set_alarm(1.0,0.0,&fall_in_trap(),this_player());
    return 1;
}

void
fall_in_trap(object ob)
{
    int hp;

    if (!ob)
	return;

    ob->catch_msg("You set off a trap, and a trap door opens under you!\n");
    tell_room(this_object(), QCTNAME(ob) + " set off a trap and falls "
	    + "down!\n", ob);

    trap_open = 1;
    
    ob->move_living("M", STAND_DIR + "pit");

    /* Don't kill, but hurt the player */
    if ((hp = ob->query_hp()) > 4)
	ob->reduce_hit_point(hp / 2);
}

int
do_open(string str)
{
    notify_fail("Open what?\n");
    if (!str)
	return 0;

    if (str != "hatch" && str != "small hatch")
	return 0;

    write("You carefully open the hatch.\n");
    say(QCTNAME(this_player()) + " carefully opens a hatch.\n");

    hatch_open = 1;
    return 1;
}

int
do_disarm(string str)
{
    if (str != "trap")
	return 0;
    write("How are you planning to disarm the trap?\n");
    return 1;
}

int
do_cut(string str)
{
    string item, what;
    object *obs, tp;
    int success, sk;

    if (trap_open || !hatch_open)
	return 0;

    notify_fail("Cut what with what?\n");
    if (!str)
	return 0;

    str = lower_case(str);
    if (sscanf(str, "%s with %s", what, item) != 2)
	return 0;

    if (what != "line" && str != "thin line")
    {
	notify_fail("You cannot cut that!\n");
	return 0;
    }

    tp = this_player();

    obs = FIND_STR_IN_OBJECT(item, tp);

    if (sizeof(obs) == 0)
    {
	notify_fail("You don't have " + LANG_ADDART(item) + ".\n");
	return 0;
    }

    if (sizeof(obs) > 1)
    {
	notify_fail("Could you be more specific?\n");
	return 0;
    }

    /* Is the item a weapon? */
    if (function_exists("create_object", obs[0]) != "/std/weapon" ||
	obs[0]->query_wt() != W_KNIFE)
    {
	notify_fail("A knife-like weapon would be best suited for the job.\n");
	return 0;
    }

    /* Finally try to cut the line */
    success = tp->resolve_task(TASK_ROUTINE,
		     ({ SKILL_AVG, SS_DEX, SS_FR_TRAP, SKILL_END }));

    if (success < 0)
    {
	write("You tremble too much and hurt yourself whilst trying to cut the line.\n");
	say(QCTNAME(tp) + " tries to disarm a trap, but hurts " +
	    tp->query_objective() + "self.\n");

	/* Don't kill, but hurt the player */
	if (tp->query_hp() > 5)
	    tp->reduce_hit_point(5);
    }
    else
    {
	write("You successfully disarm the trap.\n");
	say(QCTNAME(tp) + " successfully disarms a trap.\n");
	tell_room(this_object(), "A trapdoor falls open.\n");

	trap_open = 1;
	tp->add_exp(10,0);	/* Give a tiny bit of quest_exp */

	/*
	 * If you were not skilled in finding and
	 * removing traps at all, you learned a bit.
	 */
	if ((sk = tp->query_skill(SS_FR_TRAP)) < 2)
	    tp->set_skill(SS_FR_TRAP, sk + 1);
    }
    return 1;
}

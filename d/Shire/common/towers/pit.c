inherit "/std/room";

#include "defs.h"
#include "/sys/tasks.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

void
create_room()
{
    set_short("Trap");
    set_long(break_string(
	  "You have fallen via a trap door into a pit. The fall has "
	+ "seriously hurt you, because of all the pointy sticks that "
	+ "have been attached to the wall. Around you, you see the "
	+ "skeletons of adventurers who were not that lucky.\n", 70));

    add_item(({"sticks","stick"}), break_string(
	  "The strong, pointy sticks have been set into the wall "
	+ "to kill the people that fall down here. You were lucky "
	+ "not to be pierced to death by them.\n", 70));

    add_item(({"skeletons", "skeleton"}), break_string(
	  "The skeletons stare at you with their empty gaze. The "
	+ "expression of the excruciating pain is still on their "
	+ "faces.\n", 70));
}

void
init()
{
    ::init();
    add_action("do_climb", "climb");
}

int
do_climb(string str)
{
    object tp;
    int sk, success;

    notify_fail("Climb whereto?\n");
    if (!str)
	return 0;

    str = lower_case(str);	
    if (str != "out" && str != "up")
	return 0;

    tp = this_player();

    /* Let's see how good we are at it... */
    success = tp->resolve_task(TASK_ROUTINE,
			({ SKILL_AVG, SS_DEX, SS_CLIMB, SKILL_END }));

    if (success <= 0)
    {
	write("You try to climb out of the pit, but fall down again.\n"
	    + "You hurt yourself while falling down.\n");
	say(QCTNAME(tp) + " tries to climb out of the pit.\n"
	  + tp->query_pronoun() + " falls down again and hurts "
	  + tp->query_objective() + "self.\n");

	/* Don't let the player die */
	if (tp->query_hp() > 5)
	    tp->reduce_hit_point(5);
    }
    else
    {
	/*
	 * Wow! Managed to climb out without any climbing skill!
	 * The player obviously has learned to climb a bit.
	 */
	if ((sk = tp->query_skill(SS_CLIMB)) < 5)
	    tp->set_skill(SS_CLIMB, sk + 1);

	write("You climb out of the pit, carefully avoiding the sticks.\n");
	say(QCTNAME(tp) + " carefully climbs out of the pit.\n");
	tp->move_living("M", STAND_DIR + "tower12");
    }
    return 1;
}

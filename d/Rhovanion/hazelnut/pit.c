inherit "/std/room";

#include <stdproperties.h>
#include <tasks.h>

void
create_room()
{
    set_short("In pit");
    set_long("You are at the bottom of a huge pit.\n");

    add_prop(ROOM_I_INSIDE, 1);
}

void
init()
{
    ::init();
    add_action("do_climb", "climb");
}

int
do_climb(string arg)
{
    int success;

    if (arg != "wall") {
	notify_fail("Climb what?\n");
	return 0;
    }
    success = this_player()->resolve_task(TASK_ROUTINE,
					  ({ SKILL_WEIGHT,  50, TS_DEX,
    					     SKILL_WEIGHT, 200, SS_CLIMB }) );
    if (success > 0) {
	write("You start to scale the wall.\n");
	call_out("climb_on", 20, this_player());
	return 1;
    }
    notify_fail("You try to climb the wall, but can't find any footing.\n");
    return 0;
}

void
climb_on(object ob)
{
    int success;

    if (!ob || !present(ob))
	return;

    success = ob->resolve_task(TASK_ROUTINE,
					  ({ SKILL_WEIGHT,  50, TS_DEX,
    					     SKILL_WEIGHT, 200, SS_CLIMB }) );

    if (success < 1) {
	ob->catch_msg("You lose your footing and fall down into the pit.\n");
	tell_room(this_object(), QCTNAME(ob) + " looses " +
		  ob->query_possessive() + " footing and falls back into the "+
		  "pit.\n", ob);
    }
    ob->move_living("climbing the wall", THIS_DIR + "ledge1", 1);
}

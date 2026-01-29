/*
 * An inheritable file used for quick distribution of guard npcs
 */

#include "local.h"

static int gGuard_num;
static object *gGuards;

void
set_guards(int num)
{
    gGuard_num = num;
    gGuards = ({});
}

object
configure_guard_hook(object guard) 
{
    return guard;
}

void
reset_room()
{
    int i;
    object guard;

    gGuards -= ({0});
    if (!gGuard_num || sizeof(gGuards) >= gGuard_num)
	return;

    i = -1;
    i = i + sizeof(gGuards);
    while(++i < gGuard_num)
    {
	setuid(); seteuid(getuid());
	if (!random(3))
	    guard = clone_object(NPC_DIR + "dwarf_guard");
	else
	    guard = clone_object(NPC_DIR + "human_guard");

	guard = configure_guard_hook(guard);
	guard->move_living("void", this_object());
	gGuards += ({guard});
    }
}

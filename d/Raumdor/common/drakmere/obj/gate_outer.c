#pragma strict types
#include "defs.h"
inherit DRAKMERE_GATE;

void
create_gates()
{
    ::create_gates();
    set_lock_desc("You cannot see any lock on this side.\n");
    set_gates_desc("The gates are quite tall and made of dark iron, embedded " +
            "within the tall stone gatehouse. Its surface is smooth, aside " +
            "from the cross rails.\n");
}

void
autoclose(float delay)
{
    load_other_door();
    other_door->autoclose(delay);
}

void
guard_unlock()
{
    load_other_door();
    other_door->guard_unlock();
}

string
standard_fail_open2()
{
    return "They are secured and cannot be opened from this side.\n";
}



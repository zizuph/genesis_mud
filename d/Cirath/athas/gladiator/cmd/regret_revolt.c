#include "defs.h"

public int
_cmd_regret_revolt()
{
    string name = this_player()->query_real_name();

    if(!MANAGER->query_revolter(name))
    {
        return notify_fail("But you aren't revolutionary!\n");
    }

    MANAGER->remove_revolter(name);
    write("You are no longer revolutionary.\n");
    say(QCTNAME(TP) + " isn't revolutionary anymore.\n");
    return 1;
}

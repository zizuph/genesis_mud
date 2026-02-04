#pragma strict_types

#include "../defs.h"

void
register_gkeep_kill(object killer)
{
    object tracker = present(GKEEP_KILL_TRACKER, killer);

    if (!objectp(tracker)) {
        setuid();
        seteuid(getuid());
        tracker = clone_object(GKEEP_OBJ + "kill_tracker");
        tracker->move(killer, 1);
    }

    tracker->add_kill();
}

#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m2", "northwest");
    add_exit("/d/Calia/argos/nwterr/rooms/wfpath6", "southwest");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob) && !present(QUEST_TRACKER_NAME, ob))
    {
        seteuid(getuid());
        clone_object(OBJ + "quest_tracker")->move(ob,1);
    }
}

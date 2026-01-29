inherit "/std/room";

#include "../ctower.h"
#include <stdproperties.h>

void
create_ctower_room()
{
}

void
register_reset()
{
    setuid();
    seteuid(getuid());

    CTOWER_MANAGER->register_reset(this_object());
}

nomask void
create_room()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    if (function_exists("ctower_reset", this_object()))
    {
        register_reset();
    }

    create_ctower_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob) || ob->query_npc())
    {
        return;
    }
        
    if (!from->query_inside_ctower())
    {
    	setuid();
    	seteuid(getuid());

        CTOWER_MANAGER->enter_tower(ob);
    }
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!to || (interactive(ob) &&
        !to->query_inside_ctower()))
    {
        CTOWER_MANAGER->leave_tower(ob);
    }
}

int
query_inside_ctower()
{
    return 1;
}

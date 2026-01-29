#include "../ctower.h"

#include <macros.h>
#include <stdproperties.h>

void
remove_ctower_object()
{
    tell_room(environment(this_object()), "The " + 
        QSHORT(this_object()) + " fades into nothingness.\n");

    this_object()->remove_object();
}

void
ctower_reset()
{
    remove_ctower_object();
}

void
create_ctower_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    this_object()->enable_reset();

    this_object()->add_prop(OBJ_M_NO_STEAL, 1);

    setuid();
    seteuid(getuid());
    CTOWER_MANAGER->register_reset(this_object());
}

void
reset_ctower_object()
{
    int i;
    object *envs = all_inventory(this_object());

    for (i = sizeof(envs); i >= 0; i--)
    {
        if (living(envs[i]) && !interactive(envs[i]))
	{
            return;
	}

        if (envs[i]->query_prop(ROOM_I_IS) && 
            envs[i]->query_inside_ctower())
	{
            return;
	}
    }

    remove_ctower_object();
}

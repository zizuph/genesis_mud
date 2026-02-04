inherit "/d/Terel/cedric/guild/Obj/fork";

#include "../guild_defs.h"
#include <stdproperties.h>

string
query_fork_colour()
{
    return "platinum";
}

int
query_chance_to_break()
{
    return 2;
}

mixed
no_drop()
{
    if (MEMBER(this_player()))
    {
        return "You decide against dropping the platinum tuning fork.\n";
    }

    return 0;
}

void
create_fork()
{
    add_prop(OBJ_I_VALUE, 28800);
    // add_prop(OBJ_M_NO_DROP, no_drop);
}

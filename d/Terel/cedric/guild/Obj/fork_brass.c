inherit "/d/Terel/cedric/guild/Obj/fork";

#include <stdproperties.h>

string
query_fork_colour()
{
    return "brass";
}

int
query_chance_to_break()
{
    return 25;
}

void
create_fork()
{
    add_prop(OBJ_I_VALUE, 2304);
}

inherit "/d/Terel/cedric/guild/Obj/fork";

#include <stdproperties.h>

string
query_fork_colour()
{
    return "golden";
}

int
query_chance_to_break()
{
    return 5;
}

void
create_fork()
{
    add_prop(OBJ_I_VALUE, 11520);
}

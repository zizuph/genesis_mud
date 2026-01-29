inherit "/d/Emerald/std/room";

#include "defs.h"

static int load_clone_handler = 0;

public void
create_monastery_room()
{
}

nomask void
create_emerald_room()
{
    create_monastery_room();
    if (load_clone_handler)
    {
         set_clone_handler(MONASTERY_DIR + "clone_handler");
    }
}

varargs object
get_door(string dest)
{
    setuid();
    seteuid(getuid());
    return clone_object(MONASTERY_OBJ + "monastery_door");
}

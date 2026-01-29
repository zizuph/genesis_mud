inherit "/d/Emerald/std/stddoor";

#include <stdproperties.h>

void
create_emerald_door()
{
}

nomask void
create_door()
{
    create_emerald_door();
}

public string
query_other_door_id()
{
    return file_name(environment());
}

public object
get_default_lock()
{
    setuid();
    seteuid(getuid());
    return clone_object("/d/Emerald/std/lock");
}

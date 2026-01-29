inherit "/d/Emerald/telberin/telberin_room";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

public void add_building_exit(mixed to);

public void
create_telberin_building()
{
}

nomask public void
create_telberin_room()
{
    string *locations;

    set_short("building");

    add_prop(ROOM_I_INSIDE, 1);

    setuid();
    seteuid(getuid());
    
#if defined(USE_TELBERIN_BUILDING_MANAGER) && USE_TELBERIN_BUILDING_MANAGER
    if (sizeof(locations =
        TELBERIN_BUILDING_MANAGER->query_building_locations(this_object())))
    {
        map(locations, add_building_exit);
    }
#endif

    create_telberin_building();
}

public mixed
query_location_ids()
{
    return "building";
}

public mixed
query_location_closed()
{
    return "The " + short() + " is closed.\n";
}

public mixed
query_location_desc()
{
    return 0;
}

/*
 * This needs to be improved so that it handles multiple exits better
 */
public void
add_building_exit(mixed to)
{
    mixed exits = query_exit();
    int i;

    if (exits && (sizeof(exits) > 0))
    {
        for (i = 0; i < sizeof(exits); i += 3)
        {
//          if (exits[i][1] == "out")
            if (exits[i + 1] == "out")
            {
                 return;
            }
        }
    }

    if (objectp(to))
    {
        to = MASTER_OB(to);
    }

    add_exit(to, "out");
}


/*
 * /d/Emerald/telberin/building_manager.c
 *
 * This object serves a few purposes.  First, it decouples buildings (shops,
 * pubs, banks, etc.) from the street rooms, minimizing the code changes
 * necessary to add/move/remove buildings.  It also creates a central
 * registry for all the buildings in the city, which makes a handy reference
 * for npcs giving directions, making dynamic maps, etc.
 */

#pragma strict_types
#pragma no_clone
#pragma no_inherit
#pragma no_shadow

#include "defs.h"
#include <macros.h>

#define BUILDING_SAVE_FILE (TELBERIN_LOG_DIR + "building_save")

// Making it a room makes it easy to access management commands
inherit "/d/Emerald/std/room";

mapping data = ([]);

public void
create_emerald_room()
{
    setuid();
    seteuid(getuid());

    set_long("This is the Telberin building manager.  Commands:\n" +
             "\tadd <building> <location>\n" +
             "\tremove <building> [<location>]\n" +
             "\tlist [<building | location>]\n");

    data = restore_map(BUILDING_SAVE_FILE);
}

public void
save()
{
    save_map(data, BUILDING_SAVE_FILE);
}

public void
add_building(mixed building, mixed to_room)
{
    string *arr;

    if (objectp(building))
    {
        building = MASTER_OB(building);
    }
    else if (!stringp(building))
    {
        return;
    }

    if (objectp(to_room))
    {
        to_room = MASTER_OB(to_room);
    }
    else if (!stringp(to_room))
    {
        return;
    }

    arr = data[building];
    if (!arr)
    {
        data[building] = ({ to_room });
    }
    else
    {
        data[building] = arr + ({ to_room });
    }

    save();
}

varargs public string *
query_buildings(mixed room)
{
    string *buildings = m_indices(data);

    if (room)
    {
        int i;

        if (objectp(room))
        {
            room = MASTER_OB(room);
        }
        else if (!stringp(room))
        {
            return ({});
        }

        while (i < sizeof(buildings))
        {
            if (member_array(room, data[buildings[i]]) >= 0)
            {
                i++;
            }
            else
            {
                buildings = exclude_array(buildings, i, i);
            }
        }

        return buildings;
    }

    return m_indices(data);
}

public string *
query_building_locations(mixed building)
{
    if (objectp(building))
    {
        building = MASTER_OB(building);
    }

    return data[building];
}

public int
add(string str)
{
    string building, location;

    if (!strlen(str) || (sscanf(str, "%s %s", building, location) != 2))
    {
        notify_fail("add <building> <location>.\n");
        return 0;
    }

    add_building(building, location);    
    return 1;
}

public int
remove(string str)
{
    string building, location;

    if (strlen(str))
    {
        if (sscanf(str, "%s %s", building, location) != 2)
        {
            building = str;
	}
    }
    else
    {
        notify_fail("remove <building> [<location>]\n");
        return 0;
    }

    if (location)
    {
        data[building] = (string *)data[building] - ({ location });
    }
    else
    {
        data = m_delete(data, building);
    }

    save();
    return 1;
}

public int
list(string str)
{
    dump_array(data);
    return 1;
}

public void
init()
{
    ::init();
    add_action(add, "add");
    add_action(remove, "remove");
    add_action(list, "list");
}

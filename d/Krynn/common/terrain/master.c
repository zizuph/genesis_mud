inherit "/std/room";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include "/d/Krynn/common/terrain/terrain.h"

string *gUsers = ({});
mapping gMap = ([]);

create_room()
{
    setuid();
    seteuid(getuid());

    set_short("simple room");
    set_long("A simple room.\n");

    restore_object("/d/Krynn/common/terrain/terrain_data");
}

public void
save_master()
{
    setuid();
    seteuid(getuid());

    save_object("/d/Krynn/common/terrain/terrain_data");
}

public int
check_user(string name)
{
    if (member_array(name, gUsers) >= 0)
        return 1;

    return 0;
}

public void
add_user(string name)
{
    name = lower_case(name);

    if (check_user(name))
        return;

    gUsers += ({ name });
}

public void
remove_user(string name)
{
    name = lower_case(name);

    if (!check_user(name))
        return;

    gUsers -= ({ name });
}

public int
valid_terrain(string terrain)
{
    if (member_array(terrain, m_indexes(TERRAIN_MAP)) >= 0)
        return 1;

    return 0;
}

public int
add_terrain_prop(string terrain, string file)
{
    mixed terr = gMap[file];

    if (pointerp(terr))
    {
        if (member_array(TERRAIN_MAP[terrain], terr) >= 0)
        {
            save_master();
            return 1;
        }
        else
        {
            gMap[file] += ({ TERRAIN_MAP[terrain] });
	    save_master();
            return 1;
        }
    }
    gMap[file] = ({ TERRAIN_MAP[terrain] });
    save_master();
    return 1;
}

public int
remove_terrain_prop(string terrain, string file)
{
    mixed terr = gMap[file];

    if (pointerp(terr))
    {
        if (member_array(TERRAIN_MAP[terrain], terr) >= 0)
        {
            gMap[file] -= ({ TERRAIN_MAP[terrain] });

            save_master();
            return 1;
        }
        else
            return 0;
    }

    return 0;
}

public mixed
query_room_terrain(string file)
{
    mixed terr = gMap[file];

    if (pointerp(terr))
        return terr;
    else
        return ({});    
}

public string*
query_terrain()
{
    return m_indexes(TERRAIN_MAP);
}


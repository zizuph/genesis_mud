#pragma no_inherit
#pragma no_clone
#pragma no_shadow
#pragma strict_types

#include "defs.h"

static mapping direction_map = ([]);

public nomask void
create()
{
    string f, *lines, *parts, *destinations, room;
    int i, j;

    setuid();
    seteuid(getuid());
    f = read_file(DOCK_DIR + "npc_directions");

    lines = explode(f, "\n");
    for (i = 0; i < sizeof(lines); i++)
    {
        if (lines[i][0] == '#')
        {
            // This line is a comment.  Skip it.
            continue;
        }

        if (!sizeof(destinations))
        {
            // The first non-comment line should be the list of desinations
            destinations = explode(lines[i], "\t") - ({ "" });
            continue;
        }

        parts = explode(lines[i], "\t");
        room = parts[0];
        direction_map[room] = ([]);
        for (j = 1; j < sizeof(parts); j++)
        {
            if (!strlen(parts[j]))
            {
                continue;
            }

            direction_map[room][destinations[j - 1]] = parts[j];
        }
    }
}

public string
query_next_room(object for_whom, string destination)
{
    object env;
    string room;
    mapping m;

    env = environment(for_whom);
    if (!env)
    {
        return 0;
    }

    room = file_name(env);
    sscanf(room, DOCK_DIR + "%s", room);
    
    m = direction_map[room];

    if (!mappingp(m))
    {
        return 0;
    }

    return m[destination];
}

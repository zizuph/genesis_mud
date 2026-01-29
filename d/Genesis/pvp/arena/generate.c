inherit "/std/room";
#include "../defs.h"

void
create_room()
{
}


int
generate_map()
{
    string   arena_map_file = read_file(ARENA_DIR + "arena_map.txt");
    string   newfile = "/d/Genesis/open/MAP_FILES/arena_map.txt";
    int      rows = 21;
    int      columns = 39;
    int      i;
    int      n;

    setuid();
    seteuid(getuid());

    write_file(newfile, "main\n::MAPDATA::\n");

    for (i = 1; i <= rows; i++)
    {
        for (n = 1; n <= columns; n++)
        {
            write_file(newfile, i+"-"+n +" "+ ((n*2)-1)+" "+ (i-1)+" main\n");
        }
    }

    write_file(newfile, "main\n::MAPDATA::\n");

    write_file(newfile, arena_map_file);

    return 1;
}

    
public int
generate_rooms(string arg)
{
    string   arena_map_file = read_file(ARENA_ROOM_DIR + "1-1.c");
    string   newfile;
    int      rows = 21;
    int      columns = 39;
    int      i;
    int      n;

    setuid();
    seteuid(getuid());

    for (i = 1; i <= rows; i++)
    {
        for (n = 1; n <= columns; n++)
        {
            newfile = ARENA_ROOM_DIR + i + "-" + n + ".c";

            write_file(newfile, arena_map_file);
        }
    }

    return 1;
}


void
init()
{
    add_action(generate_map, "g_map");
    add_action(generate_rooms, "g_rooms");

    ::init();
}

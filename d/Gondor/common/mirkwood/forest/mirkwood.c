/*
 * /d/Gondor/common/mirkwood/forest/mirkwood.c
 * Created by Milan
 *
 * This file is to be inherited by all Mirkwood rooms.
 */
#pragma save_binary
#pragma strict_types
inherit "/d/Gondor/common/mirkwood/map_serv";
inherit "/d/Gondor/common/lib/herbsearch";
#include "/d/Gondor/common/lib/time.h"
#include "/d/Gondor/defs.h"

public nomask string
query_file_with_map()
{
    return "/d/Gondor/common/mirkwood/forest/mirk_map";
}

public nomask string
time_of_day()
{
    return tod();
}

public int
is_room(string arg)
{
    if ((arg == "x") || (arg == "P") || (arg == "s") || (arg == "C") ||
        (arg == "b") || (arg == "E") || (arg == "T") || (arg == "p") ||
        (arg == "M"))
	return 1;
    return 0;
}



/*
 * /d/Rhovanion/common/mirkwood/mirkwood.c
 * Created by Milan
 *
 * This file is to be inherited by all Mirkwood rooms.
 */
#pragma save_binary
#pragma strict_types
inherit "/d/Rhovanion/lib/map_serv";
inherit "/d/Gondor/common/lib/herbsearch";
#include "/d/Gondor/common/lib/time.h"
#include "/d/Rhovanion/defs.h"

public nomask string
query_file_with_map()
{
    return MIRK_DIR + "mirk_map";
}

public nomask string
time_of_day()
{
    return "/d/Gondor/elessar/lib/clock"->query_time_of_day();
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



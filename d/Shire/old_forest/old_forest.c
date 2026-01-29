/*
 * /d/Rhovanion/common/mirkwood/mirkwood.c
 * Created by Milan
 *
 * This file is to be inherited by all Mirkwood rooms.
 */
#pragma save_binary
#pragma strict_types
#include "/d/Shire/old_forest/defs.h"
inherit "/d/Shire/old_forest/map_serv";
inherit "/d/Gondor/common/lib/herbsearch";
#include "/d/Gondor/common/lib/time.h"
#include "/d/Shire/sys/defs.h"

public nomask string
query_file_with_map()
{
    return OLD_FOR_DIR + "map";
}

public nomask string
time_of_day()
{
    return tod();
}

public int
is_room(string arg)
{
    if ((arg == "x") || (arg == "P") || (arg == "s") || (arg == "H") ||
        (arg == "g") || (arg == "E") || (arg == "T") || (arg == "p") ||
        (arg == "M"))
	return 1;
    return 0;
}



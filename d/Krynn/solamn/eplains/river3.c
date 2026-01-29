/* Aridor, 08/98 */

#include "local.h"
inherit ROOM_BASE;

int
flooded()
{
    return (VKEEP)->query_flooded();
    return 0; /* not flooded */
    /*return 1; flooded */
}

void
create_road_room()
{
    set_short("@@my_short@@");
    set_long("@@my_long@@");

    add_item(({"river", "vingaard river", "shore", "western shore"}),
        "@@my_long@@");

    add_exit(VKEEP_LINK,"up","@@flooded@@",6,"@@flooded@@");
    add_exit("river2","southeast","@@flooded@@",6,"@@flooded@@");

    add_prop(ROOM_I_TYPE, "@@flooded@@");
}

string
my_short()
{
    if (flooded())
        return ("Near the western shore of the Vingaard River");
    return "On the western shore of Vingaard River";
}

string
my_long()
{
    if (flooded())
        return ("This is somewhere on the Vingaard River which is close " +
            "to the western shore. The river looks mighty and strong. " +
            "The water level is much higher than normal.\n");
    return ("You are standing on the western shore of the Vingaard " +
        "River, which spans quite some distance across. " +
        "A ford appears to lead southeast across the river. An inclined " +
        "plane leads up the embankment onto the pier here.\n");

}

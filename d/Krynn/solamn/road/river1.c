/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

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

    add_item(({"river", "water", "vingaard river", "shore", "eastern shore",
        "western shore"}), "@@my_long@@");

    add_exit("river2", "northwest", "@@flooded@@", 6, 0);
    add_exit("vkeep_link", "southeast", "@@flooded@@", 6, 0);

    add_prop(ROOM_I_TYPE, "@@flooded@@");
}

string
my_short()
{
    if (flooded())
        return ("In the middle of the Vingaard River");

    return "In a ford across the Vingaard River";
}

string
my_long()
{
    if (flooded())
          return ("This is somewhere on the Vingaard River. The eastern " +
              "shore is a bit closer than the western shore. The river " +
              "looks mighty and strong. The water level is much higher " +
              "than normal.\n");

    return ("You are standing in the water of the Vingaard River about " +
        "one third of the way from the eastern shore. The river is less " +
        "than knee deep here, and the current isn't very strong.\n");
}

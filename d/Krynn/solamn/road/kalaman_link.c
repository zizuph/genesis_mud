/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

void
create_road_room()
{
    set_short("Before the city gates of Kalaman");
    set_long(" " +
        "You can enter the city through the gates by going southeast. " +
        "Northwest, the road will take you towards the far away " +
        "city of Solanthus. North, you can see the Vingaard River, " +
        "while the massive city walls of Kalaman block your view to " +
        "the east. In the distance to the south, you can see mountains " +
        "rising up into the sky, while the west and southwest are " +
        "dominated by the green of bushes and the occasional tree " +
        "making up the Plains of Solamnia.\n");
    add_item(({"road", "stone road"}),
        "The road is a typical stone road, very dusty and dirty.\n");
    add_item(({"city", "gates", "wall", "city walls", "city wall", "walls",
        "kalaman"}),
            "The city of Kalaman can be entered by going southeast past " +
            "the city gates. The gates are the only way into the city, " +
            "since there are walls protecting the city everywhere else.\n");
    add_item(({"river", "vingaard river", "water"}),
        "You can see the water reflecting the light, and the river seems " +
        "to be several hundred metres across at this point.\n");
    add_item(({"mountains", "dargaard mountains"}),
        "The mountains to the south are known as the Dargaard Mountains, " +
        "stretching south from here all the way to Throtyl.\n");
    add_item(({"bushes", "tree", "trees", "plains", "plains of solamnia"}),
        "Bushes and trees block any good view you might otherwise have, " +
        "but you know these plains stretch out for many miles.\n");

    if (LOAD_ERR(ROAD_OBJECT))
    {
        write("Bug! please report immediately.\n");
	return;
    }

    add_exit("", "west", "@@enter_map:" + ROAD_OBJECT + "|K@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|K@@",6,1);
    add_exit("", "northwest","@@enter_map:" + ROAD_OBJECT + "|K@@",3,0);
    add_exit(KALAMAN_LINK,"southeast","@@pass_gate@@");
}

int
pass_gate()
{
    write("You pass through the city gates and enter Kalaman.\n");
    return 0;
}

/* created by Aridor 06/19/93 */
/* modified by Vitwitch 08/2021 to include climbers route link */

#define VINGAARD_HERBTRAIL_STH "/d/Krynn/solamn/vin_herbtr/vinherbtr7"

#include "../local.h"

inherit ROOM_BASE


void
create_vin_mount_room()
{

    set_short("Vingaard mountains");
    set_long("You are on a twisty road through the "
        +    "Vingaard mountains. The road leads up to "
        +    "the southwest and down to the west. "
        +    "A climbers' route goes upward to the north.\n");

    OUTSIDE;

    add_exit(ROOM + "road2","west",0,0);
    add_exit(ROOM + "road4","southwest",0,5);
    add_exit(VINGAARD_HERBTRAIL_STH,"upward",0,5);

    add_item(({"track","ground","road","gravel","mountain track"}),
	     "The track itself is simply " +
		"laid out with small stones and gravel.\n");
    add_item(({"mountains","mountain","mountainside"}),
	     "These are high mountains indeed, rocks and occasional " +
		"shrubs are scattered everywhere, it is definitely " +
		"a very hostile area.\n");
    add_item(({"cliffs","cliff"}),
	     "Steep, almost vertical cliffs offer no chance for travel " +
		"in other directions but along the road.\n");
    add_item(({"shrubs","rocks"}),
	     "The mountainsides are covered with rocks with a few " +
		"shrubs making their living in between.\n");
    add_item(({"route","climbers route"}),
	     "The rugged looking climbers' route leaves the " +
   	     "track and snakes its way north and up and up and up.\n");

}

/*
void
init()
{
    ::init();
    if (random(4) != 1)
        return;
    if (present("hobgoblin",TO))
        return;
    if (TP->query_average_stat() > 45)
        clone_object(LIV + "orc")->move_living("M",TO);

}
*/


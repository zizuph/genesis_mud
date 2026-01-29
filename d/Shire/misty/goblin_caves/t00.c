/* goblin caves */
#include <filter_funs.h>
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR+"t01", "northeast");
    add_exit(MISTY_DIR+"c2", "north");
//    set_pull(MISTY_DIR+"c2", "north");
    add_prop(ROOM_I_LIGHT, 1);
    add_item(({"walls", "wall"}),
        "The walls were chiseled out of the mountain by crude instruments. They are very rough looking.\n");

}

void
reset_shire_room()
{
    object goblin1;
    object goblin2; /* there are several goblins here    */

    seteuid(getuid());
    if(!present("_misty_goblin_"))
    {
	goblin1 = clone_object(GOBLIN_NPC_DIR + "goblin_low");
	goblin1->arm_me();
	goblin1->move_living("xxx", this_object());
	goblin2 = clone_object(GOBLIN_NPC_DIR + "goblin_low");
	goblin2->arm_me();
	goblin2->move_living("xxx", this_object());
	goblin2->team_join(goblin1); /* goblin2 will be the leader */
    }
}

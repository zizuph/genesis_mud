/* 
 * highpass 
 *
 * Modified by Varian to add eastern exit March 3, 2019
 *
 */

#include "local.h"

inherit CAVE_BASE;


void create_cave()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);    

    set_short("filthy cave");
    set_long("This is a filthy dark cave. Fortunately you have a light " + 
      "by which you can see the walls around you. You notice a " +
      "dark recess in the eastern wall.\n");

    add_item( ({"recess", "dark recess", "east wall",
            "eastern wall"}),
        "There is a dark reccess at the eastern edge of this " +
        "cave, you could go investigate it if you are curious " +
        "enough.\n");

    add_exit(MISTY_DIR+"p18", "out", 0, 4);
    add_exit(MISTY_DIR + "bats", "east", 0, 4, 1);
    reset_shire_room();
}

void
reset_shire_room()
{
    object goblin1; 
    object goblin2; /* there are several goblins here    */

    seteuid(getuid());

    if (!present("_misty_goblin_"))
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

/* goblin caves */

#include "../local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    set_short("guard room in goblin prison");
    set_long("In this room usually goblin guards take their duty. "+
      "When they are here, they stop everyone from entering "+
      "the prison unless he is going to stay there locked. "+
      "Of course they stop anybody trying to escape from "+
      "prison too.\n");
    add_item(({"wall","walls"}),BS("These walls seems to be natural. But "+
	"then again you have seen so many strange things in these "+
	"caves that you are not sure with anythink you see or feel.\n"));

    add_exit(CAVE_DIR+"d0", "west", "@@block_exit:" + file_name(this_object()) + 
      "|"+CAVE_DIR+"d0@@");
    add_exit(CAVE_DIR+"d3", "east", "@@block_exit:" + file_name(this_object()) + 
      "|"+CAVE_DIR+"3@@");

    reset_shire_room();
}

int
block_exit(string room)
{
    if(present("_misty_goblin_", TO) &&
      TP->check_seen(present("_misty_goblin_", TO)) &&
      (TP->query_prop(LIVE_O_LAST_ROOM) != find_object(room)))
    {
	write("The goblin guard stops you from passing.\n");
	say(QCTNAME(TP)+" was stopped by goblin guard from passing.\n");
	return 1;
    }
    return 0;
}

void
reset_shire_room()
{
    object goblin; 

    seteuid(getuid());

    if(!present("_misty_goblin_"))
    {
	goblin = clone_object(GOBLIN_NPC_DIR +"goblin_high");
	goblin->add_prop(LIVE_I_SEE_DARK, 1);
	goblin->arm_me();
	goblin->move_living("xxx", this_object());
    }
}

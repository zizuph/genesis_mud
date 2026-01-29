#include "defs.h"

inherit SHIRE_ROOM;

#define NUM_TROLLS  10

// Prototypes
void create_trolls();

void
create_shire_room()
{
    set_short("troll breeder");
    set_long("This is a room that NO mortal should ever see.  It is the "+
      "breeding ground for trolls in the trollshaws.\n");

    add_prop(ROOM_I_INSIDE, 1);
    create_trolls();
}

void
reset_shire_room()
{
    create_trolls();
}

void
create_trolls()
{
    int i = -1;
    object troll;

    while (++i < NUM_TROLLS)
    {
	troll = clone_object(SHAWS_NPC + "troll");
	troll->move_living("void", TO);
	troll->move_out();
	SHAWS_MASTER->add_troll(troll);
    }
}

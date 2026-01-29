/* created by Aridor 06/19/93 */

#include "../local.h"

inherit ROOM_BASE

#include <ss_types.h>
#include <macros.h>

#include RND_MEET

object* monster = ({ });

void
init()
{
    object mon;

    ::init();
    if (random(50) > 1)
      return;
    mon = RANDOM_MEET(TABLE);
    mon->move_living("xx",TO);
    monster += ({ mon });
}

void
reset_vin_mount_room()
{
    monster -= ({ 0 });
    if (monster && sizeof(monster))
    {
	monster->command("emote leaves.");
	monster->remove_object();
	monster = ({ });
    }
}

void
create_vin_mount_room()
{

    set_short("Mountain pass");
    set_long("@@my_long");

    OUTSIDE;

    add_exit(ROOM + "road7","north",0,1);
    add_exit(ROOM + "road9","southwest",0,1);
    add_exit(ROOM + "road11","up","@@can_climb",20);

    add_item(({"track","ground","road","gravel","mountain track"}),
	     "The track itself is simply " +
		"laid out with small stones and gravel.\n");
    add_item("pass",
	     "There are two mountains, one to the west, and the other " +
		"to the east, whereas the road continues down towards the " +
		"north and down towards the southwest.\n");
    add_item(({"mountains","mountain","mountainside","west mountain","east mountain"}),
	     "These are high mountains indeed, rocks and occasional " +
		"shrubs are scattered everywhere, it is definitely " +
		"a very hostile area.\n");
    add_item(({"shrubs","rocks"}),
	     "The mountainsides are covered with rocks with a few " +
		"shrubs making their living in between.\n");
}


string
my_long()
{
    string desc = "It seems the road has reached its highest "
         + "point, from this pass you see mountains all "
         + "around you. There appears to be a possibility to "
         + "climb further up on top of the mountain.\n";
    return desc;
}

int
can_climb()
{
    if (TP->query_skill(SS_CLIMB) > 20)
        return 0;
    else
    {
        say(QCTNAME(TP) + " tried to climb up but failed.\n");
        write("You try to climb up but almost "
          + "break your limbs when you fall "
          + "back down.\n");
        return 1;
    }
}




/* created by Aridor 06/19/93 */

#include "../local.h"

inherit ROOM_BASE

#include RND_MEET

object* monster = ({});

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

    set_short("In the Vingaard Mountains");
    set_long("The winding road continues in a general north and south "
        +    "direction winding itself up the mountainside to the north.\n");

    OUTSIDE;

    add_exit(ROOM + "road8","northeast",0,30);
    add_exit(ROOM + "road10","southeast",0,15);

    add_item(({"track","ground","road","gravel","mountain track"}),
         "The track itself is simply " +
        "laid out with small stones and gravel.\n");
    add_item(({"mountains","mountain"}),
         "These are high mountains indeed, rocks and occasional " +
        "shrubs are scattered everywhere, it is definitely " +
        "a very hostile area.\n");
    add_item(({"shrubs","rocks"}),
         "The mountainsides are covered with rocks with a few " +
        "shrubs making their living in between.\n");
}






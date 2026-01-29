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
    set_short("Road outside Palanthas");
    set_long("The road here is flat but it reaches the "
        +    "mountains to the east and to the northwest "
        +    "you can see the city of Palanthas spreading "
        +    "out. There are two towers that you can see "
        +    "clearly from here, one seems very dark and "
        +    "blackened and even from this distance you get "
        +    "an eerie feeling. The other is very friendly "
        +    "and painted white. Both seem to be located in "
        +    "the middle of the city.\n");

    OUTSIDE

    add_exit(PALAN,"northwest",0,5);
    add_exit(ROOM + "road3","east",0,15);

    add_item(({"tower","towers","city"}),
         "You cannot make out any details from this distance.\n");
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

}



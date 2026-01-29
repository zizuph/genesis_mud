inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"

void
create_shire_room()
{
    FIXEUID

    set_short("Within a spacious cave");
    set_long("You stand within a spacious cave that looks to be "+
        "the residence of someone or something. Bones are heaped "+
        "up in one corner next to some large boulders. There "+
        "seems to be just one way out of this room, that being "+
        "the way you came in.\n");

    if (!present("_trollshaw_troll",TO))
    {
        room_add_object("/d/Shire/common/trollsh/new/troll",
            6,"A troll rises from its slumber.\n");
    }

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Shire/common/trollsh/new/cave1","north",0,1);
}

void
reset_shire_room()
{
    int amt = 3+random(2);
    object troll;

    if (!present("_trollshaw_troll",TO))
    {
        room_add_object("/d/Shire/common/trollsh/new/troll",
            amt,"A troll rises from its slumber.\n");
    }
}

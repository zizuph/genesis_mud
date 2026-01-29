inherit "/std/room";
inherit "/d/Cirath/ak_wela/inherit/room_tell";
#include "/d/Cirath/common/defs.h"

public void reset_room();

void
create_room()
{
    set_tell_time(90);
    add_tell("The smell of the sea wafts past your nose.\n");
    add_tell("An daydreaming passerby accidentally bumps into you.\n");
    add_tell("You hear the sounds of a brawl somewhere in the distance.\n");
    add_tell("A fast-moving rickshaw rattles past you.\n");

    reset_room();
}


void
reset_room()
{
    object gull, raven, pigeon;
//    if (!random(10))
//        clone_object(SHIRE_ROCK)->move(TO);
    if (!random(10))
        if (!gull || gull->query_name() == "corpse")
            clone_object(AK_WELA_DIR + "npc/gull")->move(TO);
    if (!random(20))
        if (!raven || raven->query_name() == "corpse")
            clone_object(AK_WELA_DIR + "npc/raven")->move(TO);
    if (!random(8))
        if (!pigeon || pigeon->query_name() == "corpse")
            clone_object(AK_WELA_DIR + "npc/pigeon")->move(TO);
}


void
enter_inv(object what, object from)
{
    start_room_tells(what);

    ::enter_inv(what, from);
}

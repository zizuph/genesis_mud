inherit "/std/room";
inherit "/d/Cirath/ak_wela/inherit/room_tell";

#include "/d/Cirath/common/defs.h"

#define JETSAM_CHANCE 8
#define JETSAM_DIR AK_WELA_DIR + "obj/jetsam/"


void
create_room()
{
    set_tell_time(30);
    add_tell("The smell of the sea wafts past your nose.\n");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
}


void
reset_room()
{
    object gull, raven, pigeon;
    string *jetsam;

    if (!random(JETSAM_CHANCE))
    {
        jetsam = get_dir(JETSAM_DIR);
        clone_object(JETSAM_DIR + jetsam[random(sizeof(jetsam))])->move(TO);
        tell_room(TO, "A piece of jetsam washes up on the shore.\n");
    }

    if (!random(10))
        clone_object(SHIRE_ROCK)->move(TO);

    if (!random(10))
        if (!gull || gull->query_name() == "corpse")
            (gull = clone_object(AK_WELA_DIR + "npc/gull"))->move(TO);
    if (!random(10))
        if (!raven || raven->query_name() == "corpse")
            (raven = clone_object(AK_WELA_DIR + "npc/raven"))->move(TO);
    if (!random(10))
        if (!pigeon || pigeon->query_name() == "corpse")
            (pigeon = clone_object(AK_WELA_DIR + "npc/pigeon"))->move(TO);
}


void
enter_inv(object what, object from)
{
    start_room_tells(what);

    ::enter_inv(what, from);
}

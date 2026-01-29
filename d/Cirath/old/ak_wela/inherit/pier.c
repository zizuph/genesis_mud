inherit "/std/room";
#include "/d/Cirath/common/defs.h"

public string sign_txt();
public void reset_room();

void
create_room()
{
    set_short("A noisy, crowded pier just east of the city");

    add_item("birds", "The birds are mostly seagulls, though there " +
        "are quite a few ravens and pigeons as well.  What they are " +
        "eating is, to say the least, interesting.\n");
    add_item(({"seagull", "seagulls", "gull", "gulls"}), "Despite their " +
        "clean white bodies, the seagulls appear to be the dirtiest of " +
        "all the birds.  The water they are landing in is apparently " +
        "where the city's sewage ends up.\n");
    add_item(({"pigeon", "pigeons"}), "These annoying birds are a little " +
        "less common than in the rest of the city.  They've probably " +
        "been chased off by all the gulls.\n");
    add_item(({"raven", "crow", "blackbird", "ravens", "crows", "blackbirds"}),
        "These large, intelligent birds usually prefer more rural areas, " +
        "but they're too smart to pass up the wonderful supply of food " +
        "here at the docks.\n");
    add_cmd_item("sign", "read", sign_txt());

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    reset_room();
}


void
reset_room()
{
    object gull, raven, pigeon;
    int count;

    if (!random(2)) // 50% chance of 1 to 3 gulls
        if (!gull || gull->query_name() == "corpse")
            for (count = 0; count < random(3) + 1; count++)
                (gull = clone_object(AK_WELA_DIR + "npc/gull"))->move(TO);
    if (!random(10)) // 10% chance
        if (!pigeon || pigeon->query_name() == "corpse")
            (pigeon = clone_object(AK_WELA_DIR + "npc/pigeon"))->move(TO);
    if (!random(20)) // 5% chance
        if (!raven || raven->query_name() == "corpse")
            (raven = clone_object(AK_WELA_DIR + "npc/raven"))->move(TO);
}


public string
sign_txt()
{
    return ("It says:\n\t\t No regularly scheduled ships dock here.\n");
}

inherit "/d/Emerald/std/clone_handler";

#include "/d/Emerald/defs.h"

/* Called by /d/Emerald/telberin/nw_gate.c */

#define CURAN_ID 6

int clone_curan()
{
    return !random(20);
}

void
create_clone_handler()
{
    set_default_area("/d/Emerald/telberin/");


    add_clone(TELBERIN_DIR + "npc/elf_patrol", 1, 15,
              ( ({TELBERIN_DIR, TELBERIN_DIR + "avenue/"}) ),
             "An elf guards the streets.\n");

    add_clone(TELBERIN_DIR + "npc/traveller", 2, 12,
            ( ({TELBERIN_DIR, TELBERIN_DIR + "avenue/"}) ),
             "An traveller trudges along the streets.\n");

    add_clone(TELBERIN_DIR + "npc/citizen", 3, 20,
            ( ({TELBERIN_DIR, TELBERIN_DIR + "avenue/"}) ),
             "A citizen walks past.\n");

    add_clone(TELBERIN_DIR + "npc/child", 4, 10,
            ( ({TELBERIN_DIR, TELBERIN_DIR + "avenue/"}) ),
             "Laughter abounds as a child romps in.\n");

    add_clone(TELBERIN_DIR + "npc/trader", 5, 8,
            ( ({TELBERIN_DIR, TELBERIN_DIR + "avenue/"}) ),
             "A trader walks along, looking for customers.\n");

    add_clone(TELBERIN_DIR + "npc/curan", CURAN_ID, clone_curan,  TELBERIN_DIR);

    add_clone(TELBERIN_DIR + "npc/cloak_maker", 7, 1, TELBERIN_DIR + "cloak_shop");

    add_clone(TELBERIN_DIR + "npc/armourer", 8, 1,
        TELBERIN_DIR + "armoury");

    set_excluded_destinations(({ TELBERIN_DIR + "armoury_store_room", 
                                 TELBERIN_DIR + "leather_shop",
                                 TELBERIN_DIR + "tree_office",
                                 TELBERIN_DIR + "choreo/rooms/p_hall",
                                 TELBERIN_DIR + "choreo/rooms/join_room",
                                 TELBERIN_DIR + "choreo/rooms/join",
                                 TELBERIN_DIR + "choreo/rooms/foyer"}));
}

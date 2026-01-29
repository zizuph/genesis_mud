#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
//inherit "/d/Emerald/lib/shop_list";
inherit "/lib/shop";
inherit "/d/Shire/bree/gem_list";
//inherit "/d/Gondor/common/lib/gem_shop";


inherit "/d/Genesis/gems/gem_shop";

#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define STORE_ROOM (TOWN_DIR + "gem_store")

/* Prototype */
void reset_shire_room();

void
create_shire_room()
{
    set_short("Gem Shop of Bree");
    set_long("This is the Gem Shop of Bree. It is a large building with " +
        "glass cases of gems displayed for all to see. The room is light " +
        "and airy, and run by some local dwarves who made their way to " +
        "Bree. Here, you can sell your gems for a tidy profit or buy gems " +
        "as needed.\n");
      
    create_gem_shop();
    /* Taken from /d/Genesis/gems/gem_shop.c */
    set_money_give_max(100000);
    set_money_give_out(   ({  100,  1000, 1000,  50 }));
    set_money_give_reduce(({    0,     2,    4,  10 }));

    add_exit(ROAD_DIR + "broad05", "out", 0,0,1);
    add_exit(ROAD_DIR + "broad05", "north");

    set_store_room(STORE_ROOM);
}

void
init()
{
    ::init();
    init_gem_shop();
}

void
reset_shire_room()
{
}

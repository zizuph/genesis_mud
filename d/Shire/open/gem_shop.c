#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/lib/shop";
inherit "/d/Shire/open/gem_list";


inherit "/d/Genesis/gems/gem_shop";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/defs.h"

#define STORE_ROOM ("/d/Shire/open/gem_store")

/* Prototype */
void reset_shire_room();

void
create_shire_room()
{
    set_short("Gem Shop of Bree");
    set_long("This is the Gem Shop of Bree. It is a large building with glass cases of gems displayed for all to see. The room is light and airy, and run by some local dwarves who made their way to Bree. Here, you can sell your gems for a tidy profit or buy gems as needed.\n");
      
    create_gem_shop();
    set_money_greed_sell(130);
    set_money_give_out(   ({ 100, 700, 4000, 0 })); /* Max_pay   */
    add_exit(ROAD_DIR + "broad05", "out", 0);
    add_exit(ROAD_DIR + "broad05", "north", 0,0,1);

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

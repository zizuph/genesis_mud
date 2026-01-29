/*
 * Shop of Imladris
 * Finwe, February 1998
 */
 
#pragma save_binary
#pragma strict_types
 
inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";
 
#include "local.h"
 
inherit HOUSE_IN_BASE;

/* Prototype */
void reset_shire_room();
 
static object celedur;  /* shopkeeper */
 
 
void
create_house_room()
{
    set_short("The shop of Imladris");
    set_long("The shop of Imladris. Here, elves buy and sell " +
        "all kinds of wares they find while travelling " +
        "throughout the lands. As a result, one never knows " +
        "what one will find in the shop. The elves have " +
        "graciously opened their shop to travellers, so feel " +
        "free to buy or sell anything you may have.\n");
     add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved of thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");

    set_extra_window("@@window_position@@ set into the " +
        "east and north walls.");
    add_item(({"east windows", "eastern windows", "east window",
            "eastern window"}),
        "@@east_down@@\n");
    add_item(({"north windows", "northern windows", "north window",
            "northern window"}),
        "@@south_down@@\n");

    num_of_windows=2;

 
    config_default_trade();
    set_money_greed_sell(90);
    set_money_greed_buy(90);
    set_store_room(VALLEY_DIR + "store");

    set_alarm(1.0, 0.0, reset_shire_room);
     
    add_exit(VALLEY_DIR + "n_path02", "east");
    add_exit("@@query_store_room@@", "down", "@@wiz_check@@", 0);
 
}
 
void
reset_shire_room()
{
 
    if (!celedur)
        celedur = clone_object(RNPC_DIR + "celedur");
    if (!present(celedur,this_object()))
        celedur->move(this_object());
 
}
 
 
 
void
init()
{
    ::init();
 
    init_shop();
 
}

/*  Added an extra linechange to @wizcheck mortal information
    Meton 2021*/
#include "default.h"
inherit PORT_ROOM;
inherit "/d/Kalad/std/shop_list";
#define STORE_ROOM PORT + "s18"
object ob1;

void
create_port_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_max(0);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    INSIDE;
    set_short("The Sailmaker's Shop");
    set_long("This is the interior of the Sailmaker's Shop, business place of "+
      "Orgadar. Rickety-looking, albeit sturdy wooden planks serve as the "+
      "walls, floor and ceiling. A burnished grey counter lies opposite your "+
      "position, and beyond that is an open doorway to another room.\n"+
      "A small grey plaque hangs over the counter.\n");
    add_item(({"rickety-looking wooden planks","sturdy wooden planks","wooden planks","planks","plank"}),
      "The interior of the shop looks quite unstable, yet it has withstood "+
      "the many sea storms that have struck this coast, with no damage taken. "+
      "The planks must be sturdier than they appear to be.\n");
    add_item(({"interior","walls","wall","floor","ceiling"}),
      "The inside of the shop has been entirely made out of many wooden "+
      "planks.\n");
    add_item(({"burnished grey counter","burnished counter","grey counter","counter"}),
      "It is constructed from the same material as the planks in the shop. "+
      "However, it still looks quite serviceable, as proven by the scattered "+
      "pieces of paper on top.\n");
    add_item(({"pieces of paper","pieces","paper"}),"Blank sheets of "+
      "parchment paper.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_exit(PORT + "s18", "north", "@@wiz_check");
    add_exit(PORT + "s44", "south");
    set_store_room(STORE_ROOM);
    ob1 = clone_object(PORT + "npc/sailmaker");
    ob1 -> move_living("xxx", TO);
}

plaque()
{
    return "This shop only sells items, it does not buy them.\n";
}

void
init()
{
    ::init();
    init_shop();
}

int
wiz_check()
{
    if (TP->query_wiz_level())
	return 0;
    write("The sailmaker surprises you by picking you up and hurling "+
      "you across the room!\n\n");
    say("The sailmaker surprises " + QCTNAME(TP) + " by picking " + TP->query_objective() + " up and hurling " + TP->query_objective() + " across the room!\n");
    TP->move_living("out the door",PORT + "s44");
    return 1;
}

int
do_read(string str)
{
    return 0;
}

int shop_hook_allow_sell(object ob)
{
    if(ob->id("_Kabal_sail_shop"))return 1;
    return 0;
}

int
do_sell(string str)
{
    TP->catch_msg("This shop only sells items, it does not buy them.\n");
    return 1;
}


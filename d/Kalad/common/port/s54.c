#include "default.h"
inherit PORT_ROOM;
inherit "/d/Kalad/std/shop_list";
#define STORE_ROOM PORT + "shop/tarstore"
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
    set_short("The Tar Shop");
    set_long("You are inside Mardon's Tar Shop, where the sticky black "+
      "goo is sold to help in the making and upkeep of seagoing vessels. "+
      "The interior of the shop seems to mirror the product sold here, for "+
      "the walls, floor and ceiling are colored a deep dark brown. A dark "+
      "brown desk sits in the southeastern corner of the room, right in front "+
      "of a set of stairs that leads up.\n"+
      "A dark plaque hangs over the desk.\n");
    add_item(({"walls","wall","floor","ceiling"}),"The interior of the Tar "+
      "shop is made of a rich, dark wood that possesses an amazingly fine "+
      "smooth texture. The grain of the wood is quite astounding.\n");
    add_item(({"dark brown desk","dark desk","brown desk"}),"A finely-grained "+
      "teak desk. Its polished surface distinctly reflects the light "+
      "pervading the room.\n");
    add_item(({"set of stairs","stairs"}),"A wooden staircase that leads to "+
      "the upper floor of the shop.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_exit(PORT + "s53", "west");
    add_exit(PORT + "shop/tarstore", "up", "@@wiz_check");
    set_store_room(STORE_ROOM);
    ob1 = clone_object(PORT + "npc/tarshop_owner");
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
    write("The shopkeeper charges into your stomach and forces you away from his "+
      "storeroom.\n");
    say("The shopkeeper charges into " + QCTNAME(TP) + "'s stomach because " + TP->query_pronoun() + " tried to enter his storeroom.\n");
    return 1;
}

int
do_read(string str)
{
    return 0;
}

int shop_hook_allow_sell(object ob)
{
    if(ob->id("_Kabal_tar_shop"))return 1;
    return 0;
}

int
do_sell(string str)
{
    TP->catch_msg("This shop only sells items, it does not buy them.\n");
    return 1;
}


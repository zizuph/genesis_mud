#include "default.h"
inherit PORT_ROOM;
inherit "/d/Kalad/std/shop_list";
#define STORE_ROOM PORT + "shop/netstore"
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
    set_short("The Netweaver's Shop");
    set_long("You are inside the Netweaver's shop, where many fine and "+
      "durable fishing nets are sold. The plain wooden walls of the place "+
      "are covered with a variety of fishing goods. The rest of the shop "+
      "is fairly bare, with not even a foot rug on the floor. A big counter "+
      "is opposite you, and behind that are a set of stairs going up.\n"+
      "A large plaque hangs over the counter.\n");
    add_item(({"plain wooden walls","plain walls","wooden walls","walls","wall"}),
      "Made from sturdy hardwood planks, the wall looks quite durable, "+
      "albeit rather drab in appearance.\n");
    add_item(({"fishing goods","goods"}),"Fishing tackles, poles, nets "+
      "and other fishermans' equipment hangs on the walls.\n");
    add_item(({"floor"}),"Made of the same hardwood planks as the rest of "+
      "shop, it is cold, bare and unattractive.\n");
    add_item(({"big counter","counter"}),"A large, bare counter that "+
      "is on the far side of the shop.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_exit(PORT + "s23", "east");
    add_exit(PORT + "shop/netstore", "up", "@@wiz_check");
    set_store_room(STORE_ROOM);
    ob1 = clone_object(PORT + "npc/netweaver");
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
    write("The netweaver smacks your head and forces you away from his "+
      "storeroom.\n");
    say("The netweaver smacks " + QCTNAME(TP) + "'s head because " + TP->query_pronoun() + " tried to enter his storeroom.\n");
    return 1;
}

int
do_read(string str)
{
    return 0;
}

int shop_hook_allow_sell(object ob)
{
    if(ob->id("_Kabal_net_shop"))return 1;
    return 0;
}

int
do_sell(string str)
{
    TP->catch_msg("This shop only sells items, it does not buy them.\n");
    return 1;
}


#include "default.h"
inherit PORT_ROOM;
inherit "/d/Kalad/std/shop_list";
#define STORE_ROOM PORT + "shop/tanstore"
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
    set_short("The Tanner's Shop");
    set_long("You are within the Tanner's humble shop, where handcrafted "+
      "leather goods are sold. The bare wooden walls of the shop are "+
      "meticulously clean and the unmistakeable odor of fresh leather "+
      "fills the room. A small counter lies opposite of you, and behind "+
      "that is a set of stairs that leads up.\n"+
      "A wooden plaque hangs above the counter.\n");
    add_item(({"bare wooden walls","bare walls","wooden walls","walls","wall"}),
      "Made from hardwood, they look to be in excellent condition. Not a "+
      "trace of dust mars their surface.\n");
    add_item(({"small counter","counter"}),"It has been polished to a "+
      "brilliant shine, the hardwood gleaming as bright as the morning "+
      "sun. A few feet above it is a wooden plaque.\n");
    add_item(({"set of stairs","stairs"}),"A wooden staircase that leads to "+
      "the upper floor of the shop.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_exit(PORT + "s20", "west");
    add_exit(PORT + "shop/tanstore", "up", "@@wiz_check");
    set_store_room(STORE_ROOM);
    ob1 = clone_object(PORT + "npc/tanner");
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
    write("The tanner kicks you in the stomach and forces you away from his "+
      "storeroom.\n");
    say("The tanner kicks " + QCTNAME(TP) + " in the stomach because " + TP->query_pronoun() + " tried to go up to his storeroom.\n");
    return 1;
}

int
do_read(string str)
{
    return 0;
}

int shop_hook_allow_sell(object ob)
{
    if(ob->id("_Kabal_tanner_shop"))return 1;
    return 0;
}

int
do_sell(string str)
{
    TP->catch_msg("This shop only sells items, it does not buy them.\n");
    return 1;
}


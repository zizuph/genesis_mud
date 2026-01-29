#include "../default.h"

inherit CVAN_ROOM;
inherit "/d/Kalad/std/shop_list";

#define STORE_ROOM	(CVAN + "shop/mmstore")

object ob1;

void
create_cvan_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_max(0);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));

    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Master Mapmaker's Shop");
    set_long("You are inside the mapmaker's shop.\n"+
      "Glancing around at your surroundings you see maps of all kinds and "+
      "descriptions mounted on the walls. At the far end of the shop is a "+
      "small counter, past which is a door leading into a backroom of the "+
      "shop. "+
      "A large plaque hangs over the counter.\n");

    add_item("plaque", "@@plaque");
    add_item(({"maps"}), "Countless maps of and from places far and wide "+
      "are hung upon the shop's walls.\n");
    add_item(({"counter"}), "A small wooden counter thats been lovingly "+
      "polished to a brilliant shine.\n");

    add_cmd_item("plaque", "read", "@@plaque");

    add_exit(CVAN + "shop/mmstore", "west", "@@wiz_check");
    add_exit(CVAN + "caravan/s4", "east");

    set_store_room(STORE_ROOM);

    ob1 = clone_object(NPC + "mmmaker");
    ob1->move_living("M", TO);
}

string
plaque()
{
    return "This store only sells maps, we do not pay for any items that "+
    "you attempt to sell here.\n";
}

int
wiz_check()
{
    if (TP->query_wiz_level())
	return 0;
    write("The mapmaker scowls at you, slaps you in the head and pushes you "+
      "away from his precious maps.\n");
    say(QCTNAME(TP) + " tries to go west but is slapped in the head by "+
      "the mapmaker and roughly pushed back.\n");
    return 1;
}

int
do_read(string str)
{
    return 0;
}

int
shop_hook_allow_sell(object ob)
{
    if(ob->id("_Kabal_map_shop"))return 1;
    return 0;
}

int
do_sell(string str)
{
    TP->catch_msg("This shop only sells maps.\n");
    return 1;
}

void
init()
{
    ::init();
    init_shop();
}

/*
*   Added files.h and query_object_value to replace 
*   potion_value function to the shop.
*   June 2021, Meton.
*/


#include <files.h>
#include "../default.h"
inherit CVAN_ROOM;
inherit "/d/Kalad/std/shop_list";

#define STORE_ROOM CVAN + "shop/mdstore"

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

    set_short("Master Dealer's Wagon");
    set_long("You've entered an average-sized wooden wagon. However, there is "+
      "nothing 'average' about the contents of this wagon. On one side of "+
      "the wagon is a small counter behind which is a dark curtain. The "+
      "rest of the wagon is filled with shelves that contain many strange "+
      "and fascinating objects.\n"+
      "A large plaque hangs over the counter.\n");

    add_item(({ "counter" }),
      "It cuts off the eastern side of the wagon, however there is one part "+
      "of it that lifts to allow access to the far side.\n");

    add_item(({ "curtain" }),
      "A velvet black curtain made of the finest threads of silk. It "+
      "seems to be draped over something.\n");

    add_item(({ "shelves" }),
      "They cover nearly every space of the walls and are filled to "+
      "capacity with many strange-looking objects.\n");

    add_item(({ "objects" }),
      "You can see many bottles filled with unusually-colored liquids, a few "+
      "skulls from creatures best not described and even a rabbit's foot.\n");

    add_item("plaque", "@@plaque");
    add_cmd_item("plaque", "read", "@@plaque");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s13", "north");
    add_exit(CVAN + "shop/mdstore", "south", "@@wiz_check", -1, 0);

    set_store_room(STORE_ROOM);

    clone_object(NPC + "mdealer")->move_living("M", TO);
}

string
plaque()
{
    return "This store only sells items, we do not pay for any items you "+
    "attempt to sell here.\n";
}

int
wiz_check()
{
    if (TP->query_wiz_level())
	return 0;
    write("An enormous dog jumps out from nowhere and forces you back, it then heads south.\n");
    say(QCTNAME(TP) + " tries to go south but is brutally stopped by a "+
      "massive guard dog, which then heads back south.\n");
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
    if(ob->id("_Kabal_equip_shop"))return 1;
    return 0;
}

int
do_sell(string str)
{
    TP->catch_msg("This shop only sells equipment.\n");
    return 1;
}

void
init()
{
    ::init();
    init_shop();
}

 /*
  * Function name: query_object_value
  * Desrciption:   What the object is worth. Allows shops to mask and
  *                value objects differently. Specifically useful for
  *                allowing herb shops, since herbs can normally not
  *                be sold in regular shops.
  */
  int
  query_object_value(object ob)
  {
      if (IS_POTION_OBJECT(ob))
          return ob->query_potion_value() * (ob->num_heap() || 1);
  
      return ob->query_prop(OBJ_I_VALUE);
  }
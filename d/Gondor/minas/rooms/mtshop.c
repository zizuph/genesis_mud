/* 
 *  The shop of Minas Tirith, rewritten by Randor
 *
 *  Added delivery, Olorin, 11-may-1995
 *  Removed delivery since only good-aligned can enter Minas Tirith
 *  -- Finwe, November 2005
 */

inherit "/d/Gondor/common/lib/shop";
inherit "/d/Gondor/minas/lib/minas_fof.c";
//inherit "/d/Genesis/delivery/office";

#include "/d/Gondor/defs.h"

#define STORE_ROOM "/d/Gondor/minas/rooms/store"  /* Where the items are stored */

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Minas Tirith General Store");
    set_long(BSN(
      "You are in the Minas Tirith General Store. "+
      "There are lots of strange items lying around, probably brought "+
      "here from distant lands. Sometimes the shop keeper is looking "+
      "for someone to deliver goods to distant places. "+
      "There is a poster on the wall, and a "+
      "locked door leads north. The exit to the street is east."));
    set_shop_name("Minas Tirith General Store");
    set_keeper_file(MINAS_DIR+"npc/brandir");
    set_no_sell_prop(({GONDOR_M_ROHIRRIM_NO_SELL,
                         GONDOR_M_TIRITH_NO_SELL}));
    set_hated_race(({"goblin"}));
    set_suspected_race(({"gnome","elf"}));
    set_favoured_race(({"human"}));
    add_item("poster", exa_poster());
    add_item(({"door"}), BSN(
        "The door is probably leading into the storeroom of the "+
        "shop. The door is standing open, but the shop keeper " +
        "probably would not be amused if you tried to go there. "));
    add_exit(MINAS_DIR+"e2crc2", "east", 0,0);
    add_exit(STORE_ROOM, "north", "@@wiz_check");

//    set_office("the Minas Tirith General Store", 10);
//    add_content(MINAS_DIR + "obj/cake");
//    add_content(MINAS_DIR + "obj/mtunic");

    reset_room();
}

string
exa_poster()
{
    return "Welcome to the Minas Tirith General Store!\n" +
        "You can try these instructions: \n" +
        "    buy bag for gold and get copper back\n" +
        "    buy bag for gold coins\n" +
        "    sell bag for copper coins\n" +
        "    sell all  - will let you sell all items except for\n" +
        "                items you wield or wear.\n" +
        "    sell all! - will let you sell ALL items you have,\n" +
        "                except armours and weapons.\n" +
        "    sell bag, sell second bag, sell bag 2, sell two bags\n" +
        "                also works. You might want to change the verb to\n" +
        "                'value' or 'buy' too. Beware, you will never buy\n"+
        "                more than one item at a time. So if you really\n" +
        "                want those three expensive bags, you have to\n" +
        "                repeat yourself three times.\n\n";
}

public void
print_message(string str)
{
    keeper->command("say " + str);
}

int
do_buy(string args)
{
  if (check_keeper()) return ::do_buy(args);
  return 0;
}

int
do_value(string args)
{
  if (check_keeper()) return ::do_value(args);
  return 0;
}

int
do_sell(string args)
{
  if (check_keeper()) return ::do_sell(args);
  return 0;
}

int
do_list(string args)
{
  if (check_keeper()) return ::do_list(args);
  return 0;
}

void
shop_hook_stolen_item(object pl, object ob)
{
  keeper->command("eyebrow");
  keeper->command("say Where did you get this "+ob->short()+"?");
  if (ob->query_prop(GONDOR_M_ROHIRRIM_NO_SELL))
    {
      keeper->command("say This was crafted by our allies, the Rohirrim!");
      keeper->command("say You must have stolen it....or even worse!");
      keeper->command("say Get out, before I call the guards on you!");
    }
  else if (ob->query_prop(GONDOR_M_TIRITH_NO_SELL))
    {
      keeper->command("say This is official Gondorian equipment!");
      keeper->command("say You are not supposed to be carrying this,");
      keeper->command("say you must have stolen it...or even worse!");
      keeper->command("say Leave! Or I call the guards!");
    }
}

mixed
shop_hook_filter_sell(object x)
{
    if (weapon_filter(x) || armour_filter(x))
    {
      keeper->command("say I do not trade in weapons or armours!");
      return "The shopkeeper says: Go to the Arms Shoppe with your "+x->short()+".\n"+
        "The shopkeeper says: You will find it further north in this Circle.\n";
    }
    else
      return 0;
}

void
init()
{
//    init_office();
    ::init();
}

void
reset_room()
{
//    reset_office();
    ::reset_room();
}

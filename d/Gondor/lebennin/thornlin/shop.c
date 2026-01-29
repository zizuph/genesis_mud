/* 
 *  The shop of Minas Tirith, rewritten by Randor
 *
 *  Added delivery, Olorin, 11-may-1995
 *  Modified for Thornlin by Auberon, Dec. 31 2000-Jan. 1 2001
 *  (inventory changed, MT-specific code removed)
 */

/*
 * The code that follows is the work of more than one person.
 * Without commenting on the rights of any other authors, this
 * is in significant part copyright (c) 2000 by Scott A. Hardy,
 * whose intellectual property rights are in no way forfeited
 * or transferred.  The portions coded by Scott Hardy are on
 * loan to Genesis (a game run by Chalmers University), who by
 * using and storing it on their system, acknowledge and agree
 * to all of the above.
 */

#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "shop");

public void
create_shop()
{
    set_store_room(THORN_DIR + "store");
    set_short("The Thornlin General Store");
    set_long("You are in the Thornlin General Store. " +
      "There are lots of strange items lying around, probably brought " +
      "here from distant lands.  There is a poster with instructions on " +
      "the wall.  To the east you hear the sound of a blacksmith hammering.\n");
    set_shop_name("Thornlin General Store");
    set_keeper_file(THORN_DIR + "npc/shopkeeper.c");
    add_item("poster", exa_poster());

    add_exit(THORN_DIR + "store", "north", "@@wiz_check", 0, 1);
    add_exit(THORN_DIR + "bank", "west", 0, 0);
    add_exit(THORN_DIR + "forge", "east", 0, 0);
    reset_room();
}

public string
exa_poster()
{
    return "Welcome to the Thornlin General Store!\n" +
    "You can try these instructions: \n" +
    "    buy torch for gold and get copper back\n" +
    "    buy torch for gold coins\n" +
    "    sell torch for copper coins\n" +
    "    sell all  - will let you sell all items except for\n" +
    "                items you wield or wear.\n" +
    "    sell all! - will let you sell ALL items you have,\n" +
    "                including unkept but worn armours and weapons.\n" +
    "    sell torch, sell second torch, sell torch 2, sell two torches\n" +
    "                also works. You might want to change the verb to\n" +
    "                'value' or 'buy' too. Beware, you will never buy\n"+
    "                more than one item at a time. So if you really\n" +
    "                want those three expensive torches, you have to\n" +
    "                repeat yourself three times.\n";
}

public void
print_message(string str)
{
    keeper->command("say " + str);
}

public int
do_buy(string args)
{
    if (check_keeper()) return ::do_buy(args);
    return 0;
}

public int
do_value(string args)
{
    if (check_keeper()) return ::do_value(args);
    return 0;
}

public int
do_sell(string args)
{
    if (check_keeper()) return ::do_sell(args);
    return 0;
}

public int
do_list(string args)
{
    if (check_keeper()) return ::do_list(args);
    return 0;
}

public mixed
shop_hook_filter_sell(object x)
{
    return 0;
}

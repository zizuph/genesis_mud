/*
 *  Shop in Minas Morgul
 *
 *  added delivery support,
 *  Olorin, May 1995
 *  modified to use /d/Gondor/common/lib/shop.c
 *  Olorin, July 1994
 *  changed so that weapons and armours of Morgul fabrication will not
 *    be bought, Olorin,                 July 1994
 *  Olorin, July 1993
 *  copied from:
 *  Bendar's General Store in Edoras
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/shop";
inherit "/d/Genesis/delivery/office";
inherit "/d/Gondor/morgul/feeling.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define STORE_ROOM MORGUL_DIR + "city/rooms/store"  /* Where the items are stored */

public int
block_keeper()
{
    if (TP == keeper)
        return 1;
    return 0;
}

public void
create_shop()
{
    set_store_room(STORE_ROOM);

    set_long(BSN(
        "You are in Bolzog's General Store in Minas Morgul. "
      + "It looks rather run-down and sleazy. "
      + "Here you can sell or buy all kind of things at whatever " 
      + "price Bolzog is offering or asking. He has made a poster, "
      + "which you can read if you like. Bolzog will value things "
      + "if you want him to. Sometimes, he is also looking for "
      + "someone to deliver packets for him to distant places. "
      + "The exit leading into Dark Street is to the east."));
    set_short("Bolzog's General Store in Minas Morgul");
    set_shop_name("Bolzog's General Store");
    set_keeper_file(MORGUL_DIR + "npc/bolzog");
    set_no_sell_prop(GONDOR_M_MORGUL_NO_SELL);

    add_item(({"street","dark street"}), BSN(
        "To the east, you can see narrow Dark Street running from north "
      + "to south. "));

    add_exit(MORGUL_DIR + "city/darkstr2", "east", block_keeper);

    set_office("Bolzog's General Store in Minas Morgul", 10);
    add_content(MORGUL_DIR + "obj/friedelf");
    add_content(MORGUL_DIR + "obj/spider");
    add_content(MORGUL_DIR + "obj/ltunic");
    reset_room();
}

string
exa_poster()
{
    return
        "This is Bolzog's General Store!\n" +
        "Keep your dirty hands from the inventory, or I will cut them off!\n" +
        "Use these instructions or be gone:\n"+
        "    buy lamp for gold and get copper back\n" +
        "    buy lamp for gold coins\n" +
        "    sell lamp for copper coins\n" +
        "    sell all  - will let you sell all items except for\n" +
        "                weapons and armours.\n" +
        "    sell all! - will let you sell ALL items you have, well\n" +
        "                at least the droppable, and no coins.\n" +
        "    sell lamp, sell second lamp, sell lamp 2, sell two lamps\n" +
        "                also works. You might want to change the verb to\n" +
        "                'value' or 'buy' too. \n" +
        "                I sell only one item at a time, though! \n" +
        "    If you want a list of all lamps available in the store, the\n" +
        "    correct syntax is: list lamps\n" +
        "Delivery tours:\n" +
        "    ask for a delivery tour\n" +
        "    deliver packet - to deliver a packet here.\n" +
        "    return packet  - to return a packet you do not want to deliver.\n\n";
        "";
}

public void
print_message(string str)
{
    keeper->command("say " + str);
}

void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("say Where did you get this " +
        ob->short() + "?");
    keeper->command("glare " + pl->query_real_name());
    keeper->command("say Only soldiers in the Dark Lord's " +
        "army have this kind of equipment!");
    keeper->command("say If you think I'm fool enough to " +
        "buy this, you got the wrong one!");
    keeper->command("say Leave before I call the guards!");
}

void
shop_hook_no_business(object pl)
{
    keeper->command("say I do not want your business, " +
        "you stupid creep!");
    keeper->command("spit " + pl->query_real_name());
    keeper->command("say Leave before I call the guards!");
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    object  tp = TP;
    string race;
    int bargain = tp->query_skill(SS_TRADING);

    if(bargain > 30)
        bargain = 30;
    bargain = 115 - bargain;

    switch(query_feeling(TP))
    {
        case -1: bargain = (bargain *  85) / 100; break;
        case  0: break;
        case  1: bargain = (bargain * 120) / 100; break;
    }
    return bargain;
}

void
init()
{
    init_office();
    ::init();
}

void
reset_room()
{
    reset_office();
    ::reset_room();
}

/*
 *  Bendar's General Store in Edoras
 *
 *  added the delivery support
 *               Olorin,                 May  1995
 *  modified to use /d/Gondor/common/lib/shop.c
 *               Olorin,                 July 1994
 *  changed so that weapons and armours will not be bought
 *               Olorin,                 July 1994
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 */
inherit "/d/Gondor/common/lib/shop";
inherit "/d/Genesis/delivery/office";
inherit "/d/Faerun/lib/shop_list";


#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/mordor/sys/clock.h"

#define STORE_ROOM EDORAS_DIR + "store"  /* Where the items are stored */

int sunrise();

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("Bendar's General Store");
    set_long(BSN(
        "You stand in Bendar's General Store. Here you can sell or buy all kind "
      + "of things, except weapons and armours. Many other things are sold at a "
      + "reasonable price. The owner has made a poster, which you can read if "
      + "you like. The shopkeeper can value things if you want him to. Bendar "
      + "is also trading in valuable goods. Sometimes he has packets to be "
      + "delivered to places near or far. The street is to the east and the "
      + "storeroom is to the west."));
    set_shop_name("Bendar's General Store");
    set_keeper_file(EDORAS_DIR + "npc/bendar");
    set_no_sell_prop(GONDOR_M_ROHIRRIM_NO_SELL);
    set_hated_race(({"goblin"}));
    set_suspected_race(({"dwarf", "elf", "gnome"}));
    set_favoured_race(({"human"}));

    add_exit(EDORAS_DIR + "path5", "east", 0);
    add_exit(STORE_ROOM, "west", "@@wiz_check");

    set_office("Bendar's General Store in Edoras", 10);
    add_content(EDORAS_DIR + "obj/diamond");
    add_content(EDORAS_DIR + "obj/robe");
    CLOCK->notify_dawn(sunrise);
}

string
exa_poster()
{
    return "\nWelcome to the Bendar's General Store!\n" +
         "You can try these instructions: \n" +
        "    buy lamp for gold and get copper back\n" +
        "    buy lamp for gold coins\n" +
        "    sell lamp for copper coins\n" +
        "    sell all  - will let you sell all items except for\n" +
        "                weapons and armours.\n" +
        "    sell lamp, sell second lamp, sell lamp 2, sell two lamps\n" +
        "                also works. You might want to change the verb to\n" +
        "                'value' or 'buy' too.\n" +
        "    If you want a list of all the lamps available in the store,\n"+
        "    the correct syntax is: 'list lamps'.\n\n"+
        "Delivery tours:\n" +
        "    ask for a delivery tour\n" +
        "    deliver packet - to deliver a packet here.\n" +
        "    return packet  - to return a packet you do not want to deliver.\n\n";
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
    keeper->command("say It is of Rohirrim manufacture,");
    keeper->command("say you must have stolen it ... or worse!");
    keeper->command("say Leave before I call the guards!");
}

void
sunrise()
{
    CLOCK->notify_dawn(sunrise);
    if (objectp(keeper))
        keeper->open_shop();
}

void
init()
{
    ::init();

    init_office();
}

void
reset_room()
{
    reset_office();
    ::reset_room();
}

/*
 *  Alwine's Armoury in Edoras
 *  modified to use /d/Gondor/common/lib/shop.c
 *  Olorin, July 1994
 *  changed to trade only in weapons and armours
 *    Olorin,                            July 1994
 *  changed so that weapons and armours of Rohirrim fabrication will not
 *    be bought, Olorin,                 July 1994
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 */
inherit "/d/Gondor/common/lib/shop";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/mordor/sys/clock.h"

#define STORE_ROOM EDORAS_DIR + "armoury_store"  /* Where the items are stored */

int sunrise();

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("Alwine's Armoury");
    set_shop_name("Alwine's Armoury");
    set_long(BSN(
        "You stand in Alwine's Armoury. Here you can sell or buy all kinds "
      + "of weapons and armours. Alwine, the owner, has made a poster, which "
      + "you can read if you like. He can value weapons and armours if you "
      + "want him to. To buy or sell items that are neither armours nor "
      + "weapons, please visit Bendar's General Store. The street is to "
      + "the west and the storeroom is to the east."));

    set_keeper_file(EDORAS_DIR + "npc/alwine");
    set_no_sell_prop(({GONDOR_M_ROHIRRIM_NO_SELL, GONDOR_M_TIRITH_NO_SELL }));
    set_hated_race(({"goblin"}));
    set_suspected_race(({"dwarf", "elf", "gnome"}));
    set_favoured_race(({"human"}));

    add_exit(EDORAS_DIR + "path4", "west", 0);
    add_exit(STORE_ROOM, "east", "@@wiz_check");
    CLOCK->notify_dawn(sunrise);
}

mixed
shop_hook_filter_sell(object x)
{
    if (!weapon_filter(x) && !armour_filter(x))
        return "The shopkeeper says: I do not want your " + x->short() + "!\n" +
               "The shopkeeper says: I do not trade in anything but weapons and armours!\n";
    else
        return 0;
}

void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("say Where did you get this " +
        ob->short() + "?");
    keeper->command("glare " + pl->query_real_name());
  if (ob->query_prop(GONDOR_M_ROHIRRIM_NO_SELL)) 
    keeper->command("say It is of Rohirrim manufacture,");
  else if (ob->query_prop(GONDOR_M_TIRITH_NO_SELL))
    keeper->command("say It is typical equipment from the Mundburg! So");
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

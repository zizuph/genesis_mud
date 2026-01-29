/*
 *  Herb Shop in Minas Tirith
 *
 *  Copied from herb shop in Minas Morgul
 *
 *  Olorin, 14-nov-1994
 *
 *  Modification Log:
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herb_shop";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    FIX_EUID

    /* this line needed to created default trade configuration */
    config_default_trade();

    set_money_greed_buy(60);
    set_money_greed_sell(150);

    set_short("The Herb Shop of Minas Tirith");
    set_long(BSN(
        "This is the Herb Shop of Minas Tirith in the Fifth Circle of the "
      + "City. The narrow doorway is leading out onto Main Street. "
      + "On a narrow wooden counter stands a sign. "
      + "Hooks in the ceiling hold bunches of drying herbs."));

    /* set the room to be used as storage room for this shop */
    set_store_room(MINAS_DIR + "rooms/herb_storage");
    call_other(store_room, "load_me");

    add_item(({"roof","ceiling"}), BSN(
        "From the high vaulted ceiling several hooks are hanging."));
    add_item(({"sign", "poster"}), read_sign());
    add_cmd_item(({"sign", "poster"}), "read", read_sign());
    add_item(({"small shop", "herb shop","shop"}), BSN(
        "In the ground floor of this building is a herb shop. Here you can " +
        "buy and sell herbs."));
    add_item(({"counter", "wooden counter"}), BSN(
        "A simple wooden counter made from rough boards. On the " +
        "counter, you can see a sign."));
    add_item(({"windows"}), "There are no windows here.\n");
    add_item(({"hooks", "hook"}), BSN(
        "Wrought iron. From some of them are hanging dried herbs, " +
        "but they are out of your reach."));
    add_item(({"herbs", "herb", "bunches of herbs", "bunches"}), "Herbs, "+
          "tied in bunches, hanging from the ceiling to dry.\n");

    add_exit(MINAS_DIR + "e2crc5", "west", 0);

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
}

void
init()
{
    ::init();

    init_herb_shop();
}

string
read_sign()
{
   return "\t __________________________________________\n" +
          "\t/                                          \\\n" +
          "\t|      The Herb Shop of Minas Tirith       |\n" +
          "\t|     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      |\n" +
          "\t|         We sell and buy herbs.           |\n" +
          "\t|    From our large stock, we also sell    |\n" +
          "\t|    jars, pouches and cords, but we do    |\n" +
          "\t|          not buy these items!            |\n" +
          "\t|       You can list what we offer.        |\n" +
         "\t\\__________________________________________/\n";
}


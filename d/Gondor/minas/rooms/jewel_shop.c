/*
 * A jeweller's shop in Minas Tirith
 *
 * Coded by Olorin, 10-nov-1994
 *
 * TODO:
 * Add a gold smith.
 * The gold smith can make rings, necklaces, and carcanets
 * from copper, silver, gold, platinum (use coins!). Into the
 * jewelry, the gold smith can set gems from the jeweller.
 * The player will have to give the gold smith the gems, the coins for
 * metal and then he has to pay for the work done.
 *
 */
inherit "/d/Gondor/common/lib/gem_shop";

#include "/d/Gondor/defs.h"

#define STORE_ROOM	(MINAS_DIR + "rooms/jewel_store")
#define LIVE_I_KRYNN_GEM   "_live_i_krynn_gem"

void
init()
{
    ::init();

    init_shop();
}

void
create_shop()
{
    set_short("Jeweller's Shop in Minas Tirith");
    set_long(BSN(
             "This is the shop and the workshop of Sarndil, goldsmith and "
           + "jeweller of Gondor. In the background of the room, close to a "
           + "window going south stands a work bench covered with the tools "
           + "of Sanrdil's profession. Besides working in precious metals, "
           + "Sarndil also trades in gems of many different kinds.")
           + BSN("In the not too distant future Sarndil will hopefully offer "
           + "to work the metal of coins into rings, coronets, and necklaces "
           + "into which gems can be set - all for a price, of course!"));

    set_store_room(STORE_ROOM);
    set_shop_name("Sarndil's Jewellery");
    set_keeper_file("/d/Gondor/minas/npc/sarndil");

    setup_gem_shop();

    add_exit(MINAS_DIR + "s2crc4", "north", 0, 0);

    add_item(({"window"}), BSN(
        "The window goes out into a large court between the building and "
      + "the Fourth Wall south of it."));
    add_item(({"work bench", "bench", "tools"}), BSN(
        "The work bench is covered with many different tools. Sarndil seems "
      + "to be in the habit of working on new jewellery while waiting for "
      + "customers to visit his shop."));
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy diamond for gold and get copper back\n"
      + "    buy diamond for gold coins\n"
      + "    sell diamond for copper coins\n"
      + "    sell all  - will let you sell all gems.\n"
      + "    list      - will list all gems in stock.\n"
      + "    value diamond - will give an estimate on the price.\n"
      + "\n";
}


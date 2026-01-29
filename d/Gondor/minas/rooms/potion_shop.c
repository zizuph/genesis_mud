/*
 *  Potion Shop
 *
 *  Originally coded by Falke@Angalon as herb shop
 *  Modified for Minas Morgul in Gondor@Genesis by Olorin, July 1994
 *
 *  Modification Log:
 */
inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/potion_shop";

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

   set_short("The Alchemist's Shop in Minas Tirith");
   set_long(BSN("This is the Alchemist's Shop in the Fifth Circle of "
     + "Minas Tirith. Through the narrow doorway to the north Main "
     + "Street is visible. On a stone bench which serves as counter "
     + "stands a sign. Behind the counter, there are many wooden "
     + "boards filled with bottles, vials, mortars."));

   /* set the room to be used as storage room for this shop */
   set_store_room(MINAS_DIR + "rooms/potion_storage");
   call_other(store_room, "load_me");

   add_item(({"sign", "poster"}), read_sign());
   add_cmd_item(({"sign", "poster"}), "read", read_sign());
   add_item(({"small shop", "alchemist's shop","shop"}), BSN(
       "On the street level of this building an alchemist buys and sells " +
       "the tools of his trade and all kinds of potions."));
   add_item(({"counter", "high stone bench", "stone bench", 
       "high bench", "bench"}), BSN(
       "This is a narrow stone slab standing on one of its small " +
       "sides. The alchemist uses it as a counter. On it, there is " +
       "a sign with something written on it."));
   add_item(({"windows"}), "There are no windows here.\n");
   add_item(({"board", "boards"}), BSN(
       "There are many different things on the board. Some of them " +
       "you can buy, others are probably so valuable to the alchemist " +
       "that he is unlikely to be willing to part with them. Among " +
       "other items you can make out bottles filled with potions, " +
       "empty vials and a large collection of mortars on the boards."));
   add_item(({"mortar", "mortars", "vial", "vials"}), BSN(
       "On one board there are empty vials and mortars presented " +
       "for sale. If you have enough coins you can equip yourself " +
       "here with the tools of trade of an alchemist."));
   add_item(({"bottle", "bottles"}), BSN(
       "Some bottles are empty, others are filled with liquids or " +
       "pills. Perhaps some of the potions and pills are for sale, " +
       "but probably not all are."));

   add_exit(MINAS_DIR + "e1crc5", "north", 0);

   add_prop(ROOM_I_LIGHT, 1); 
   add_prop(ROOM_I_INSIDE, 1); 
}

void
init()
{
   ::init();

   init_potion_shop();
}

string
read_sign()
{
   return "\t ___________________________________________\n" +
          "\t/                                           \\\n" +
          "\t|         The Alchemist's Provider          |\n" +
          "\t|        ~~~~~~~~~~~~~~~~~~~~~~~~~~         |\n" +
          "\t|         We sell and buy potions.          |\n" +
          "\t| From our large stock, we also sell vials  |\n" +
          "\t|   and mortars, but we do not buy them!    |\n" +
          "\t|         We sell and buy potions.          |\n" +
          "\t|        You can list what we offer.        |\n" +
          "\t\\___________________________________________/\n";
}


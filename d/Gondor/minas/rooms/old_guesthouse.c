/*
 *  The Sleeping Stallion
 *  
 *  copied from the Seven Stars Inn
 *
 *  created by Elessar.
 *  modified for The Sleeping Stallion by Olorin on 6-jan-93
 *  again modified for the Old Guesthouse in Minas Tirith, by Elessar, 14/1-93
 *  partly rewritten by Olorin, Nov 1995
 */
inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/lib/inn.c";
inherit "/d/Gondor/minas/lib/minas_fof.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define STAND_DIR	(RANGER_DIR + "obj/")
#define MY_PRICES	({ 3, 8, 12, 36, 75, 12, 24, 48, 216, 540, 144})

string  price_long();

void
create_room()
{
   set_short("the Old Guesthouse");
   set_long(BSN(
      "You are in the Old Guesthouse, an old inn. Here you can eat and "
    + "drink to your heart's delight, or order a room for the night. "
    + "Most of the tables here are already occupied by "
    + "travellers or by traders, who came to Minas Tirith for business, and "
    + "now are feasting on the excellent meals offered in this inn. By the "
    + "north wall is a counter. In front of it several Gondorian men are "
    + "standing, drinking beer. Behind the counter, the innkeeper is working. "
    + "On the wooden floor lies a rug, which has seen better times. It is "
    + "worn out, covered with dirt, pipe ashes and holes. A few lamps are "
    + "hanging from the ceiling, creating a nice atmosphere. To the left of "
    + "the counter are stairs leading upstairs to a room where one can "
    + "stay for the night. On the wall behind the counter is a pricelist and "
    + "menu."));
   add_item("rug", "The rug was once beautiful and red, but now it is grey "
    + "and full of holes.\n");
   add_item(({"table","tables","chair","chairs"}),
      "Most of the tables are free, but some are occupied by the Gondorian "
   	+ "customers of this inn.\n");
   add_item("counter", BSN(
      "Above the wooden counter is a lamp and a shelf. On the shelf are "
    + "several brands of liquor. Behind the counter is the innkeeper of the "
    + "Old Guesthouse. On the wall behind the counter there hangs a "
    + "pricelist and menu."));
   add_item(({"innkeeper","barkeeper","bartender"}), BSN(
      "The innkeeper is a very corpulent, almost fat, rohirrim man. He does "
    + "not seem to work much, but surprisingly, everyone is served promptly "
    + "in this inn. From the frequent glances that he keeps casting at you, "
    + "you conclude that he expects you to order something."));
   add_item(({"pricelist","list","prices","menu"}), price_long());
   add_cmd_item(({"pricelist","list","prices","menu"}), "read", price_long());

   add_exit(MINAS_DIR + "n1crc1","south",0,1);
   add_exit(MINAS_DIR + "rooms/innroom","up",0,2);

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

   config_default_trade();
   set_money_give_max(2000);
   set_money_give_out(({ 2000, 700, 50, 4}));
   set_money_give_reduce(({1,1,1,1})); 
}

void
init()
{
   ::init();

   init_inn();
}

string
price_long()
{
   return (
      "The pricelist reads:\n\n"
    + "DRINKS:\n"
    + "   Water                 ...  " + money_text(MY_PRICES[0]) + "\n"
    + "   Golden Ale            ...  " + money_text(MY_PRICES[1]) + "\n"
    + "   Prime Beer            ...  " + money_text(MY_PRICES[2]) + "\n"
    + "   Wine from Ithilien    ...  " + money_text(MY_PRICES[3]) + "\n"
    + "   Whiskey from Rohan    ...  " + money_text(MY_PRICES[4]) + "\n\n"
    + "HOT MEALS:\n"
    + "   Porridge              ...  " + money_text(MY_PRICES[5]) + "\n"
    + "   Vegetable stew        ...  " + money_text(MY_PRICES[6]) + "\n"
    + "   Bacon and beans       ...  " + money_text(MY_PRICES[7]) + "\n"
    + "   Pheasant              ...  " + money_text(MY_PRICES[8]) + "\n"
    + "   Stag steak            ...  " + money_text(MY_PRICES[9]) + "\n\n"
    + "ROOMS:\n"
    + "   Key for a room        ...  " + money_text(MY_PRICES[10]) + "\n\n");
}

public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    switch (item_name)
    {
        case "water":
            if (can_afford(MY_PRICES[0], number, "water", pay_type, get_type))
                buy_item(STAND_DIR + "water", number);
            break;
        case "ale":
        case "golden ale":
            if (can_afford(MY_PRICES[1], number, "golden ale",
                pay_type, get_type))
                buy_item(STAND_DIR + "ale", number);
            break;
        case "beer":
        case "prime beer":
            if (can_afford(MY_PRICES[2], number, "prime beer",
                pay_type, get_type))
                buy_item(STAND_DIR + "beer", number);
            break;
        case "wine":
        case "wine from ithilien":
            if (can_afford(MY_PRICES[3], number, "wine from Ithilien",
                pay_type, get_type))
                buy_item(STAND_DIR + "wine", number);
            break;
        case "whiskey":
        case "whiskey from rohan":
            if (can_afford(MY_PRICES[4], number, "whiskey from Rohan",
                pay_type, get_type))
                buy_item(STAND_DIR + "whiskey", number);
            break;
        case "porridge":
            if (can_afford(MY_PRICES[5], number, "porridge",
                pay_type, get_type))
                buy_item(STAND_DIR + "porridge", number);
            break;
        case "stew":
        case "vegetable stew":
            if (can_afford(MY_PRICES[6], number, "vegetable stew",
                pay_type, get_type))
                buy_item(STAND_DIR + "stew", number);
            break;
        case "beans":
        case "bacon":
        case "bacon and beans":
            if (can_afford(MY_PRICES[7], number, "bacon and beans",
                pay_type, get_type))
                buy_item(STAND_DIR + "beans", number);
            break;
        case "pheasant":
            if (can_afford(MY_PRICES[8], number, "pheasant",
                pay_type, get_type))
                buy_item(STAND_DIR + "pheasant", number);
            break;
        case "stag":
        case "steak":
        case "stag steak":
            if (can_afford(MY_PRICES[9], number, "stag steak",
                pay_type, get_type))
                buy_item(STAND_DIR + "steak", number);
            break;
        case "room":
        case "key":
        case "key for a room":
        case "single room":
        case "night":
            if (query_friend_or_foe(TP) == -1)
            {
                write("The innkeeper glares at you.\n"+
                      "He says: I'll let you drink my ale and eat my food.\n"+
                      "        But I will not have filthy scum like you sleeping in my beds!\n");
                return 1;
            }
            if (number > 1)
            {
                write("Ths innkeeper says: I rent the rooms only one at a time, and only for one night.\n");
                return 1;
            }
            if (can_afford(MY_PRICES[10], number, "room", 
                pay_type, get_type))
            {
                buy_item(MINAS_DIR + "obj/guesthouse_key", number,
                    "a single room to spend the night in Minas Tirith");
                write("The innkeeper gives you the key to the room. Don't lose it!\n");
            }
            break;
        default:
            NF("The innkeeper says: We don't have that on the menu.\n");
            return 0;
            break;
    }

    return 1;
}


/*
 *  /d/Gondor/clubs/nisse/room/tavern.c
 *
 *  The Hawk's Nest Tavern of Nisse Ohtar.
 *
 *  Tigerlily & Deagol, April 2003
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/lib/inn.c";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

#define MY_PRICES ({10, 12, 48, 314, 180, 12, 24, 24, 24, 56, 216, 512})

/*
 *  Variables
 */
object	keeper;

/*
 *  Prototypes
 */
void	clone_npc();
string	exa_dishes();

void
create_room()
{
    set_short("the Hawk's Nest Tavern");
    set_long("For being a camp tent this room has a homey atmosphere. " +
        "There is a bar across from the entrance and comfortable wooden " +
        "benches and tables around the room. The tables and bar are " +
        "scoured clean and shiny with oil that prevents stains from " +
        "absorbing into the wood. There is a wonderful aroma of smoking " +
        "meat and bakery confections that make your mouth water. It is " +
        "warm from the camp stove and oven, and you notice a large basin " +
        "to the side that is filled with steaming soapy water and dishes. " +
        "There is a good deal of noise from the clattering of plates and " +
        "pans as well as the chatter of customers. You notice a stuffed " +
        "hawk mounted on the wall behind the bar, seeming to keep watch " +
        "over the customers.\n");

    add_item(({"hawk", "stuffed hawk"}),
        "This is a large, lifeless stuffed red-tailed hawk that, " +
        "nonetheless, almost looks alive. It watches over the bar with " +
        "haughty piercing glass eyes. There is a small sign attached " +
        "to the base that reads, 'Beloved Red, who will always live " +
        "on in memory.\n");
    add_item(({"tables", "benches", "bar"}),
        "There is a long bar that lies opposite the entrance and a number " +
        "of benches and tables for customers. They are scoured clean and " +
        "kept to a high polish. Clearly the owner of this establishment " +
        "values cleanliness.\n");
    add_item(({"floor", "ground"}),
        "While the floor is just hard-packed earth, it is nonetheless " +
        "kept swept clean.\n");
    add_item(({"camp oven", "oven", "stove"}),
        "You see a small kitchen behind the bar with an oven and camp " +
        "stove. It is remarkable how much food this small stove can " +
        "create. There are pots and pans on top of the stove bubbling " +
        "merrily and a little smoke now and then escapes from the oven. " +
        "The owner must work night and day to keep up with customers' " +
        "demand.\n");
    add_item(({"basin", "large basin", "water", "soapy water"}),
        "Clearly all the cooking and eating activities create lots of " +
        "dirty dishes! The cook can always use a hand with cleaning up!\n");
    add_item(({"customers"}),
        "This is a very active place with people just like you who come in " +
        "with a big thirst and empty bellies!\n");
    add_item(({"pricelist", "list", "prices", "menu"}), price_long());
    add_item(({"dishes", "plates", "pans", "pots"}), &exa_dishes());
    add_cmd_item(({"pricelist", "list", "prices", "menu"}),
        "read", price_long());

    config_default_trade();

    set_money_give_max(2000);
    set_money_give_out(({2000, 700, 50, 4}));
    set_money_give_reduce(({1, 1, 1, 1}));

    add_prop(ROOM_I_INSIDE, 1);
    
    clone_npc();
    
    add_exit(NISSE_ROOM_DIR + "path1", "out", 0, 0, 0);
}

/*
 *  Function name: exa_dishes
 *  Description  : Gives a different description of dishes according to
 *                 the status of dishes_flag.
 *  Returns      : strings
 */
string
exa_dishes()
{
    keeper = present(NISSE_COOK_ID, TO);

    if (!(keeper->query_dishes_flag()))
    {
        return "You look for dirty dishes in the basin, but someone has " +
            "just washed up. Do not worry! There will be more soon.\n";
    }
    
    return "You seek for dirty dishes. You spot a heap of dishes in the " +
        "basin. Maybe you can help this poor hobbit and wash them?\n";
}

/*
 *  Function name: clone_npc
 *  Description  : Clone the barkeeper.
 */
void
clone_npc()
{
    object npc = clone_object(NISSE_NPC_DIR + "cook");
    
    set_innkeeper_npc(npc);
    npc->move(TO);
}

/*
 * Function name: price_long
 * Description:   It prints the menu.
 */
string
price_long()
{
   return (
      "The menu reads:\n\n" +
      "DRINKS:\n" +
      "   Apple juice           ...  " + money_text(MY_PRICES[0]) + "\n" +
      "   Ice tea               ...  " + money_text(MY_PRICES[1]) + "\n" +
      "   Hot grog              ...  " + money_text(MY_PRICES[2]) + "\n" +
      "   Dwarven ale           ...  " + money_text(MY_PRICES[3]) + "\n" +
      "   Miruvor               ...  " + money_text(MY_PRICES[4]) + "\n\n" +
      "MEALS:\n" +
      "   Bread with bacon      ...  " + money_text(MY_PRICES[5]) + "\n" +
      "   Mincemeat cookies     ...  " + money_text(MY_PRICES[6]) + "\n" +
      "   Bran muffin           ...  " + money_text(MY_PRICES[7]) + "\n" +
      "   Potato scone          ...  " + money_text(MY_PRICES[8]) + "\n" +
      "   Green tomatoes        ...  " + money_text(MY_PRICES[9]) + "\n" +
      "   Smoked dried meat     ...  " + money_text(MY_PRICES[10]) + "\n" +
      "   Cake of cram          ...  " + money_text(MY_PRICES[11]) + "\n\n" +
      BSN("Try 'order juice for gold' if you want to specify what to pay " +
      "with. You can also specify 'order 3 juices' to get three juices. " +
      "There is a maximum of " + hook_query_max_items() + " " +
      "items you can order at one time."));
}

/*
 *  Function name: hook_query_max_items
 *  Description  : Sets the number of items a player can buy at once.
 *  Returns      : int - number of items
 */
public int
hook_query_max_items()
{
    return 10;
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy an item.
 * Arguments:     string str - describing how to pay and get change
 * Returns:       1 on sucess
 */
public int
do_buy(string str)
{
    object  player = TP;
    
    keeper = present(NISSE_COOK_ID, TO);

    if (!strlen(str))
    {
        notify_fail(CAP(query_verb()) + " what?\n");
        return 0;
    }

    if (query_prop(OBJ_I_LIGHT) < 1)
    {
        if (CAN_SEE_IN_ROOM(player))
        {
            keeper->command("say Sorry, it's too dark in here, I can't " +
                "see!\n");
        }
        else
            keeper->command("say Sorry, it's too dark in here, I can't " +
                "see!\n");
        return 1;
    }

    return ::do_buy(str);
}

/*
 * Function name: buy_it
 * Description:   Identify the item the player tries to buy.
 * Arguments:     item_name - the name
 *                number    - the amount
 *                pay_type  - coins to pay with
 *                get_type  - coins for change
 * Returns:       0/1 - failure/success
 */
public int
buy_it(string item_name, int number, string pay_type, string get_type)
{
    string	file;
    string	ware;
    int		price;

    keeper = present(NISSE_COOK_ID, TO);

    switch (item_name)
    {
	case "juice":
	case "juices":
	case "apple juice":
	case "apple juices":
	    file = "juice";
	    ware = "big tumbler of apple juice";
	    price = MY_PRICES[0];
	    break;
        case "tea":
        case "teas":
        case "ice tea":
        case "ice teas":
            file = "ice_tea_lemon";
            ware = "dewy glass of ice tea with slice of lemon";
            price = MY_PRICES[1];
            break;
        case "grog":
        case "grogs":
        case "hot grog":
        case "hot grogs":
            file = "grog";
            ware = "mug of hot grog";
            price = MY_PRICES[2];
            break;
        case "ale":
        case "ales":
        case "dwarven ale":
        case "dwarven ales":
            file = "dwarven_ale";
            ware = "glass of dwarven ale";
            price = MY_PRICES[3];
            break;
        case "miruvor":
        case "miruvors":
        case "flask of miruvor":
        case "flasks of miruvor":
            file = "miruvor";
            ware = "a small flask of miruvor";
            price = MY_PRICES[4];
            break;
        case "bread":
        case "breads":
        case "bread with bacon":
        case "breads with bacon":
        case "slab of bread":
        case "slabs of bread":
        case "slab of bread with bacon":
        case "slabs of bread with bacon":
            file = "bread";
            ware = "slab of bread with bacon";
            price = MY_PRICES[5];
            break;
        case "cookies":
        case "mincemeat cookies":
        case "sack of mincemeat cookies":
        case "sacks of mincemeat cookies":
            file = "cookies";
            ware = "small sack of mincemeat cookies";
            price = MY_PRICES[6];
            break;
        case "muffin":
        case "muffins":
        case "bran muffin":
        case "bran muffins":
            file = "muffin";
            ware = "bran muffin";
            price = MY_PRICES[7];
            break;
        case "scone":
        case "scones":
        case "potato scone":
        case "potato scones":
            file = "scone";
            ware = "potato scone";
            price = MY_PRICES[8];
            break;
        case "tomatoes":
        case "green tomatoes":
        case "half dozen of green tomatoes":
        case "half dozens of green tomatoes":
            file = "tomatoes";
            ware = "half dozen of green tomatoes";
            price = MY_PRICES[9];
            break;
        case "meat":
        case "meats":
        case "dried meat":
        case "dried meats":
        case "smoked dried meat":
        case "smoked dried meats":
            file = "meat";
            ware = "smoked dried meat";
            price = MY_PRICES[10];
            break;
        case "cram":
        case "crams":
        case "cake of cram":
        case "cakes of cram":
            file = "cram";
            ware = "cake of cram";
            price = MY_PRICES[11];
            break;
        default :
            keeper->command("say We don't have that on the menu.");
            return 1;
    }

    if (can_afford(price, number, ware, pay_type, get_type))
        buy_item(NISSE_OBJ_DIR + file, number);
    return 1;
}

void
init()
{
    ::init();

    init_inn();
}

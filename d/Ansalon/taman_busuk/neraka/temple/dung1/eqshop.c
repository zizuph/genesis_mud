/* Ashlar, 20 Oct 97 */
/* The code to sell standard items is from somewhere,
   can't remember exactly where. The old WOHS code I think.
   Credits where they are due anyway. Thanks a lot, sorry I
   can't remember where I took it.
*/

#include "../defs.h"
#include <files.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Ansalon/guild/new_pot/guild.h"
#include "/d/Ansalon/common/defs.h"

inherit TEMPLE + "std_temple";
inherit "/lib/shop";

mixed *standard_items =
    ({
    	// ({ "mortar" }), "/d/Genesis/std/potions/mortar", 720,
    	// ({ "vial", "empty vial" }), POTION_VIAL_OBJECT, 24,
        ({ "phial", "empty phial" }), GUILDDIR + "rituals/obj/phial", 24,
    	({ "pouch", "component pouch" }), GUILDDIR + "obj/comp_pouch", 120,
    	({ "pack", "backpack" }), GUILDDIR + "obj/backpack", 480,
        ({ "sack", "kender-hide sack" }), GUILDDIR + "obj/sack", 300,
    	({ "needle" }), GUILDDIR + "obj/needle", 67,
    	({ "gloves" }), GUILDDIR + "obj/leat_gloves", 240,
        ({ "clerical robe", "robe" }), GUILDDIR + "obj/clerical_robe", 420,
        ({ "sheath" }), GUILDDIR + "obj/sheath", 600,
        ({ "oil lamp", "lamp" }), "/d/Gondor/common/obj/oil_lamp", 156,
        ({ "flask of oil", "flask", "oil flask", "oil" }), "/d/Gondor/common/obj/oilflask", 180,
    });
int gCannotPay = 0;    	
    	

string
read_sign()
{
    return "The sign reads:\n\n" +
    "The Temple Equipment shop.\n\n" +
    "You can <list> to get a list of the equipment in stock, " +
    "and then you can <buy> any of them. You can also ask " +
    "the shopkeeper to <show> any of the items.\n\n" +
    "There are some standard items available, they are priced as " +
    "follows;\n\n" +
    // "   Mortar ........................ 5 gc\n" +
    // "   Empty vial .................... 2 sc\n" +
    "   Empty phial ...................  2 sc\n" +
    "   Component pouch ............... 10 sc\n" +
    "   Backpack ...................... 40 sc\n" +
    "   Sack .......................... 25 sc\n" +
    "   Needle ........................  5 sc\n" +
    "   Gloves ........................ 18 sc\n" +
    "   Clerical robe ................. 35 sc\n" +
    "   Knife sheath .................. 50 sc\n" +
    "   Flask of oil .................. 15 sc\n" +
    "   Oil lamp ...................... 13 sc\n" +
    "\n";
}

void
create_temple_room()
{
    ::create_temple_room();

     set_short("equipment shop in the temple");
    set_long("This is a small room that serves as an equipment shop " +
        "for the Priests of Takhisis. Here standard equipment can be " +
        "purchased for a reasonable sum. There is a sign hanging on one " +
        "wall. A doorway leads northeast out of the room.\n");

    add_item(({"doorway","small doorway"}), "The doorway is decorated " +
        "with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}), "The frame is " +
        "made of wood, but you cannot discern the type of wood. The " +
        "white paint contrasts nicely with the darker walls.\n");

    add_item("sign","@@read_sign");
    add_cmd_item("sign","read","@@read_sign");

    config_default_trade();
    set_money_greed_buy(90);
    set_money_greed_sell(85);

    set_store_room(DUNGONE + "eqstore");

    setuid();
    seteuid(getuid());
    
    clone_object(DOOR + "eqshop2")->move(this_object());
//    add_exit(DUNGONE + "corr8", "northeast");
}

/*
 * Function name: buy_standard_item
 * Description:   Try to let the player buy the item array
 * Arguments:     ob - the object array
 *                str2 - string describing how the money should be paid
 *                str3 - what coin types to get chainge back in
 *                price - the price for the item
 * Returns:       bought items
 */
object *
buy_standard_item(object *ob, string str2, string str3, int price) 
{
    int i, j, k, *value_arr, *arr, error, num, err;
    object *bought;
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0; i < sizeof(ob); i++)
    {
        if (!shop_hook_allow_buy(ob[i]))
            continue;

        if (tmp = ob[i]->query_prop(OBJ_M_NO_BUY))
        {
            shop_hook_buy_no_buy(ob[i], tmp);
            continue;
        }

        if (err, ob[i]->move(this_player()))
        {
            shop_hook_buy_cant_carry(ob[i], err);
            continue;
        }

	if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
        {
            ob[i]->remove_object();
//            shop_hook_buy_cant_pay(ob[i], arr);
            continue;  /* pay() can handle notify_fail() call */
        }

	/* Detect if there was a move error. */
        if (error = arr[sizeof(arr) - 1])
        {
            if (error < -1)
            {
                /* Couldn't take the money from player, the coins were stuck */
                shop_hook_buy_magic_money(ob[i]);
                ob[i]->remove_object();
                continue;
	    }

            /* We don't want the money so no move error to us, if there was
             * one it was because the player couldn't hold all coins, and if
             * so the drop text is already written, but the deal is still on :)
             */
        }

        for (k = 0; k < 2 * num; k++)
            value_arr[k] += arr[k];

        bought[j] = ob[i];
        j++;
        if (j >= 1)
       	    break;
        /* Well, we don't want to let a player accidentily buy too much :) */
    }

    bought = bought - ({ 0 });

    if (sizeof(bought) > 0)
        shop_hook_buy_pay_money(text(arr[0 .. num - 1]),
            text(arr[num .. 2 * num - 1]));

    return bought;
}

void
shop_hook_buy_cant_pay(object ob, int *arr)
{
    write("You cannot afford that.\n");
    gCannotPay = 1;
}

/*
 * Function name: do_buy_standard_item
 * Description:   Try to let the player buy an item
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy_standard_item(string str)
{
    object *item;
    int i;
    string str1, str2, str3;

    if (!str || str =="")
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    for (i = 0; i < sizeof(standard_items); i += 3)
    {
    	if (member_array(str1, standard_items[i]) >= 0)
    	{
            item = buy_standard_item(({ clone_object(standard_items[i+1]) }),
                str2, str3, standard_items[i+2] );
    	    if (sizeof(item))
                return shop_hook_bought_items(item);
            else
            {
                write("You cannot afford that.\n");
                return 1;
            }

            return 1;
    	}
    }

    return shop_hook_buy_no_match(str1);
}

int
do_buy(string a)
{
    if (::do_buy(a) || gCannotPay)
    {
        gCannotPay = 0;
        return 1;
    }

    return do_buy_standard_item(a);
}

int
do_sell(string a)
{
    NF("You cannot sell items in this shop.\n");
    return 0;
}

int
do_show(string a)
{
    return ::do_show(a);
}

int
do_list(string a)
{
    return ::do_list(a);
}

int
do_store(string a)
{
    if(!TP->query_wiz_level())
        return 0;
    return ::do_store(a);
}

void
init()
{
    ::init();
    add_action(do_buy,   "buy");
    add_action(do_sell,  "sell");
    add_action(do_show,  "show");
    add_action(do_list,  "list");
    add_action(do_store, "store");
}

/*
 * Function name: my_text
 * Description:   Generates a _compact_ text string from the array describing the coins
 * Arguments:     arr - the array holding the coins to describe
 */
mixed
my_text(int *arr)
{
    string *t_arr, coin_str;
    int i, j;
    
    t_arr = ({ });

    for (i = num_of_types - 1; i >= 0; i--)
    {
        if (arr[i] > 0)
        {
            j += arr[i]; /* Total number of coins */
            t_arr += ({ arr[i] + " " + ({"cc","sc","gc","pc"})[i] });
        }
    }

    j = sizeof(t_arr);

    if (j < 1)
        return;

    if (j == 1)
        return t_arr[0];
    else
        return implode(t_arr[0 .. j - 2], ", ") + " and " + t_arr[j - 1];
}
    

/*
 * Function name: shop_hook_list_object
 * Description:   List an object
 * Arguments:     ob - The object
 */
void
shop_hook_list_object(object ob, int price)
{
    string str, mess;

    str = sprintf("%-45s", capitalize(LANG_ASHORT(ob)));

    if (mess = my_text(split_values(price)))
        write(str + mess + ".\n");
    else
        write(str + "That item wouldn't cost you much.\n");
}


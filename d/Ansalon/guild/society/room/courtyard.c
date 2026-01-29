/* 
 * /d/Ansalon/guild/society/room/courtyard.c
 *
 * Modified by Gwyneth July - September, 1999
 * Ashlar, 20 Oct 97 
 * The code to sell standard items is from somewhere,
 * can't remember exactly where. The old WOHS code I think.
 * Credits where they are due anyway. Thanks a lot, sorry I
 * can't remember where I took it.
 */
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <language.h>
#include "../guild.h"
#include DL_CLOCK
#include <ss_types.h>
 
inherit KENDERMORE_OUT;
 
inherit "/lib/shop";

#define STORE_ROOM      KGROOM + "kstoreroom"
#define PLAYER_I_IS_ON_BENCH "_player_i_is_on_bench"

int rope_down, fruit_here;
object gStorekeeper, gDragon;

/* Standard items to be sold in the store without running out. */
mixed *standard_items =
    ({
    	({ "lamp", "blue lamp" }), KGOBJ + "blamp", 180,
        ({ "lamp", "red lamp" }), KGOBJ + "rlamp", 180,
        ({ "lamp", "multi-coloured lamp" }), KGOBJ + "mclamp", 180,
        ({ "yellow belt", "yellow pouch", "yellow pouch-belt", "pouch" }),
           KGOBJ + "ypouch", 180,
        ({ "blue belt", "blue pouch", "blue pouch-belt", "belt" }),
           KGOBJ + "bpouch", 180,
        ({ "green belt", "green pouch", "green pouch-belt", "pouch-belt" }),
           KGOBJ + "gpouch", 180,
        ({ "flask", "oil", "oil-flask" }), KGOBJ + "oilflask", 180,
        ({ "chalk", "white chalk" }), "/d/Krynn/solamn/thief/obj/chalk",
        180
    });
    	
    	

void
reset_kendermore_room()
{
    if (!objectp(gStorekeeper))
    {
        gStorekeeper = clone_object(KGNPC + "storekeeper");
        gStorekeeper->arm_me();
        gStorekeeper->move(this_object());
    }

    if (!objectp(gDragon))
    {
        gDragon = clone_object(KGOBJ + "dragon_statue");
        gDragon->move(this_object());
    }

    if (fruit_here != 1)
        fruit_here = 1;
}

/* Function name : long_descr
 * Description   : Returns the long description of the room depending on
 *                 weather and time of day.
 * Arguments     : None
 * Returns       : The long description
*/

string
long_descr()
{
    if (gStorekeeper)
        return (tod_descr() + season_descr() + " You've entered a grassy " +
        "courtyard. Four stone paths meet in the center, where two " +
        "stone benches have been placed. A few large cherry trees shade the " + 
        "benches. You can often see kender " +
        "chatting or telling stories here. One such kender sits on the " +
        "bench, his full pouches and pack sitting next to him. He listens " +
        "with wide-eyed interest as another old-timer spins a tale of adventure. " +
        "Occasionally, he will even contribute a story of his own. " +
        "The full pack draws your attention, as you can see various things " +
        "of interest sticking out of the top. A small sign is propped up " + 
        "next to him. Perhaps you could buy some of " +
        "this kender's findings.\n");

    else
        return (tod_descr() + season_descr() + " You've entered a grassy " +
        "courtyard. Four stone paths meet in the center, where two " +
        "stone benches have been placed. A few large trees shade the " + 
        "benches. You can often see kender " +
        "chatting or telling stories here. There is usually a kender " +
        "here who can be persuaded to sell some of his findings, but " +
        "it seems he's not here right now.\n");

}

/* Function name : change_rope
 * Description   : Allows other rooms to change the rope's position.
 * Arguments     : int i, 1 for down, 0 for up
 * Returns       : null
*/

void
change_rope(int i)
{
    if (i == 1)
        rope_down = 1;
    else
        rope_down = 0;
}

/* Function name : query_rope
 * Description   : Allows other rooms to find whether the rope is up or down.
 * Arguments     : None
 * Returns       : 1 if rope is down, 0 if up
*/

int
query_rope()
{
    if (rope_down == 1)
        return 1;
    else
        return 0;
}

/* Function name : read_sign
 * Description   : Gives a description of the sign when read or examined.
 * Arguments     : None
 * Returns       : The sign description.
*/

string
read_sign()
{
    return "The sign reads:\n\n" +
    "Miscellaneous things for sale!\n\n" +
    "You can <list> to get a list of the equipment in stock, " +
    "and then you can <buy> any of them. " +
    "There are some standard items available, they are priced as " +
    "follows;\n\n" +
    "   Blue glass lamp............... 15 sc\n" +
    "   Red glass lamp................ 15 sc\n" +
    "   Multi-coloured glass lamp..... 15 sc\n" + 
    "   Yellow belt of pouches........ 15 sc\n" +
    "   Blue belt of pouches.......... 15 sc\n" + 
    "   Green belt of pouches......... 15 sc\n" + 
    "   Flask of oil.................. 14 sc\n" + 
    "   Piece of chalk................ 14 sc\n" +
    "\n";
}

void
create_kendermore_room()
{
    set_short("A grassy courtyard");
    set_long("@@long_descr");
    add_item(({"benches", "stone benches", "bench", "stone bench"}), "The " +
        "stone benches are typically crowded with kender listening or " +
        "telling of their adventures.\n");
    add_item(({"pouches", "pack"}), "There is a large pack and several " +
        "stuffed pouches sitting on a bench next to a kender.\n");
    add_item("kender", "They are listening to and telling stories of their " +
        "adventures.\n");
    add_item(({"cherry trees", "trees", "large trees", "few trees", 
        "few large trees", "branches", "cherries", "cherry", "flowers", 
        "white flowers", "blossoms", "white blossoms", "cherry fruit",
        "fruit", "large cherry trees", "rope", "strong rope"}), "@@tree_desc");

    add_item("sign","@@read_sign");
    add_cmd_item("sign","read","@@read_sign");
    add_cmd_item(({"up", "up tree", "rope", "strong rope", "tree", "trees", 
        "large trees", "few trees",
        "few large trees", "cherry trees", "large cherry trees"}), "climb", 
        "@@climb_desc");
    add_cmd_item(({"cherries", "fruit", "cherry"}), "pick", "@@pick_fruit");
    add_cmd_item(({"legs", "feet"}), "swing", "@@bench_swing");

    add_prop(ROOM_M_NO_ATTACK, "The peaceful setting of the courtyard " + 
        "calms your mind.");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The peaceful setting of the " + 
        "courtyard calms your mind.");

    rope_down = 1;
    fruit_here = 1;
    reset_kendermore_room();

    add_exit(KGROOM + "joinroom", "north", 0);
    add_exit(KGROOM + "board_room", "east", "@@k_check");
    add_exit(KGROOM + "po", "west", "@@k_check");
    add_exit(KGROOM + "rack_room", "south", "@@k_check");

    config_default_trade();
    set_money_greed_buy(90);
    set_money_greed_sell(85);

    set_store_room(STORE_ROOM);
}


/* Function name : k_check
 * Description   : Blocks non members from going further into the guild.
 * Arguments     : None
 * Returns       : 1 for blocked people, 0 for members
*/

int
k_check()
{
    if (MEMBER(this_player()))
        return 0;

    write("Only members are allowed further.\n");
    return 1;
}

/* Function name : climb_desc
 * Description   : Allows the player to climb into the trees.
 * Arguments     : None
 * Returns       : ""
*/

string
climb_desc()
{
    if (rope_down)
    {
        if (this_player()->query_skill(SS_CLIMB) > (20 + random(10)))
        {
            write("You quickly climb up the rope into the " + 
                "branches of a cherry tree.\n");
            say(QCTNAME(this_player()) + " swings up the rope into the " + 
                "branches of a cherry tree.\n");
            tell_room(KGROOM + "cherry_tree", "The branches shake as " + 
                QTNAME(this_player()) + " swings up into the tree from " +
                "the rope.\n", this_player());
            this_player()->move_living("M", KGROOM + "cherry_tree", 0, 0);
            return "";
        }
        else
        {
            write("You try to climb the rope into the branches of the " + 
                "cherry tree, but slip and fall to the ground.\n");
            say(QCTNAME(this_player()) + " tries to climb the rope " +
                "into the branches of the cherry tree, but slips and " +
                "falls to the ground.\n");
            return "";
        }
    }
    else
    {
        return("The rope has been pulled up. Apparently someone is in the " + 
            "tree and wants some privacy.\n");
    }
}

/* Function name : pick_fruit
 * Description   : Pick cherries in the summer
 * Arguments     : None
 * Returns       : The description of the fruit picking
*/

string
pick_fruit()
{
    string str;
    switch(GET_SEASON)
    {
    case SPRING:
        str = "The only visible cherries are small and green. Leave them " + 
            "alone, and there will be delicious red cherries to be had.\n";
        break;
    case SUMMER:
        if (fruit_here < 6)
        {
            str = "You pick a handful of ripe red cherries.\n"; 
            clone_object(KGOBJ + "cherries")->move(this_player());
            fruit_here++;
        }
        else
            str = "The lower branches seem to have been picked clean of " + 
                "cherries!\n";
        break;
    case AUTUMN:
        str = "The only remaining cherries are only good for the birds.\n";
        break;
    case WINTER:
        str = "There aren't any cherries to be had!\n";
        break;
    }
    return str;
}

/* Function name : tree_desc
 * Description   : Gives a description depending on the time of year.
 * Arguments     : None
 * Returns       : The description of the trees.
*/

string
tree_desc()
{
    string str, rope_desc;

    if (rope_down)
        rope_desc = " A strong rope hangs down from a tree.\n";
    else
        rope_desc = " You can see a bit of coiled rope hanging down " + 
            "from a tree, but it is much too high for you to reach.\n";
    switch(GET_SEASON)
    {
        case SPRING:
            str = "The cherry trees are in full blossom. The white flowers " + 
                "crown the branches above, and birds sing sweetly amidst " + 
                "the leaves. Soon, they will be laden with fruit.";
            break;
        case SUMMER:
            str = "The cherry trees are laden with fruit, and the soft " + 
                "white petals of spring coat the grass. Birds flock to " + 
                "the branches to feast on the summer's bounty.";
            break;
        case AUTUMN:
            str = "The leaves of the cherry trees drift slowly to the " + 
                "ground as winter approaches. There won't be anymore " + 
                "flowers until springtime. However, the birds still " + 
                "find pleasure in the branches, and in the remnants of " + 
                "cherries on the ground.";
            break;
        case WINTER:
            str = "The bare branches of the cherry trees still hold " + 
                "a natural hidden beauty. Come spring, the branches will " + 
                "be covered in white blossoms, with delicious cherries " + 
                "to follow in the summer.";
    }

    return str + rope_desc;
}

/*
 * Function name : buy_standard_item
 * Description   : Try to let the player buy the item array
 * Arguments     : ob - the object array
 *                  str2 - string describing how the money should be paid
 *                  str3 - what coin types to get chainge back in
 *                  price - the price for the item
 * Returns       : bought items
 */

object *
buy_standard_item(object *ob, string str2, string str3, int price) 
{
    int i, sz, j, k, *value_arr, *arr, error, num, err;
    object *bought;
    mixed tmp;

    num = sizeof(query_money_types());
    value_arr = allocate(2 * num);
    bought = allocate(sizeof(ob));

    for (i = 0, sz = sizeof(ob) ; i < sz ; i++)
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
	    shop_hook_buy_cant_pay(ob[i], arr);
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
	    /* We don't want the money so no move error to us, if there was one
	       it was because the player couldn't hold all coins, and if so the
	       drop text is already written, but the deal is still on :) */
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
	shop_hook_buy_pay_money(
		text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));

    return bought;
}

/*
 * Function name : do_buy_standard_item
 * Description   : Try to let the player buy an item
 * Arguments     : string - describing how to pay and get change
 * Returns       : 1 on sucess
 */

int
do_buy_standard_item(string str)
{
    object *item;
    int i, sz;
    string str1, str2, str3;

    if (!str || str =="")
    {
	notify_fail("Buy what?\n");
	return 0;
    }

    if (!gStorekeeper)
    {
        notify_fail("There's nobody here to buy from.\n");
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

    for (i = 0, sz = sizeof(standard_items) ; i < sz ; i += 3)
    {
    	if (member_array(str1, standard_items[i]) >= 0)
    	{
    	    item = buy_standard_item(
    	        ({ clone_object(standard_items[i+1]) }),
    	        str2,
    	        str3,
    	        standard_items[i+2] );
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
    if (!gStorekeeper)
    {
        notify_fail("There's nobody here to buy from.\n");
        return 0;
    }

    if (::do_buy(a))
        return 1;

    return do_buy_standard_item(a);
}

int
do_sell(string a)
{
    notify_fail("You cannot sell items in this shop.\n");
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
    if(!this_player()->query_wiz_level())
        return 0;
    return ::do_store(a);
}

/* Function name : bench_swing
 * Description   : Lets a seated person swing their legs.
 */
string
bench_swing()
{
    if (this_player()->query_prop(PLAYER_I_IS_ON_BENCH))
    {
        say(QCTNAME(this_player()) + " swings " + 
            this_player()->query_possessive() + " feet back " +
            "and forth while sitting on the bench.\n");
        return "You swing your feet back and forth while sitting " +
            "on the bench.\n";
    }
    else
    {
        return "You cannot swing your feet while they are rooted " +
            "firmly to the ground.\n";
    }
}

/* Function name : stand_up
 * Description   : Allows the player to stand up.
 * Arguments     : string str - up
 * Returns       : Returns 0 on failure, 1 on success
*/

int
stand_up(string str)
{
    if ((str == "up") || (!str))
    {
        if (this_player()->query_prop(PLAYER_I_IS_ON_BENCH))
        {
            write("You stand up from the stone bench and stretch.\n");
            say(QCTNAME(this_player()) + " stands up from the stone bench " +
                "and stretches.\n");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            this_player()->remove_prop(PLAYER_I_IS_ON_BENCH);
            return 1;
        }

        if (!this_player()->query_prop(PLAYER_I_IS_ON_BENCH))
        {
            notify_fail("First you must be seated in order to stand!\n");
            return 0;
        }
    }

    notify_fail("Stand up?\n");
    return 0;
}

/* Function name : bench_sit
 * Description   : Let's people sit down on the benches.
 * Arguments     : string str - on bench or down
 * Returns       : Returns 0 on failure, 1 on success.
*/

int
bench_sit(string str)
{
    if ((str == "on bench") || (str == "down"))
    {
        if (!this_player()->query_prop(PLAYER_I_IS_ON_BENCH))
        {
            write("You sit down on a stone bench.\n");
            say(QCTNAME(this_player()) + " sits down on a stone bench.\n");
            this_player()->add_prop(PLAYER_I_IS_ON_BENCH, 1);
            this_player()->add_prop(LIVE_S_EXTRA_SHORT, " sitting on a bench");
            return 1;
        }

        if (this_player()->query_prop(PLAYER_I_IS_ON_BENCH))
        {
            notify_fail("You're already seated!\n");
            return 0;
        }
    }

    /* Set failure message. */
    notify_fail("Sit where?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(do_buy, "buy");
    add_action(do_sell, "sell");
    add_action(do_show, "show");
    add_action(do_list, "list");
    add_action(do_store, "store");
    add_action(bench_sit, "sit");
    add_action(stand_up, "stand");
}

/*
 * Function name : my_text
 * Description   : Generates a _compact_ text string from the array 
 *                   describing the coins
 * Arguments     : arr - the array holding the coins to describe
 */

mixed
my_text(int *arr)
{
    string *t_arr, coin_str;
    int i, j;
    
    t_arr = ({ });

    for (i = num_of_types - 1; i >= 0; i--)
        if (arr[i] > 0)
        {
        j += arr[i]; /* Total number of coins */
            t_arr += ({ arr[i] + " " + ({"cc","sc","gc","pc"})[i] });
        }

    j = sizeof(t_arr);

    if (j < 1)
        return;

    if (j == 1)
        return t_arr[0];
    else
        return implode(t_arr[0 .. j - 2], ", ") + " and " +
               t_arr[j - 1];
}
    

/*
 * Function name : shop_hook_list_object
 * Description   : List an object
 * Arguments     : ob - The object
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

/* Function name : enter_inv
 * Description   : Called every time something enters this inventory.
 *                 Starts room tell messages.
 * Arguments     : None
 * Returns       : Null
*/

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

/* Function name : leave_inv
 * Description   : Called when objects leave this container or when an
 *                 object is about to change its weight/volume/light status.
 * Arguments     : ob: The object that just leaved this inventory
 *                 to: Where it went.
*/

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!living(ob))
        return;

    /* Removes the sitting prop upon leaving the room. */
    if (ob->query_prop(PLAYER_I_IS_ON_BENCH))
    {
        ob->catch_msg("You stand up from the stone bench and stretch.\n");
        ob->tell_watcher(QCTNAME(ob) + " stands up from the stone bench " +
            "and stretches.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop(PLAYER_I_IS_ON_BENCH);
        return;
    }

    return;
}


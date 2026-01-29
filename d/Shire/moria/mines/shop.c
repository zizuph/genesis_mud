/*
 *  The Moria Shop.
 *
 *  Taken from: /d/Shire/common/bree/shop.c
 *
 
 ChangeLog
 Palmer May 07, 2004
   Removed logging of players entering shop. What on Arda
   was that for? The file was 1 meg.
   
 */

#include "defs.h"
inherit "/d/Genesis/lib/shop";

#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"
#include "/sys/composite.h"

// #define SHOP_LOG "/d/Shire/moria/log/shop"
#define IS_STUPID
#define STORE_ROOM (THIS_DIR + "shop_store") /* Where the items are stored  */
#define MAX_PAY 1000	/* Maximum price the owner will pay for something   */
#define MIN_SELL 10	/* Minimum price players will pay for an item       */
#define MAX_MISS 20	/* Maximum % deviation of answer to 'value' command */
#define RIPP_OFF 200	/* % of the value that is added to get sell-value   */
 			/* 100% rippoff means the sellvalue is 100+100%     */

#define NUM sizeof(MONEY_TYPES)	/* How many types of money do we use? */

object *item_arr, *weapon_arr, *armour_arr, *misc_arr, to;

object *not_int_sell,
       *not_int_buy,
       *no_value,
       *worn_wielded,
       *no_sell,
       *stuck,
       *too_heavy,
       *fake_money,
       *not_sell_container;

/* Prototypes */
int not_interesting_sell(object obj);
int interesting_sell(object obj);
int not_interesting_buy(object obj);
int interesting_buy(object obj);
string price_long();

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
CONSTRUCT_ROOM
{
    set_short("Ugluk Dumwa's Pawnshop and Antiques");
    set_long("You have entered the remains of an old Shop " +
	     "inside the Mines of Moria. It looks just like a " +
	     "typical dwarven shop, except the smell and aura " +
	     "of the new inhabitants of Moria: Orcs. Behind a " +
	     "desk, the new shop-keeper, a subtle and cunning " +
	     "orc with name Ugluk measures you carefully. " +
	     "With a foul writing he has scratched some symbols " +
	     "which could possibly be his price-list, but I guess " +
	     "you could ask him about the values of your items.");

    add_item(({"list","pricelist","prices","price-list","symbols"}), "@@price_long@@");

    add_item(({"item","items"}), 
       "There are far too much items lying around to pick one out of. You "
     + "should better take a look at the pricelist, to get an idea of what "
     + "useful stuff you can buy here.\n");

    add_item(({"owner","store owner","ugluk"}), 
	"The Orc, Ugluk obviously, measures you carefully, and " +
	"by the looks of him, you would guess that it is no " +
	"accident which makes him the grand keeper of this Shop. ");

    add_item(({"desk", "instructions"}), 
	     "It seems like a sturdy desk.\n" +
	     "On it, you can read some instructions:\n" +
	     "    buy <item>   : To buy an item.\n" +
	     "    sell <item>  : To sell an item.\n" +
	     "    value <item> : To let me value an item.\n" +
	     "No arguments on the quality of items within this " +
	     "store whatsoever is appreciated, listen to or argued.\n");

    add_exit(THIS_DIR + "stneslab", "west", 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check");

    add_prop(ROOM_I_INSIDE,1);	/* This is a real room */
    add_prop(ROOM_I_LIGHT, 2);

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(1000); /* Else things go wrong with "sell all" */
			  /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 700,   10000,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({	 0,	7,   4,    4 })); /* Threshold */
    set_store_room(STORE_ROOM);
}

init()
{
    init_shop();
    ::init();
    add_action("do_price", "price");
}

string
text_short(int *mon_arr)
{
    string str = "";
    string *type = ({ "cc", "sc", "gc", "pc" });
    int i;

    if (sizeof(mon_arr) != 4)
	return "---";

    for (i=3; i>=0; i--)
    {
	if (mon_arr[i] > 0)
	{
	    str += sprintf("%2d %s ", mon_arr[i], type[i]);
	}
	else
	    str += "      ";
    }
    return str;
}

string
price_str(string str, int value)
{
    string *list = ({});
    string ret;
    int len, i;

    if (strlen(str)>28)
    {
	list = explode(break_string(str, 26), "\n");

	ret = list[0] + "\n";
	for (i=1; i<sizeof(list)-1; i++)
	    ret += "   " + list[i] + "\n";

	if (sizeof(list) > 1)
	    ret += "   " + list[sizeof(list)-1];

	len = strlen(list[sizeof(list)-1])+3;
    }
    else
    {
	ret = str;
	len = strlen(ret);
    }

    ret += "..............................................."[0..30-len];

//    return ret + ":" + text_short(split_values(value)) + "\n";
    return ret + text_short(split_values(value)) + "\n";
}

/*
 * Function name:   wiz_check
 * Description:     Check if a player is a wizard
 * Returns:         0 if the player is a wizard
 *                  1 otherwise
 */
int
wiz_check()
{
    seteuid(geteuid(this_object()));
    if (TP->query_wiz_level())
	return 0;
    write("The owner of the store keeps you from going there.\n");
    say("The owner of the store blocks " + QTNAME(TP) + ".\n");
    return 1;
}

int
shop_hook_sell_no_match(string what)
{
    tell_room(TO,
	"Uglug says: Stupid " + TP->query_race_name()+ "!\n" +
	"Ugluk says: You do not have " + LANG_ADDART(what) + "!\n");
    return 1;
}

int
shop_hook_allow_sell(object obj)
{
    if (not_interesting_sell(obj))
	not_int_sell += ({ obj });

    if (function_exists("create_object", obj) == "/std/container")
	if (obj->query_room() && sizeof(all_inventory(obj->query_room())) ||
	    sizeof(all_inventory(obj)))
	{
	    not_sell_container += ({ obj });
	    return 0;
	}

    return 1;
}

void
shop_hook_sell_no_value(object obj)
{
    no_value += ({ obj });
    notify_fail("You could not fool the owner to buy your "+obj->short()+".\n");
}

void
shop_hook_sell_worn_or_wielded(object obj)
{
    worn_wielded += ({ obj });
    notify_fail("You did not state to sell worn or wielded items.\n");
}

void
shop_hook_sell_no_sell(object obj, mixed str)
{
    no_sell += ({ obj });
}

void
shop_hook_sell_object_stuck(object obj, int err)
{
    stuck += ({ obj });

    notify_fail(CAP(LANG_THESHORT(obj)) +
		" is stuck with you, and you can't sell it.\n");
}

int
shop_hook_sell_get_money(string text)
{
    write("Ugluk grins evilly and hands over "+text+".\n");
    say("Ugluk grins evilly and hands some money over to "+QTNAME(TP)+".\n");
}

/*-----------------------------------------------------------------------------*/

int
shop_hook_buy_no_match(string what)
{
    tell_room(TO,
	"Ugluk sneers: Bloody bastard, " + TP->query_race_name() + "! Haven't got it!!\n");
    return 1;
}

void
shop_hook_buy_no_buy(object obj, string str)
{
    tell_room(TO, "Ugluk laughs: I don't sell that, moron!\n");
    notify_fail(CAP(LANG_THESHORT(obj))+" was not for sale.\n");
    obj->remove_object();
}

void
shop_hook_buy_cant_carry(object ob, int err)
{
    too_heavy += ({ ob });
    notify_fail(CAP(LANG_THESHORT(ob))+" was too heavy to carry.\n");
}

void
shop_hook_buy_magic_money(object ob)
{
    fake_money += ({ ob });
    notify_fail("Your money was no good.\n");
}

/*
void
shop_hook_buy_cant_pay(object obj, int *arr)
{
}
*/


void
shop_hook_value_not_interesting(object ob)
{
    if (not_interesting_sell(ob))
	return;
    notify_fail("You couldn't sell "+LANG_THESHORT(ob)+".\n");
}

void
shop_hook_value_held(object obj, string text)
{
    say("Ugluk takes a good look at " + LANG_THESHORT(obj) + " that "
	+ QCTNAME(TP) + " is ");
    write("The owner takes a good look at " + LANG_THESHORT(obj)
	  + " that you are ");
    tell_room(TO,
	      "carrying and tries to estimate its value.\n");
    tell_room(TO,
	"Ugluk snarls: "+CAP(TP->query_nonmet_name()) + ", I'll give ya " +
	text + " for " + LANG_THESHORT(obj) + ".\n");
}

void
shop_hook_value_store(object obj, string text)
{
    tell_room(TO,
	"Ugluk hisses: " + CAP(LANG_THESHORT(obj)) + " would cost you " +
	text + ", " + TP->query_nonmet_name() + ".\n");
}

int
shop_hook_price_no_match(string what)
{
    tell_room(TO,
	"The owner grins: Eh! '"+what+"'!?! Haven't gotit! Getit, "+
	TP->query_nonmet_name()+"?\n");
    notify_fail("Ok.\n");
}

int
shop_hook_value_no_match(string what)
{
    tell_room(TO,
	      "The owner laughs: What do you mean, moron? '"+what+"' I can't value, "+
	      TP->query_nonmet_name()+".\n");
}

/*
 * Function name:  map_fnames
 * Arguments:      object ob
 * Returns:        The object's filename
 */
string
map_fnames(object ob)
{
    return MASTER_OB(ob);
}

/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
int
do_value(string str)
{
    object *item, store;
    int *arr, price, i, j, num, gfail;

    if (!str || str =="")
    {
	notify_fail("Value what?");
	return 0;
    }

    num = sizeof(query_money_types());
    item = FIND_STR_IN_OBJECT(str, this_player());

    TO->reset_arr();

    if (!sizeof(item))
    {
	shop_hook_value_no_match(str);
	return 1;
    }

    for (i = 0; i < sizeof(item); i++)
    {
	if (!shop_hook_allow_sell(item[i]) ||
	    !item[i]->query_prop(OBJ_I_VALUE) ||
	    item[i]->query_prop(OBJ_M_NO_SELL))
	{
	    shop_hook_value_not_interesting(item[i]);
	    gfail = 1;
	}

	price = query_sell_price(item[i]);

	arr = give(price, this_player(), "", 1);

	shop_hook_value_held(item[i], text(arr[num .. (2 * num - 1)]));
	j++;
	gfail = 0;
    }

    if (gfail)
	return 0;

    write("Ok.\n");
    return 1;
}

int
do_price(string str)
{
    object *item, store;
    int *arr, price, i, j, num;

    if(!str)
    {
	write(price_long());
	return 1;
    }
    TO->reset_arr();

    call_other(store_room, "load_me");
    store = find_object(store_room);
    item = FIND_STR_IN_OBJECT(str, store);

    if (!sizeof(item))
    {
	shop_hook_price_no_match(str);
	return 1;
    }

    for (i = 0; i < sizeof(item); i++)
    {
	price = query_buy_price(item[i]);
	arr = split_values(price); /* A price with few coins possible */
	shop_hook_value_store(item[i], text(arr));
	j++;
    }	

    shop_hook_value_asking(str);
    if (j > 0)
	return 1;

    return shop_hook_value_no_match(str);
}

int
do_buy(string str)
{
    int res = ::do_buy(str);
    STORE_ROOM->reset();
    return res;
}



/*
 * Function name:   do_read
 * Arguments:       string list_name
 * Description:     Provide an alias for "exa pricelist"
 * Returns:         0 if not recognised
 *                  1 otherwise
 */
int
do_read(string str)
{
    if (str == "pricelist" || str == "list" || str == "prices")
    {
	write(price_long());
	return 1;
    }
    return 0;
}

void
reset_arr()
{
    not_int_sell = ({});
    not_int_buy = ({});
    no_value = ({});
    worn_wielded = ({});
    no_sell = ({});
    stuck = ({});
    too_heavy = ({});
    fake_money = ({});
    not_sell_container = ({});
}

int
do_sell(string str)
{
    reset_arr();
    notify_fail("Ok.\n");

    if(::do_sell(str))
    {
	reset_arr();
	return 1;
    }

    if (sizeof(not_sell_container))
    {
	tell_room(TO,
	      "Ugluk hisses: You have something inside "
	    + COMPOSITE_DEAD(not_sell_container) + ".\n"
	    + "The owner says: Please empty it first, " + TP->query_nonmet_name() + ".\n");
    }
    if (sizeof(not_int_sell))
    {
	tell_room(TO, "Ugluk spits in the ground in disgust!\n" +
		  "Ugluk points at " + COMPOSITE_DEAD(not_int_sell) + ".\n"+
		  "Ugluk shakes his head, and says: Not interesting - at ALL!\n");
    }
    if (sizeof(no_value))
    {
	tell_room(TO, "Ugluk yawns, and stares at an imaginary point on the wall.\n" +
		  "Ugluk sneers: Do you take me for buying " + COMPOSITE_DEAD(no_value) + "??\n" +
		  "Ugluk asks: Take me for Moran? Take me for Stupid??\n" +
		  "Ugluk spits on the floor in disgust.\n");
    }
    if (sizeof(worn_wielded))
    {
	tell_room(TO,
	    "Ugluk sighs: You do not want to sell " + COMPOSITE_DEAD(worn_wielded) +
	    ", do you?\n");
    }
    if (sizeof(no_sell))
    {
	tell_room(TO,
	    "Ugluk says: Hah!! I can't *buy* " +
	    COMPOSITE_DEAD(no_sell) + ", " + TP->query_nonmet_name() + ".\n");
    }
    if (sizeof(too_heavy))
    {
	tell_room(TO,
	    "Ugluk laughs evilly.\n"+
	    "He says: It seems that " + COMPOSITE_DEAD(too_heavy) +
	    (sizeof(too_heavy)==1?" is":" are") + " far too heavy for you!\n");
    }
    if (sizeof(stuck))
    {
	tell_room(TO,
	    "Ugluk hmms: It seems that " + COMPOSITE_DEAD(stuck) +
	    (sizeof(stuck)==1?" is":" are") + " stuck with you.\n");
    }
    if (sizeof(fake_money))
    {
	tell_room(TO,
	    "Ugluk examines " + COMPOSITE_DEAD(fake_money) + " carefully.\n"+
	    "Ugluk screams loudly.\n"+
	    "Ugluk says: WHAT!! Do you expect me to be a complete fool?\n"+
	    "Ugluk says: This money is no good! The deal is off!\n");
    }
    reset_arr();

    return 0;
}

int
do_list(string str)
{
    write(price_long());
    say(QCTNAME(TP)+" looks at the pricelist.\n");
    return 1;
}

/*
 * Function name:   price_long
 * Description:     Give a list of all objects in the STORE_ROOM.
 *                  The items on the list are categorized and numbered.
 * Returns:         A string with the above described list.
 */
string
price_long()
{
    int i, value, previous;
    string the_long, tmp, fill_str;

    /* This is a VBFC function, so make sure our euid is set */
    seteuid(getuid());

    /* Force STORE_ROOM to be loaded */
    (STORE_ROOM)->short();
    item_arr = all_inventory(find_object(STORE_ROOM));
    if (!sizeof(item_arr))
	return "Ugluk's Shop is empty at the moment.\n";

    to = this_object();
    weapon_arr = filter(item_arr, "weapon_filter", to);
    armour_arr = filter(item_arr, "armour_filter", to);
    misc_arr = filter(item_arr, "misc_filter", to);

    fill_str = "                     ";
    previous = 1;

    the_long  = "\n---------------------- Weapons -------------------------\n";
    if (!sizeof(weapon_arr))
	the_long += "   None\n";
    else
    {
	for (i = 0; i < sizeof(weapon_arr); i++)
	{
	    tmp = " " + CAP(LANG_ASHORT(weapon_arr[i]));
	    value = query_buy_price(weapon_arr[i]);
	    the_long += price_str(tmp, value);
	}
    }

    previous += sizeof(weapon_arr);
    the_long += "\n---------------------- Armours -------------------------\n";

    if (!sizeof(armour_arr))
	the_long += "   None\n";
    else
    {
	for (i = 0; i < sizeof(armour_arr); i++)
	{
	    tmp = " " + CAP(LANG_ASHORT(armour_arr[i]));
	    value = query_buy_price(armour_arr[i]);
	    the_long += price_str(tmp, value);
	}
    }

    previous += sizeof(armour_arr);
    the_long += "\n---------------------- Others --------------------------\n";

    if (!sizeof(misc_arr))
	the_long += "   None\n";
    else
    {
	for (i = 0; i < sizeof(misc_arr); i++)
	{
	    tmp = " " + CAP(LANG_ASHORT(misc_arr[i]));
	    value = query_buy_price(misc_arr[i]);
	    the_long += price_str(tmp, value);
	}
    }
    the_long += "\n";
    return the_long;
}

int
query_money_greed_sell()
{
    int factor = 100;
    string race = TP->query_race_name();

    /* This is a Orc shop... */
    if (race == "hobbit" || race == "dwarf")
	factor += 3;
    if (race == "human" || race == "elf")
	factor += 5;
    if (TP->query_alignment() > 0)
	factor += 3;

    return factor;
}

int
query_money_greed_buy()
{
    int factor = 100;
    string race = TP->query_race_name();

    /* This is a Orc shop... */
    if (race == "hobbit" || race == "dwarf")
	factor += 3;
    if (race == "human" || race == "elf")
	factor += 5;
    if (TP->query_alignment() > 0)
	factor += 3;

    return factor;
}

/* Function to identify a weapon */
int
weapon_filter(object obj)
{
    return ((!living(obj)) &&
	    (function_exists("create_object", obj) == "/std/weapon"));
}

/* Function to identify an armour */
int
armour_filter(object obj)
{
    return ((!living(obj)) &&
	    (function_exists("create_object", obj) == "/std/armour"));
}

/* Function to identify things that are neither a weapon nor an armour */
int
misc_filter(object obj)
{
    return (!living(obj)) &&
	(member_array(obj, weapon_arr) < 0) &&
	(member_array(obj, armour_arr) < 0);
}

/*
 * Two arrays needed by not_interesting_...().
 * The first defines the objects that define the identifier function,
 * the second contains the names of the identifier functions, in the
 * same order as the objects are in the first array. Note that the
 * tricky bit is that you have to find a function that only is defined
 * by the object you search. The create_object() function is a good
 * identifier, because all the /std things define their own create_xxx().
 */
#define STD_OBJ      ({ "/std/coins",\
                        "/std/food",\
                        "/std/drink",\
                        "/std/living" })

#define STD_OBJ_FUNC ({ "create_heap",\
                        "create_heap",\
                        "create_heap",\
                        "create_container" })

/*
 * Function name:   not_interesting_sell
 * Arguments:       object obj_to_check
 * Description:     Check if the object can be sold. This check will
 *                  assure that no weird items such as money or food
 *                  will be sold in the shop. You can add things in
 *                  the STD_OBJ and STD_OBJ_FUNC arrays to exclude more.
 *
 * Returns:         1 if it cannot be sold
 *                  0 otherwise
 */
int
not_interesting_sell(object obj)
{
    int i;

    for (i = 0; i < sizeof(STD_OBJ); i++)
    {
	if (function_exists(STD_OBJ_FUNC[i], obj) == STD_OBJ[i])
	    return 1;
    }

    return 0;
}

int
interesting_sell(object obj)
{
    return !not_interesting_sell(obj);
}

/*
 * Function name:   not_interesting_buy
 * Arguments:       object obj_to_check
 * Description:     Check if the object can be bought. This check will
 *                  assure that no weird items such as money or food
 *                  will be sold in the shop. You can add things in
 *                  the STD_OBJ and STD_OBJ_FUNC arrays to exclude more.
 *
 * Returns:         1 if it cannot be sold
 *                  0 otherwise
 */
int
not_interesting_buy(object obj)
{
    int i;

    for (i = 0; i < sizeof(STD_OBJ); i++)
    {
	if ((obj->query_prop(OBJ_I_VALUE) == 0)
	    || (obj->query_prop(OBJ_M_NO_DROP) == 1)
	    || obj->query_prop(OBJ_M_NO_BUY)
	    || (function_exists(STD_OBJ_FUNC[i], obj) == STD_OBJ[i]))
	    return 1;
    }
    return 0;
}

int
interesting_buy(object obj)
{
    return !not_interesting_buy(obj);
}
 
/*
What on Arda was this for? Palmer May 07, 2004
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (!living(ob))
        return;
 
    write_file(SHOP_LOG, ob->query_name()+
        " entered the shop on "+ctime(time())+".\n");
}
*/
/* The Redhammer Smithy 
 * Modified for Rilak's Smithy in Mithas
*/

#include "../local.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit MITHAS_IN;
inherit "/lib/trade";

#define MEND_COST    80 
/* Mending will cost 80% (was 50%) of the weapon's price */
#define WAX_COST     10 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */

/* prototypes are here */
int calc_sharpen_value(object obj);
int calc_wax_value(object obj);
int calc_mend_value(object obj);
int distort(int price);
object rilak_smith;

string
pound_tell()
{
    if(!rilak_smith || !P(rilak_smith, TO))
    return "";
/*
    return (QCTNAME(rilak_smith) + " pounds a strip of metal, turns it over " + 
        "and pounds on it some more.\n");
*/
    return ("The smith pounds a strip of metal, turns it over and pounds " + 
        "on it some more.\n");
}

string
inspect_tell()
{
    if(!rilak_smith || !P(rilak_smith, TO))
    return "";
/*
    return (QCTNAME(rilak_smith) + " inspects her work to ensure that it " + 
        "is up to her standards, then plunges it into the barrel of water " + 
        "as steam fills the room.\n");
*/
    return ("The smith inspects her work to ensure that it " + 
        "is up to her standards, then plunges it into the barrel of water " +
        "as steam fills the room.\n");

}

string
grind_tell()
{
    if(!rilak_smith || !P(rilak_smith, TO))
    return "";
/*
    return (QCTNAME(rilak_smith) + " starts her grindstone moving, then holds a piece of " +
    "tempered metal to it, grinding it until it becomes too hot to hold, " +
    "then dips it into her barrel of water briefly.\n");
*/
    return ("The smith starts her grindstone moving, then holds a piece of " + 
    "tempered metal to it, grinding it until it becomes too hot to hold, " +
    "then dips it into her barrel of water briefly.\n");

}

public void
reset_mithas_room()
{
    if (!rilak_smith)
    {
	rilak_smith = clone_object(MNPC + "rilak");
	rilak_smith->move_living("xx", TO);
	rilak_smith->seq_new("do_thing");
	rilak_smith->seq_addfirst("do_thing","@@arm_me");
    }
}

public void
create_mithas_room()
{
    set_short("Imperial weapon smithy");
    set_long("You are standing in a steamy smithy in the city "+
        "of Nethosak. A barrel of water " + 
        "and an anvil rest beside a red brick forge. The bellows hang " + 
        "near the forge, chained securely to the wall. A large contraption " + 
        "sits by the far wall. Little else " + 
        "decorates this room except for a sign nailed firmly into the " + 
        "wall next to the door.\n");

    add_item("sign", "@@read_sign");
    add_item("contraption", "It looks like a big solid table with pedals " + 
        "at the bottom. A grinding wheel is attatched to the top, and the " + 
        "pedals make it move, allowing the smith to sharpen weapons.\n");
    add_item(({"stone", "grinding stone", "grinding wheel", "wheel"}), "It " + 
        "is a coarse grey stone used to sharpen weapons.\n");
    add_item("pedals", "The smith pushes the pedals with her feet to turn " + 
        "the grindstone.\n");
    add_item("table", "It supports the grinding stone and pedals.\n");
    add_item("forge", "It is filled with glowing red coals.\n");
    add_item("anvil", "Many dents mark the age of this anvil.\n");
    add_item("bellows", "They are securely chained to the wall to prevent " + 
        "any borrowing by patrons.\n");
    add_item("coals", "They look very hot!\n");
    add_item("barrel", "It's filled with water, but you wouldn't want " + 
        "to drink it.\n");
    add_item(({"wall", "walls"}), "The walls look very sturdy. Perhaps " +
        "they are of dwarven make.\n");
    add_item("water", "It's used to cool hot weapons.\n");
    add_item(({"chain", "chains"}), "It fastens the bellows securely to " + 
        "the wall.\n");

    add_exit(MROOM + "road13","south",0);
    INSIDE;

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell("@@discriminate");

    set_tell_time(200);
    add_tell("A bead of sweat runs down your forhead.\n");
    add_tell("@@pound_tell");
    add_tell("@@inspect_tell");
    add_tell("@@grind_tell");
    add_tell("A wandering kender tries to take off with the bellows, but " + 
        "is stopped by the chain. He gets a very surprised look on his " + 
        "face, and chatters: How did THAT get in my pouch?\n");

    reset_mithas_room();
}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
}

void
init()
{
    ::init();
    //add_action("do_fix","mend",0);
    add_action("do_not_fix","mend",0);
    add_action("do_fix","sharpen",0);
    add_action("do_fix","wax",0);
    add_action("do_read","read",0);
    add_action("do_cost","cost",0);
}

string
read_sign()
{
    return
    "Weapon improvement:\n"
    + "-------------------\n"
    + "Sharpen dull weapons\n"
    + "Wax corroded weapons\n"
    + "\n"
    + "All prices depend on the price of the weapon.\n"
    + "Do \"cost <weapon>\" to see the costs.\n";
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "sign")
	return 0;

    write(read_sign());
    return 1;
}

int
do_cost(string str)
{   
    object *weapon, tp;
    int v1, v2, v3;

    if (!(present("rilak", TO)))
    {
	write("It is impossible to cost your weapon without " +
	  "the blacksmith here.\n");
	return 1;
    }

    tp = this_player();

    NF("The dwarf gruffs: Which weapon?\n");
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
      !sizeof(weapon))
	return 0;

    NF("Frowning, the dwarf says: Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
	return 0;

    NF("Smirking, the dwarf states: That is not really a weapon.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
	return 0;

    v1 = calc_sharpen_value(weapon[0]);
    v2 = calc_wax_value(weapon[0]);
    v3 = calc_mend_value(weapon[0]);

    write("The dwarf suggests: Sharpening that " + weapon[0]->short() + " "
      + ((v1 == -1) ? "is not necessary.\n"
	: ("would cost about " + distort(v1) + " coppers.\n"))
      + "Waxing it "
      + ((v2 == -1) ? "is not necessary.\n"
	: ("would cost about " + distort(v2) + " coppers.\n"))
      + "Mending it "
      + ((v3 == -1) ? "is not necessary.\n"
	: ("is necessary but cannot be done here.\n"))
      //	     : ("would cost about " + distort(v3) + " coppers.\n"))
    );
    return 1;
}

int
do_not_fix(string str)
{
    write("Sorry, this option is currently unavailable.\n");
    return 1;
}

int
do_fix(string str)
{
    object *weapon, tp;
    int int_str, value, *money_arr;
    string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
    verb;

    verb = query_verb();

    if (!(present("rilak", TO)))
    {
	write("You are unable to do that when the blacksmith is absent.\n");
	return 1;
    }

    NF(capitalize(verb) + " what?\n");
    if (!str)
	return 0;

    tp = this_player();

    /*   Check if the player defines what she wants to pay with
     *   and what you would like in return.
     */
    if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
	get_type = "";
	/* Hmmm... Maybe she only wishes to pay with a certain type */
	if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
	{
	    pay_type = "";
	    item_name = str;
	}
    }

    if (pay_type != "")
    {
	if (member_array(pay_type, MONEY_TYPES) < 0)
	{
	    tell_room(this_object(), "The smith says: I don't accept " +
	      "those " + pay_type + " coins, " + 
	      tp->query_nonmet_name() + ".\n");
	    return 1;
	}
    }

    if (get_type != "")
    {
	if (member_array(get_type, MONEY_TYPES) < 0)
	{
	    tell_room(this_object(), "The dwarf states: " + 
	      capitalize(get_type) + " coins? Never "
	      + "heard of those.\n");
	    return 1;
	}
    }

    NF(capitalize(verb) + " what?\n");
    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
      !sizeof(weapon))
	return 0;

    NF("The dwarf shouts: Be more specific. Which one?\n");
    if (sizeof(weapon) > 1)
	return 0;

    NF("The smith laughs: That is not really a weapon.\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
	return 0;

    /* Talk about tricky code! ;-) */
    value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

    NF("The smith says: I cannot " + verb + " that any further.\n");
    if (value == -1)
	return 0;

    /* Try to take the money */
    if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
    {
	if (money_arr[0] == 1)
	{
	    tell_room(this_object(), "The smith says: I think that " + 
	      weapon[0]->short() + " is a bit more"
	      + " expensive, " + tp->query_nonmet_name() + ".\n");
	    return 1;
	}
	if (money_arr[0] == 2)
	{
	    tell_room(this_object(), "The smith says: You do not have " +
	      "any " + pay_type + " coins, "
	      + tp->query_nonmet_name() + ".\n");
	    return 1;
	}
	else
	{
	    tell_room(this_object(), "The smith says: I think that " + 
	      weapon[0]->short() + " is a bit too expensive "
	      + "for you, " + tp->query_nonmet_name() + ".\n");
	    return 1;
	}
    }

    /* It is paid for, so let's fix the weapon */
    value = call_other(this_object(), "fix_"+verb, weapon[0]);

    write("You give the smith the " + weapon[0]->short() + ".\n");
    say(QCTNAME(tp) + " gives the smith " + tp->query_possessive() +
      " " + weapon[0]->short() + ".\n");

    tell_room(this_object(),
      "The smith " + verb + ((verb == "wax") ? "es" : "s") + " the "
      + weapon[0]->short() + ".\n"
      + "The smith gives the weapon back.\n");

    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
	sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the smith " +coin_pay_text+ ".\n");
    if (coin_get_text)
	write("You get " + coin_get_text + " in return.\n");

    return 1;
}

int
calc_wax_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
	return -1;

    if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
	obj->query_corroded()))
	return -1;
    return (obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}

int
calc_sharpen_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
	return -1;

    if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
	obj->query_dull()))
	return -1;
    return (obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}

int
calc_mend_value(object obj)
{
    if (!(obj->query_prop(OBJ_I_BROKEN)))
	return -1;
    return (F_VALUE_WEAPON(obj->query_pen(), obj->query_hit()) * MEND_COST)/100;
}

void
fix_wax(object obj)
{
    obj->set_repair_corr(obj->query_repair_corr() + 1);
}

void
fix_sharpen(object obj)
{
    obj->set_repair_dull(obj->query_repair_dull() + 1);
}

void
fix_mend(object obj)
{
    //obj->remove_prop(OBJ_I_BROKEN);
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    return 105;
}

#define F_RANGE_RANDOM(orig, max, min, value) \
        ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
        + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))


int
distort(int price)
{
    int trading;

    trading = this_player()->query_skill(SS_TRADING);
    if (trading > 100)
	trading = 100;
    if (trading < 0)
	trading = 0;

    return F_RANGE_RANDOM(price, 30, 2, trading);
}

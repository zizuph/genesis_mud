// Bazaar Armoury (/d/Avenir/common/bazaar/armr.c)
// creator(s):   Triana 1994
// last update:  Lilith, Mar 98
//               Tepisch, Nov 94
// purpose:      weapon repair               
// note:         heavily borrowed from the solamnic armoury
// bug(s):
// to-do:        

inherit "/std/room";
inherit "/lib/trade";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "/sys/formulas.h"
#include "/sys/money.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

#define MEND_COST     75	
#define WAX_COST      15
#define SHARPEN_COST  15
#define FALCHION_BITS 0, 19

/* Prototypes */
int calc_wax_value(object obj);
int calc_sharpen_value(object obj);
int distort(int price);
int favour();
string sign_long();

object iron, smith;

void
create_room()
{
    set_short("Bazaar Island Forge");
    set_long("A very warm, dark room from the back of which an " +
        "intense heat radiates.  Metal glows red-gold upon the fire, " +
        "the only source of light.  The sighing of the bellows can be " +
        "heard between the clangs of the blacksmith's hammer upon the " +
        "anvil.  Here, a blacksmith toils to fix weapons for adventurers " +
        "who are in the area.  @@see_exit@@\n"+
        "A sign hangs from the ceiling.\n");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_item(({"list","sign"}), "@@sign_long");
    add_item(({"forge","fire"}), 
        "It throws flickering light upon the walls.\n");  
    add_item(({"apprentice", "boy"}), "He is a miniature version of " +
        "the blacksmith, facing the intense heat stoically.\n");
    add_item(({"walls", "wall"}), 
        "Shadows dance upon walls which radiate an intense heat.\n");
    add_item(({"bellow", "bellows"}),
        "A hard-working apprentice mans the bellows, fanning the fire " +
        "hotter and hotter.\n");
    add_item("metal", "It glows red-gold in the fire.\n");

    add_exit(EXTR + "str3", "east", 0);
    add_exit(INTR + "armr_shop", "west", "@@exit_check", 1, 1);

    config_default_trade();

    set_money_give_max(100000);
    set_money_give_out(({    5000,   500,  50,    1 }));
    set_money_give_reduce(({    0,    10,   5,    5 })); 
    set_money_greed_sell("@@favour");


    reset_room();
}

void
reset_room()
{
    if (!present(iron))
    {
        iron = clone_object(BAZAAR + "Obj/misc/iron");
        iron->move(this_object());
    }
    if (!present(smith))
    {
        smith = clone_object(BAZAAR + "NPCS/smith");
        smith->move_living("X", this_object());
    }
}

int
exit_check()
{
    if (this_player()->test_bit("Avenir", FALCHION_BITS)) 
    {
        write("The dwaven blacksmith steps aside and allows you to pass.\n");
        return 0;
    }
    else
        write("You have not earned the right to enter there.\n");
    return 1;           
}
                 
string 
see_exit()
{
    if (this_player()->test_bit("Avenir", FALCHION_BITS)) 
        return "West, beyond the firepit, you can glimpse a "+
               "small courtyard.";
    else
        return "";
}

string
sign_long()
{
    return
        "\n\nBazaar Forge Weapon Restoration:\n"
      + "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
      + "     Sharpen dull weapons\n"
      + "     Wax corroded weapons\n"
      + "\n"
      + "All prices depend upon the value of the weapon.\n"
      + "Do \"cost <weapon>\" to see the cost for a service.\n";
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "list" && str != "pricelist" &&
        str != "sign" && str != "little sign")
        return 0;

    write(sign_long());
    return 1;
}

int
no_mend(string str)
{
    write("The blacksmith regrets to inform you that he is forbidden "+
          "from mending the weapons and armours at this time.\n");
    return 1;
}

int    
do_cost(string str)
{
    int v1, v2;
    object *weapon;

    if (!strlen(str) || !sizeof(weapon = FIND_STR_IN_OBJECT(str, TP)))
        return notify_fail("Which weapon?\n");

    if (sizeof(weapon) > 1)
        return notify_fail("Be more specific. Which one?\n");

    if (!weapon[0]->check_weapon())
        return notify_fail("That is not really a weapon.\n");

    v1 = calc_sharpen_value(weapon[0]);
    v2 = calc_wax_value(weapon[0]);

    write("Sharpening that " + weapon[0]->short() +" "+
        ((v1 == -1) ? "is not necessary.\n" : 
        ("would cost about " + distort(v1) + " coppers.\n")) +
        "Waxing it "+ ((v2 == -1) ? "is not necessary.\n" : 
        ("would cost about " + distort(v2) + " coppers.\n")));

    return 1;
}

int
do_fix(string str)
{
    object *weapon;
    int    int_str, value, *money_arr;
    string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
           verb;

    if (!strlen(str))
        return notify_fail(capitalize(verb) + " what?\n");

    if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
    {
        get_type = "";
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
            tell_room(this_object(), "The smith says: I don't "+
                "accept those " + pay_type + " coins, "+ 
                TP->query_nonmet_name() + ".\n");
            return 1;
        }
    }

    if (get_type != "")
    {
        if (member_array(get_type, MONEY_TYPES) < 0)
        {
            tell_room(this_object(), "The smith says: "+ 
                capitalize(get_type) + " coins? Never "+ 
                "heard of those. You must be a surface-dweller.\n");
            return 1;
        }
    }

    if (!sizeof(weapon = FIND_STR_IN_OBJECT(str, TP)))
        return notify_fail("Mend what?\n");

    if (sizeof(weapon) > 1)
        return notify_fail("Be more specific. Which one?\n");

    if (!weapon[0]->check_weapon())
        return notify_fail("That is not really a weapon.\n");

    verb  = query_verb();
    value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

    if (value == -1)
        return notify_fail("The smith says: I cannot " + verb +
	    " that any further.\n");

    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1)
    {
        if (money_arr[0] == 1)
        {
            tell_room(this_object(), "The smith says: I think that "+ 
                "repairing your "+weapon[0]->short() + " costs a bit "+ 
                "more than you can afford, "+ TP->query_nonmet_name() +
                ".\n");
            return 1;
        }
        if (money_arr[0] == 2)
        {
            tell_room(this_object(), "The smith says: You do not "+
                "have any " + pay_type + " coins, "+ 
                TP->query_nonmet_name() + ".\n");
            return 1;
        }
        else
        {
            tell_room(this_object(), "The smith says: I think that " + 
                "repairing your "+weapon[0]->short() + " costs a bit "+ 
                "more than you can afford, "+ TP->query_nonmet_name() +
                ".\n");
            return 1;
        }
    }

    value = call_other(this_object(), "fix_"+verb, weapon[0]);

    write("You give the smith the " + weapon[0]->short() + ".\n");
    say(QCTNAME(TP) + " gives the smith " + TP->query_possessive() +
        " " + weapon[0]->short() + ".\n");

    tell_room(this_object(), "The smith "+ verb +
	((verb == "sharpen") ? "s" : "es") + " the "+ weapon[0]->short() +
	".\nThe smith gives the weapon back.\n");

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

    return max(obj->query_repair_cost_corr(),
	(obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100);
}

int
calc_sharpen_value(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
        return -1;

    if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
        obj->query_dull()))
        return -1;

    return max(obj->query_repair_cost_dull(),
	(obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100);
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

/*
 * Function name:   favour
 * Description:     Favour some players by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
favour()
{
    string race = this_player()->query_race();
    
    /* This is a servant of the Shadow Elves, thus elves do well; and 
     * dwarves are treated fairly because the smith is dwarven.
     */
    if (race == "elf")
        return 90;
    if (race == "dwarven")
        return 100;    
    return 115;
}

#define F_RANGE_RANDOM(orig, max, min, value) \
       ((orig) - (orig) * ((min) *100 + ((max)-(min)) * \
       (100 - (value))) / 10000 + random(2 * (orig) * \
       ((min) * 100 + ((max) - (min)) * (100 - (value))) / 10000))

int
distort(int price)
{
    int trading;

    trading = this_player()->query_skill(SS_TRADING);
    if (trading < 10)
        trading = 10;
    if (trading > 100)
        trading = 100;

    return F_RANGE_RANDOM(price, 30, 2, trading);
}

void
init()
{
    ::init();
    add_action(no_mend,  "mend",0);
    add_action(do_fix,   "sharpen",0);
    add_action(do_fix,   "wax",0);
    add_action(do_read,  "read",0);
    add_action(do_cost,  "cost",0);
}


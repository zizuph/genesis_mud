/*
 *  Filename:       wr_smith.c
 *  Description:    This is the room on top of the smithy wagon w_smith.
 *
 *  Copyright (c) Okt. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Smith code at the bottom copied from a smithy in icewall, thank you
 *  original coder!
 *
 *  Change log:
 */

#pragma strict_types
#include "wagon.h"
#include <money.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

inherit "/lib/trade";
inherit WAGON_ROOM_INDOOR;

#define SHARPEN_COST 25 /* Sharpening costs 25 % of weapon cost */

/* prototypes are here */
int calc_sharpen_value(object obj);
int distort(int price);



string
anvil()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "The anvil looks old and well-used ,filled with dents from " +
             "the blows from a hammer.\n";
}

string
fireplace()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "A roaring fire is burning in the fireplace, smoke billowing " +
             "up and out the chimney. The fireplace are build of stone " +
             "on top of a steel reinforced piece of the floor.\n";
}

string
chimney()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "The chimney are made of stone, spiralling up and out the roof" +
             "of the hardboxed wagon.\n";
}

string
bucket()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "A bucket of water stands ready for cooling down the metal " +
             "after it have been heated in the fireplace.\n";
}

string
floor()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Most of the floor are made of wood, while the parts below the" +
             "anvil and the fireplace are made of a few steel plates, " +
             "making it bear the weight of the anvil and resist the fire " +
             "of the fireplace.\n";
}

string
windows()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "The windows are tiny, too small in a smithy wagon with its big" +
             "need of airconditioning, and these windows are shut closed " +
             "to even more .\n";
}

string
shelf()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "All around the walls there are shelves filled with either" +
             "raw metals for use in weapon production or finished swords " +
             "polearms or axes.\n";
}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";
    desc =  "You are inside " + LANG_ADDART(myWagon->short()) +
            ", it is hot and smoky in here due to the fireplace at the far " +
            "end are roaring with fire, in the middle of the wagon there " +
            "is a big black anvil and a bucket of water. The windows in " +
            "the hardbox are small making the heat from the fireplace " +
            "unbearable.\n";

    return desc;
}

public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "Inside the hardbox of the smithy wagon";

    return desc;

}


void
init()
{
    ::init();
    add_action("do_fix","sharpen",0);
    add_action("do_cost","cost",0);

}


void
create_wagon_room()
{

    string str;

    add_item("anvil", anvil);
    add_item("fireplace", fireplace);
    add_item("chimney", chimney);
    add_item("bucket", bucket);
    add_item("floor", floor);
    add_item(({"window","windows"}), windows);
    add_item(({"shelf","shelves"}), shelf);

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell("@@discriminate");

    set_tell_time(250);

}


/* The remaining code is for smithing to work in the wagon */

int
do_cost(string str)
{
    object *weapon, tp;
    int v1, v2, v3;

    if (!(present("neggel", TO)))
    {
    write("The blacksmith is not here to help you with that.\n");
    return 1;
    }

    tp = this_player();

    NF("The half-ogre slaps your shoulder and says: Which " +
      "weapon ya wanna fixed?\n");
    if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
      !sizeof(weapon))
    return 0;

    NF("Snarling, the half-ogre says: Stop messing with me. Which one?\n");
    if (sizeof(weapon) > 1)
    return 0;

    NF("Spitting a gob of phlegm, the half-ogre snarls: That's " +
      "not a weapon, moron!\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
    return 0;

    v1 = calc_sharpen_value(weapon[0]);

    write("The half ogre snarls: Ye dumb? The " + weapon[0]->short() + " "
      + ((v1 == -1) ? "is sharp enough!\n"
    : ("would cost about " + distort(v1) + " coppers.\n")));
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

    if (!(present("neggel", TO)))
    {
    write("But the blacksmith is absent!\n");
    return 1;
    }

    NF(capitalize(verb) + " what?\n");
    if (!str)
    return 0;

    tp = this_player();

    if (tp->query_race_name() == "dwarf")
    {
        tell_room(this_object(), "The half-ogre snarls: I don't do " +
          "business for dirty dorfs!\n");
        return 1;
    }

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
        tell_room(this_object(), "The half-ogre snarls: I don't accept " +
          "funny " + pay_type + " coins, " +
          tp->query_nonmet_name() + ".\n");
        return 1;
    }
    }

    if (get_type != "")
    {
    if (member_array(get_type, MONEY_TYPES) < 0)
    {
        tell_room(this_object(), "The half-ogre snarls: " +
          capitalize(get_type) + " coins? Never "
          + "heard of those.\n");
        return 1;
    }
    }

    NF(capitalize(verb) + " what?\n");
    if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) ||
      !sizeof(weapon))
    return 0;

    NF("The half-ogre snarls: Make up yer mind! Which one?\n");
    if (sizeof(weapon) > 1)
    return 0;

    NF("The half-ogre laughs: That's not a weapon, moron!\n");
    if (function_exists("create_object",weapon[0]) != "/std/weapon")
    return 0;

    /* Talk about tricky code! ;-) */
    value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

    NF("The half-ogre snarls: Ye dumb? Its sharp enough!\n");
    if (value == -1)
    return 0;

    /* Try to take the money */
    if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
    {
    if (money_arr[0] == 1)
    {
        tell_room(this_object(), "The half-ogre snarls: Ye poor " +
              "bastard! I ain't working for free unless da Master " +
              "orders me..\nHah hah hahahaha...\n");
        return 1;
    }
    if (money_arr[0] == 2)
    {
        tell_room(this_object(), "The half-ogre snarls: Ye do not have " +
          "any " + pay_type + " coins, "
          + tp->query_nonmet_name() + ".\n");
        return 1;
    }
    else
    {
        tell_room(this_object(), "The half-ogre snarls: Ye poor " +
              "bastard! I ain't working for free unless da Master " +
              "orders me..\nHah hah hahahaha...\n");
        return 1;
    }
    }

    /* It is paid for, so let's fix the weapon */
    value = call_other(this_object(), "fix_"+verb, weapon[0]);

    write("You give the half-ogre the " + weapon[0]->short() + ".\n");
    say(QCTNAME(tp) + " gives the half-ogre " + tp->query_possessive() +
      " " + weapon[0]->short() + ".\n");

    tell_room(this_object(),
      "The half-ogre " + verb + ((verb == "wax") ? "es" : "s") + " the "
      + weapon[0]->short() + ".\n"
      + "The half-ogre gives the weapon back.\n");

    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES),
    sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay " +coin_pay_text+ ".\n");
    if (coin_get_text)
    write("You get " + coin_get_text + " in return.\n");

    return 1;
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


void
fix_sharpen(object obj)
{
    obj->set_repair_dull(obj->query_repair_dull() + 1);
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



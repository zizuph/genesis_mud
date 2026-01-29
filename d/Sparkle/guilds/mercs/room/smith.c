/*
 * /d/Genesis/guilds/merc/room/smith by Morrigan, 11/01
 *   adapted from the forge in Vingaard Keep
 */
#include "../merc.h"
#include "room.h"

inherit "/std/room";
inherit "/lib/shop";
inherit "/lib/trade";

#define ASSIGN_AND_VALIDATE_STORE_OBJECT(s_o) \
    s_o = get_store_object(); \
    if (!(s_o)) \
    { \
	write("Error: no store object - please make a bug report.\n"); \
    } \

#define STORE_ROOM   MROOM + "smith_store"
#define MEND_COST    80
 
/* Mending will cost 80% (was 50%) of the weapon's price */
#define WAX_COST     10 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */
#define WEAPONS ({ 	"longsword", "broadsword", "shortsword",\
			"mace", "warhammer", "morning-star" })

/* prototypes are here */
int calc_sharpen_value(object obj);
int calc_wax_value(object obj);
int calc_mend_value(object obj);
int distort(int price);
int gOrdering;
object gSmith;

public int exit_tent()
{
	write(TENT_EXIT);
}

public void
reset_room()
{
    /* Commenting this out. Tarn has left. (Gorboth)
    if (!gSmith)
    {
	gSmith = clone_object(MNPC + "tarn");
	gSmith->move_living("xx", TO);
    }
    */
}

public int 
do_sell(string str)
{
    gSmith->command("say I'm not interested in buying yer wares!");
    return 1;
}

public void
create_room()
{
    set_short("A small tent");
    set_long("The tent has an open roof above the forge, letting steam and "+
	"smoke escape. Near the back, you can see an opening leading into the "+
	"store room. There is a sign next to the forge.\n");

    add_item("forge","The forge glows a fiery-red colour.\n");
    add_item(({"store", "store room"}), "The back room in which the excess "+
      "armours and weapons are kept.\n");
    add_item(({"list","pricelist","sign"}), "@@sign_long");
    add_item(({"bucket", "buckets"}), "There are two buckets, one full of steel "+
	"and one full of water.\n");
    add_item("apprentice", "The young lad busies himself with whatever "+
	"he is instructed to do.\n");
    add_item(({"shelf", "shelves"}), "The shelves are used to store weapons "+
	"and other things that have been forged. You may 'list' their contents.\n");

    add_exit(MROOM + "center", "northwest", "@@exit_tent", 0, 0);

    reset_room();

    config_default_trade();  /* Set up the trading system */
    set_store_room(STORE_ROOM);
    set_money_give_max(100000); /* Else things go wrong with "sell all" */
    /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_money_greed_sell("@@discriminate");
    query_store_room()->load_me();
    reset_room();
}

void
init()
{
    ::init();
    init_shop();
    //add_action("do_fix","mend",0);
    add_action("do_not_fix","mend",0);
    add_action("do_fix","sharpen",0);
    add_action("do_fix","wax",0);
    add_action("do_read","read",0);
    add_action("do_cost","cost",0);
    add_action("do_order", "order", 0);
}

string
sign_long()
{
    return "You can <order> weapons of the following types:\n"+
	   "     longsword   broadsword   shortsword\n"+
	   "       mace   morning-star   warhammer\n\n"+
	   "You can also <sharpen> dull weapons, <wax> corroded:\n"+
	   "  weapons, and check to see what these will cost with\n"+
	   "  <cost weapon>.\n";
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "list" && str != "pricelist" &&
      str != "sign")
	return 0;

    write(sign_long());
    return 1;
}

int
do_cost(string str)
{   
    object *weapon, tp;
    int v1, v2, v3;

    if (!objectp(gSmith) || environment(gSmith) != TO)
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

    if (!(present("tarn", TO)))
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

/*
 * Allow player to order weapons here:
 *
 *    Weapon types:	longsword
 *			broadsword
 *			shortsword
 *			mace
 *			warhammer
 *			morning-star
 *
 */

public void set_ordering(int i)
{
    gOrdering = i;
}

public int query_ordering()
{
    return gOrdering;
}


public void seventh_message(string str)
{
    setuid();
    seteuid(getuid());

    gSmith->command("emote takes the "+str+" and puts it on the shelf to "+
	"be purchased.");
    gSmith->command("say I don't have time ta be spent counting yer coins, "+
	"so ya can buy it from my apprentice here when yer ready.");
    gSmith->command("emote says: 'Who's next?' and looks around impatiently.");
    clone_object(MOBJ + str)->move(STORE_ROOM);
    set_ordering(0);
}

public void sixth_message(string str)
{
    switch(str)
    {
	case "shortsword":
	case "longsword":
	case "broadsword":
	{
	    gSmith->command("emote adds some intriciate detailing to the blade "+
		"near the hilt.");
            break;
        }

        case "mace":
	case "morning-star":
	case "warhammer":
        {
	    gSmith->command("emote adds some intricate detailing to the shaft "+
		"of the "+str+" near the hilt.");
	    break;
	}
    }

    set_alarm(3.0, 0.0, "seventh_message", str);
}

public void fifth_message(string str)
{
    switch(str)
    {
	case "shortsword":
	case "longsword":
	case "broadsword":
	{
	    gSmith->command("emote fashions the hilt of the sword with some "+
		"shaped wood and brass pieces, attaching them to the dull end of "+
		"the blade.");
            break;
        }

        case "mace":
	case "morning-star":
	case "warhammer":
        {
	    gSmith->command("emote fashions the hilt of the "+str+" with some "+
		"shaped wood and brass pieces, attaching them to other end of "+
		"the shaft.");
	    break;
	}
    }

    set_alarm(8.0, 0.0, "sixth_message", str);
}

public void fourth_message(string str)
{
    switch(str)
    {
	case "shortsword":
	case "longsword":
	case "broadsword":
	{
	    gSmith->command("emote shapes the sword a bit more, hammering a "+
		"concave groove in the center that runs nearly the length "+
		"of the blade.");
            break;
        }

        case "mace":
        {
	    gSmith->command("emote heats the end of the bar again and fastens "+
		"a diamond-shaped hunk of metal to the end of it.");
	    break;
	}
	case "morning-star":
	{
	    gSmith->command("emote heats the end of the bar again and fastens "+
		"a ball of steel covered with small spikes to the end of it.");
	    break;
	}
	case "warhammer":
	{
            gSmith->command("emote heats the end of the bar again and fastens "+
		"a great hammer-like head to the end of it.");
	    break;
        }
    }

    set_alarm(10.0, 0.0, "fifth_message", str);
}

public void third_message(string str)
{
    switch(str)
    {
	case "shortsword":
	case "longsword":
	case "broadsword":
	{
	    gSmith->command("emote dips the metal, which is now beginning to "+
		"resemble a blade, into a bucket water with a loud hissing "+
		"sound.");
            break;
        }

        case "mace":
	case "morning-star":
	case "warhammer":
	{
            gSmith->command("emote dips the bar of metal into a bucket of water "+
		"with a loud hissing sound.");
	    break;
        }
    }

    set_alarm(5.0, 0.0, "fourth_message", str);
}

public void second_message(string str)
{
    switch(str)
    {
	case "shortsword":
	case "longsword":
	case "broadsword":
	{
	    gSmith->command("emote hammers some on the strip of metal as it "+
		"begins to glow red from the heat of the forge.");
            break;
        }

        case "mace":
	case "morning-star":
	case "warhammer":
	{
	    gSmith->command("emote begins to hammer on the bar of metal as it "+
		"begins to glow red from the heat of the forge.");
	    break;
        }
    }

    set_alarm(10.0, 0.0, "third_message", str);
}

public void first_message(string str)
{
    switch(str)
    {
	case "shortsword":
	case "longsword":
	case "broadsword":
	{
	    gSmith->command("emote pulls a thin strip of metal from a bucket "+
		"beside the forge and begins to heat it.");
            break;
        }

        case "mace":
	case "morning-star":
	case "warhammer":
	{
	    gSmith->command("emote pulls a bar of metal from a bucket beside "+
		"the forge and begins to heat it.");
	    break;
        }
    }

    set_alarm(10.0, 0.0, "second_message", str);
}

public int do_order(string str)
{
    str = lower_case(str);
    
    if (member_array(str, WEAPONS) == -1)
    {
	gSmith->command("say I only make the weapons on that there list!");
	gSmith->command("emote points at the list on the wall.");
	return 1;
    }

    if (present("_mercenary_"+str+"_", find_object(STORE_ROOM)))
    {
	gSmith->command("say Are ya blind? There's already a "+str+" on "+
	    "the shelf!");
	return 1;
    }

    if (query_ordering() == 1)
    {
	gSmith->command("say Confound it! Can't ya see I'm already busy at "+
	    "the forge? Wait a blasted minute!");
        return 1;
    }

    set_ordering(1);
    gSmith->command("emote picks up his hammer and turns to the forge.");
    gSmith->command("emote mumbles something.");
    set_alarm(5.0, 0.0, "first_message", str);
    return 1;
}


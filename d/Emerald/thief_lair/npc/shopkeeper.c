/* Ewam. The supply master for the bandits. He operates the "shop" where
   players may sell and purchase weapons stolen from the local elvish
   militia. 
   Code (c) 1999 Damian Horton. BKA Casimir. Much of this code is based
   upon the work of Milan's shop in the goblin caves, and Maniac's shop
   in Gelan.
*/

#pragma strict_types
#pragma save_binary 

#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <options.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Emerald/defs.h"

inherit THIEF_LAIR_DIR + "npc/base_thug.c";
/* Ewam behaves just like any other thug when he is attacked, and
   he follows orders like any thug. Note, however, that he uses
   his own special_attack routine.
*/

inherit "/d/Emerald/lib/shop.c";
inherit THIEF_LAIR_DIR + "/npc/intro"; // Ewam introduces himself.

// Special attack prototypes.
int smash(object enemy);
int charge(object enemy);

// Global variables

static mixed *store_inventory; // A list of the contents of the store_inventory
                               // room in the bandits lair.

void
create_bandit()
{
    set_name("Ewam");
    add_name("_Ewam");
    add_name("ewam");
    set_title("Brigand Supply Master");
    set_race_name("human");
    set_adj("fat");
    add_adj("robust");
    set_long("A large, somewhat flabby yet solid-looking human. He "+
	     "may be inclined to trade with you. You might "+
	     "try to 'sell' something to him, or, perhaps, 'buy' "+
	     "something from the 'list' of things he is willing to "+
	     "part with.\n");

    set_appearance(35);
    add_prop(CONT_I_HEIGHT, 195);
    add_prop(CONT_I_WEIGHT, 135000);
    add_prop(CONT_I_VOLUME, 145000);
    
    set_stats(({122,72,126,76,76,125}));
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT,65);
    set_skill(SS_AWARENESS, 70);
    set_alignment(-400);
    set_exp_factor(130); // Frequent and very damaging specials.

    add_equipment(({THIEF_LAIR_DIR + "wep/ewams_club",
			THIEF_LAIR_DIR + "arm/iron_ringmail", 
			THIEF_LAIR_DIR + "arm/iron_helm",
			THIEF_LAIR_DIR + "arm/quilt_leggings"}));

    set_act_time(9);
    add_act("emote grumbles about the quality of food he has been eating "+
	    "of late.");
    add_act("say We might be able to come to an arrangement, if you have any "+
	    "weapons or armours to sell.");
    add_act("emote inspects the items in the alcove behind him.");
    
    set_cact_time(7);
    add_cact("say I will crush you, fool!");
    add_cact("emote is becoming exceedingly violent!");

    set_special_attack_percent(30);
    add_special_attack(smash, 100, "smash");

    // Shop functionalities:
    
    create_emerald_shop();
    set_store_room(THIEF_LAIR_DIR + "store_inventory");
    set_money_greed_sell(125); //Not the most profitable place to trade. 
    set_money_greed_buy(125);
//    set_my_give_out(({ 10000, 400, 5, 1}));

    setuid();
    seteuid(getuid());
}
 
/* sets unarmed combat off, giving more axe attacks! */
int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}


/* Determines whether or not a given object can see.
   returns 0 if it can, 1 if the object cannot.
*/
   
int
check_blind(object ob)
{
    return (!CAN_SEE_IN_ROOM(ob) || !CAN_SEE(ob, this_object()));
}

// Damage special.
 
int
smash(object enemy)
{
    mixed* hitresult;   // Result of the special attack. 
    string how;         // Damage verb.     

    int var1;           // Number of clubs he wields.
    int difficulty = 0; // How hard it is to smash a foe.

//  Does he wield a club with which to smash?
   
    var1 = sizeof(filter(this_object()->query_weapon(-1),&->id("club")));
  
    if (var1 == 0) // He does not wield a club...
    {
	return charge(enemy);  // He will charge instead.	
    }

    if (check_blind(this_object()))
    {
	difficulty = 325; // Hard to smash things when you cannot see.
    }

    if ((enemy->query_stat(SS_WIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(450) - difficulty))
    {
	hitresult = enemy->hit_me(100 + random (200), W_BLUDGEON, this_object(), -1);
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->catch_msg(QCTNAME(this_object()) + " crushes your skull with "+
			     "his heavy club!\n");
 	    tell_watcher(QCTNAME(this_object()) + " crushes " + QTNAME(enemy) +
			 "'s skull with his heavy club!\n", enemy);
	    enemy->do_die(this_object());
	}

	else
	{
	    how = ({ "bruised",
		     "brutally battered", 
		     "seriouly beaten",
		     "pulverized" })[min(3, hitresult[0] / 20)];
	    
	    enemy->catch_msg(QCTNAME(this_object()) + " smashes you with his "+
			     "heavy club. You are "+ how +"!\n");
	    tell_watcher(QCTNAME(this_object()) + " smashes "+
			 QTNAME(enemy) + " with his heavy club. "+
			 capitalize(enemy->query_pronoun()) + " is " + how +"!\n",
			 enemy);
	}
    }

    else
    {
	enemy->catch_msg("You manage to evade " + QTNAME(enemy) + "'s "+
			 "dangerous swing!\n");
    }
    return 1;
}  

/* Alternate damage special, in case he does not happen to have a club at the
   time, perhaps because it has been brawled from this grasp. Not as effective.
*/

int
charge(object enemy)    
{
    // Since this function is called from smash, we need to use new variables.

    mixed* hitresult2;    // Result of the special attack. 
    string how2;          // Damage verb.     
    int difficulty2 = 0;  // Difficulty to charge.

    if (check_blind(this_object()))
    {
	difficulty2 = 175; // Harder to charge  things when you cannot see.
    }

    if ((enemy->query_stat(SS_WIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(400) - difficulty2))
    {
	hitresult2 = enemy->hit_me(100 + random (200), W_BLUDGEON, this_object(), -1);
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->catch_msg(QCTNAME(this_object()) + " charges into you at full "+
			     "speed, running right over you! You are too stunned "+
			     "to move!\nTaking "+
			     "advantage of your prone position, he brings his "+
			     "foot down on your throat.\n");

 	    tell_watcher(QCTNAME(this_object()) + " charges into "+
			 QTNAME(enemy) + "at full speed, running right over "+
			 enemy->query_objective() + "! " + QCTNAME(enemy) +
			 "lies motionless on the ground, allowing "+
			 QTNAME(this_object()) + "to step on " +
			 enemy->query_possessive() + "throat and end "+
			 enemy->query_possessive() + " suffering.\n", enemy);

	    enemy->do_die(this_object());
	}

	else
	{

	    how2 = ({ "dazed",
		     "winded", 
		     "crushed",
		     "pulverized" })[min(3, hitresult2[0] / 20)];
	  
	    enemy->catch_msg(QCTNAME(this_object()) + " charges right into "+
			     "you! You are " + how2 +"!\n");
	    tell_watcher(QCTNAME(this_object()) + " charges right into "+
			 QTNAME(enemy) + "! " + capitalize(enemy->query_pronoun()) +
			 " is " + how2 + "!\n", enemy); 
	}
    }

    else
    {
	enemy->catch_msg("You step aside, as " + QTNAME(this_object()) +
			 " charges right past you!\n");
	tell_watcher(QCTNAME(enemy) + " steps aside as " +
		     QTNAME(this_object()) + " charges right past "+
		     enemy->query_objective() + "!\n", enemy);
    }
    return 1;
}

/* Store functionality modified, starting below this line ----------- 

- Heavily modified version of /lib/shop.c
  I have left some of the documentation of the original, where applicable.
  Basically, rather than just writing a message to the player trying
  to buy, sell, etc., Ewam says these things instead.
*/

/* Advanced implementation of check_blind(). Called to see if
   Ewam can see well enough to perform any transactions. Returns
   0 if Ewam cannot see.
*/
int
check_light()
{
    if (check_blind(this_object()))
    {
	command("say Is someone talking to me?");
	return 0;
    }
    return 1;
}

/*
 * Function name: shop_hook_sell_no_match
 * Description:   Hook that is called when players tried to sell something
 *		  but we couldn't understand what he wanted to sell
 * Arguments:	  str - The string player tried to sell
 * Returns:	  0
 */

int
shop_hook_sell_no_match(string str)
{
    command("say Hey! What are you trying to pull on me?!?");
    notify_fail("");
    return 0;
}

/*
 * Function name: shop_hook_sell_no_value
 * Description:   Called if object has no value
 * Arguments:     ob - The object
 */
void
shop_hook_sell_no_value(object ob)
{
    command("say Hey! " + capitalize(LANG_THESHORT(ob)) + " is "+
	    " worthless!");
}


/*
 * Function name: shop_hook_sell_no_sell
 * Description:   An object has the no sell prop set (OBJ_M_NO_SELL)
 * Arguments:	  ob  - The object
 *		  str - Set if object has an own not sell string
 */
void
shop_hook_sell_no_sell(object ob, string str)
{
    if (stringp(str))
	notify_fail(str);
    else
    {
	command("say I have no interest in the " + LANG_THESHORT(ob) + ".\n");
	notify_fail("");
    }
}

/*
 * Function name: shop_hook_sell_object_stuck
 * Description:   Object didn't want to be moved to the store room
 * Arguments:	  ob  - The object
 *		  err - Error code from move
 */
void
shop_hook_sell_object_stuck(object ob, int err)
{
    command("say It seems you are stuck with " + LANG_THESHORT(ob) + ".");
}

/*
 * Function name: shop_hook_sell_get_money
 * Description:   Called when player gets money for the stuff he sold
 * Arguments:     str - String describing the money he got
 */
void
shop_hook_sell_get_money(string str)
{
    this_player()->catch_msg(QCTNAME(this_object()) + " gives "+
		   "you " + str + ".\n");
    say(QCTNAME(this_object()) + "hands " + QTNAME(this_player()) +
	" some coins.\n");
}

/*
 * Function name: shop_hook_buy_no_match
 * Description:   Called if we can't find what player wants to buy
 * Arguments:	  str - The string the player typed in
 * Returns:	  0
 */
int
shop_hook_buy_no_match(string str)
{
    command("emote 's eyes narrow in irritation.");
    command("say There is no '" + str + "' in stock!");
    notify_fail("");
}

/*
 * Function name: shop_hook_buy_no_buy
 * Description:   The item isn't for sale (OBJ_M_NO_BUY set)
 * Arguments:     ob  - the object
 *                str - the fail text (if any)
 */
void
shop_hook_buy_no_buy(object ob, string str)
{
    if (stringp(str))
        notify_fail(str);
    else
    {
        notify_fail("");
	command("say Uhm... On second thought, I'd like to keep the "+
		str + ".");
    }
}

/*
 * Function name: shop_hook_buy_cant_pay
 * Description:   Called when player can't pay for what he wants to buy.
 *		  The /lib/trade.c sets some default error messages but
 *		  perhaps you are not happy with them?
 * Arguments:	  ob - The object
 *		  arr - The error code as it comes from trade.c
 */
void 
shop_hook_buy_cant_pay(object ob, int *arr)
{
    notify_fail("");
    command("emote scowls.");
    command("say Perhaps when you have some money, I will sell you the "+
	    ob->short() + "!");      
}

/*
 * Function name: shop_hook_buy_cant_carry
 * Description:   Player can't carry the object he tried to buy
 * Arguments:     ob  - The object
 *		  err - Error code from move()
 */
void
shop_hook_buy_cant_carry(object ob, int err)
{
    command("emote begins to laugh loudly.");
    command("say Why, it seems that you are too weak to carry "+
	    LANG_THESHORT(ob) + ".");
    notify_fail("");
}

/*
 * Function name: shop_hook_buy_magic_money
 * Description:	  Called if we failed to take the money from the player for
 *		  some strange reason (magic money , fool's gold ? )
 * Arguments:	  ob - The object player tried to buy
 */
void
shop_hook_buy_magic_money(object ob)
{
    command("say Hey! What are you trying to pull on me?!?");    
}

/*
 * Function name: shop_hook_buy_pay_money
 * Description:   Called when player pays the money for something
 * Arguments:     str    - How much he pays in text form
 *		  change - The change he gets back (if any)
 */
void
shop_hook_buy_pay_money(string str, string change)
{
    write("You pay " + str);
    if (change)
	write(" and get " + change + " back");
    write(".\n");
    say(QCTNAME(this_player()) + " hands some coins to " + 
		QTNAME(this_object()) + ".\n");
    
}

/*
 * Function name: shop_hook_value_not_interesting
 * Description:   Called when player values something we don't want to buy
 * Arguments:	  ob - The object
 */
void
shop_hook_value_not_interesting(object ob)
{
    notify_fail("");
    command("say I have no interest in the  " + capitalize(LANG_THESHORT(ob)) +
	    ".");
}

/*
 * Function name: shop_hook_value_held
 * Description:   Player values an object he's holding
 * Arguments:	  ob   - The object
 *		  text - The price in text form
 */
void
shop_hook_value_held(object ob, string text)
{
    command("say " + (break_string("You would get " + text + " for " +
		LANG_THESHORT(ob) + ".\n", 75)));
}

/*
 * Function name: shop_hook_value_store
 * Description:   Player values object in store
 * Arguments:     ob   - The object 
 *		  text - The value in text form
 */
void
shop_hook_value_store(object ob, string text)
{
    command("say " + (break_string(capitalize(LANG_THESHORT(ob)) +
	" would cost you " + text + ".\n", 75)));
}


/*
 * Function name: shop_hook_value_asking
 * Description:   What other see when someone evaluates something
 * Arguments:     str - The text form what the player is asking about
 */
void
shop_hook_value_asking(string str)
{
    say(QCTNAME(this_player()) + " asks " + QCTNAME(this_object()) +
	"something.\n");
}

/*
 * Function name: shop_hook_value_no_match
 * Description:   Called if there were no match with what the player asked
 *		  about
 * Arguments:     str - The string player asked about
 * Returns:	  0
 */
int
shop_hook_value_no_match(string str)
{
    notify_fail("");
    command("say I have no " + str + " to show you.");
}

/*
 * Function name: shop_hook_list_empty_store
 * Description:   If the storeroom is empty when the player wants a list
 *		  of its items
 * Arguments:	  str - If player specified string
 */
void
shop_hook_list_empty_store(string str)
{
    command("say We are not interested in selling anything, at this time.");
}


/*
 * Function name: shop_hook_list_no_match
 * Description:   Called if player specified the list and no matching
 *		  objects where found
 * Arguments:	  str - The string he asked for
 * Returns:	  0
 */
int
shop_hook_list_no_match(string str)
{
    notify_fail("");
    command("say I have no " + str + "' in stock.\n");
}

/*
 * Function name: shop_hook_fail_storeroom
 * Description  : This function is called when a player tries to enter
 *                the storeroom. The function operates on this_player().
 */

void
shop_hook_fail_storeroom()
{
    tell_room(environment(this_player()),
	      QCTNAME(this_object()) + " steps in front of " +
	      QTNAME(this_player()) + " preventing " + 
	      this_player()->query_objective() +
	      " from progressing into the alcove.",
	      0, this_object());
    command("say You are not allowed in there!!"); 
}

string 
message_sell_worn_or_wielded()
{
    command("say "+TP->query_nonmet_name()+", you's specified to sell "+
                  "worn or wielded objects, deary.");
     return "";
}

/* Called whenever a player tries to trade (buy, sell etc.)
   with Ewam. Returns 0 if Ewam will not trade with that individual.
*/

int
check_trade(string arg)
{
    object enemy;
    string buyers_real_name;
    string who;

    buyers_real_name = this_player()->query_real_name(); //The player trying to buy stuff.

/* Not yet implemented...

  if (TP->query_prop(BANDIT_FOE)) { 
	
	// The player is an enemy of the bandits:

	command("spit " + buyers_real_name); 
	command("say to " + buyers_real_name + " Oh, you think I will trade with you "+
	    "do you?!");
	command("say You will die, you insolent bastard!");
	command("kill " + buyers_real_name);
	
	notify_fail("");
        return 0;
    }
*/
    
    who = this_player()->query_nonmet_name();
    if(enemy = this_object()->query_attack())   
    {
	if(enemy == TP)
	{
	    // Trying to trade while fighting Ewam!!!

	    command("say Just who the hell do you think you are?!");
	    smash(enemy); //Ask a stupid question ... it might hurt. ;)
	}
    
	else
	{

	    // Trying to trade while Ewam is under attack:

	    command("say Maybe if you helped me out...");
	    command("emote 's face colors with anger.");
	    command("say I would CONSIDER trading with you!!");
	}
	return 0;
    }
    else
    { 
	//All's well. Ewam will trade with that player.

	return 1;
    }
}

// This is what happens when a player attempts to "value" something.
// Im not certain that I wish to keep this functionality...

int
do_value(string args)
{
    // Is it possible to value items right now?
    if(!check_trade("value"))
    {
	notify_fail("");
   	return 0;
    }

    // Can he see?
    if(!check_light())
    {
	notify_fail("");
	return 0;
    }
    
    if (!args || args == "")
    {
	command("emote appears impatient");
	command("emote snarls: What is it that you interests you?");
	notify_fail("");
	return 0;
    }
    if (args == "all" || args == "all!")
    {
	notify_fail("");
	TP->catch_msg("You ask " + QTNAME(this_object())+ " about the "+
		      "values of everything.\n");
	say(QCTNAME(TP)+" asks " + QTNAME(this_object()) + " about the "+
	    "values of everything.\n");
	command("emote growls: Be specific!");
	return 0;
    }

    TP->catch_msg("You ask " + QTNAME(this_object()) + " about the value of the "+
		  args + ".\n");
    say(QCTNAME(TP)+" asks " + QTNAME(this_object()) + " about the value of the "+
	args + ".\n");

    return ::do_value(args);
}

int
do_buy(string args)
{
    if(!check_trade("buy"))
    {
	notify_fail("");
	return 0;
    }

    if(!check_light()) 
    {
	notify_fail("");
	return 0;
    }

    if (!args || args =="")
    {
	command("emote impatiantly growls: What is it that you wish "+
	    "to buy?");
	notify_fail("");
	return 0;
    }

    TP->catch_msg("You ask " + QTNAME(this_object()) + 
		  " to sell you the " + args + ".\n");
    say(QCTNAME(TP) + " asks " + QTNAME(this_object()) + " to sell "+
	TP->query_objective() + " the " + args + ".\n");

    return ::do_buy(args);
}

/* The player is trying to sell something.
 */

int
do_sell(string args)
{
    if(!check_trade("sell"))
    {
	notify_fail("");
	return 0;
    }

    if(!check_light())
    {
	notify_fail("");
	return 1;
    }

    if (!args || args == "")
    {
	command("emote growls: What is it that you wish to sell me?");
	notify_fail("");
	return 1;
    }

    if((args != "all") && (args != "all!"))
    {
	TP->catch_msg("You offer the " + args + " to " + QTNAME(this_object()) + ".\n");
	say(QCTNAME(TP)+" offers the " + args + " to " + QTNAME(this_object()) + ".\n");
    }
    else
    {
	TP->catch_msg("You offer all your possessions to " + QTNAME(this_object())
		      +".\n");
	say(QCTNAME(TP)+" offers all " + TP->query_possessive() + " possessions to "+
	    QTNAME(this_object()) + ".\n");
    }
    return ::do_sell(args);
}

int
do_list(string str)
{
    object *item_arr;
    int i, price, *arr, j;

    if(!check_trade("list"))
    {
	notify_fail("");
	return 0;
    }

    if(!check_light())
    {
	notify_fail("");
	return 0;
    }

    if (str && (str != "all") && (str != "all!"))
    {
	TP->catch_msg("You ask " + QTNAME(this_object()) +
		      " about available " + str + ".\n");
	say(QCTNAME(TP) + " asks " + QTNAME(this_object()) + 
	    " about available " + str + ".\n");
    }
    else
    {
	TP->catch_msg("You ask " + QTNAME(this_object()) + 
		      " what is for sale.\n");
	say(QCTNAME(TP) + " asks " + QTNAME(this_object()) + 
	    " what is for sale.\n");
    }

    call_other(THIEF_LAIR_DIR + "store_inventory", "load_me");
    item_arr = all_inventory(find_object(THIEF_LAIR_DIR + "store_inventory"));

    if (!sizeof(item_arr))
    {
	shop_hook_list_empty_store(str);
	notify_fail("");
	return 0;
    }

    if (str == "weapons")
        item_arr = filter(item_arr, "weapon_filter", this_object());
    else if (str == "armours")
            item_arr = filter(item_arr, "armour_filter", this_object());
    else if (str)
    {	
	item_arr = FIND_STR_IN_ARR(str, item_arr);
    }

    if (sizeof(item_arr) < 1)	
	return shop_hook_list_no_match(str);
 
    command("say I have " + COMPOSITE_DEAD(item_arr) + 
	    " which I would consider selling - for the right price.");
    return 1;
}

/* Identifies Ewam as a bandit - this is done chiefly so that
   he will prevent people from entering the store room.
*/
public int
query_bandit()
{
    return 1;
} 
    
void
init_living()
{
    ::init_living();
    // Add shop commands
    init_emerald_shop();
}
 

















/*
 * weapon_repairs.c
 *
 * A lib module for smiths who can repair (sharpen/polish)
 * weapons.
 *
 * One warning: This will _only_ work for living smiths, and must
 * be inherited into npc's. If you inherit it into a room, it'll
 * probably still work fine, but almost all of the messages will
 * never happen, as most are delivered with this_object()->command.
 *
 * Functions:
 *
 * init_smith_repairs: Call this function from the init_living
 *                     of the npc to activate repair commands.
 *
 * Those three are the only functions you'll usually want to use, 
 * however, most of the stages in the repair procedure have hook
 * functions you can redefine to change parts. Be careful if you
 * do this, as it's necessary that some of the functions be able
 * to differentiate between 'sharpening' and 'polishing'.
 *
 * hook_find_weapon: Redefine this function to change the way the
 *                   smith identifies weapons to repair.
 * hook_not_weapon: Redefine this function to change the way the
 *                  smith responds to requests to repair objects
 *                  that aren't weapons.
 * hook_magic_fail: Redefine this function to change the way the
 *                  smith reacts to being asked to sharpen magic
 *                  weapons. By default, they can't.
 * hook_weapon_type_fail: Redefine this function to change the way
 *                        the smith reacts to odd requests (if wanted)
 *                        such as sharpening a hammer. For example,
 *                        you might want a smith that will only repair
 *                        knives. Here's where to make the hook.
 * hook_no_repairs: Redefine this function to change the way the 
 *                  smith reacts to weapons that don't need repairs,
 *                  or can't be further repaired.
 * hook_calculate_price: Redefine this function to change the way the
 *                       smith charges for repairs. Alternatively,
 *                       the repair cost query functions can be masked
 *                       to handle special routines there, such as
 *                       different rates for a guild.
 * hook_no_money: Redefine this function to change the way the smith
 *                reacts to a customer having no money.
 * hook_begin_work: Redefine this function to customize any little
 *                  messages you might want the smith to say as he
 *                  begins actual construction.
 * 
 * Khail - April 21/97
 */
#pragma strict_type

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

/* Global Variables. */
static int repair_base_cost,
           repair_incr_cost;

/* Prototypes. */
public varargs void init_smith_repairs(string type);
public int set_repair_base_cost(int val);
public int query_repair_base_cost();
public int set_repair_incr_cost(int val);
public int query_repair_incr_cost();
public object hook_find_weapon(string str);
public int hook_not_weapon(object wep, string activity);
public int hook_magic_fail(object wep, string activity);
public int hook_weapon_type_fail(object wep, string activity);
public int hook_no_repairs(object wep, string activity);
public int hook_calculate_price(object wep, string activity);
public int hook_no_money(object wep, string activity);
public void hook_begin_work(object wep, string activity);
public int do_sharpen(string str);
public int do_polish(string str);
public int do_repair(string str);

/*
 * Function name: init_smith_repairs
 * Description  : Called to activate the repair commands.
 * Arguments    : type - String representing the type of work
 *                       done. Either 'sharp' for the sharpen and
 *                       polish commands, or 'blunt' for the repair
 *                       and polish commands. If left blank, all
 *                       three will be available.
 * Returns      : n/a
 */
public varargs void
init_smith_repairs(string type)
{
    add_action(do_polish, "polish");
    if (!type || type == "sharp")
        add_action(do_sharpen, "sharpen");
    if (!type || type == "blunt")
        add_action(do_repair, "repair");
}

/*
 * Function name: set_repair_base_cost
 * Description  : Sets the base repair cost (as a percent of the weapon's
 *                value) for any repairs. For example, setting this value
 *                to 25 would result in a weapon with a value of 1000
 *                copper costing at _least_ 250 coppers to repair.
 * Arguments    : val - Any positive integer.
 * Returns      : 0 - Failed (attempted value was less than 1)
 *                1 - Success
 */
public int
set_repair_base_cost(int val)
{
    if (val < 1)
        return 0;
    repair_base_cost = val;
    return 1;
}

/*
 * Function name: query_repair_base_cost
 * Description  : Queries the repair_base_cost variable.
 * Arguments    : n/a
 * Returns      : As described.
 */
public int
query_repair_base_cost()
{
    return repair_base_cost;
}

/*
 * Function name: set_repair_incr_cost
 * Description  : Sets the incremental repair cost (as a percent of
 *                the weapon's value) for any repairs. This percent
 *                is added to the base percent for each time the
 *                weapon in question has already been repaired. For
 *                example, with a base of 10% and an incremental of
 *                2%, a weapon that's been repaired 2 times would
 *                cost 14% of it's value to repair again. Specifying
 *                a value of 0 means no incremental cost.
 * Arguments    : val - Any positive integer or 0.
 * Returns      : 0 - Fail (attempted value was less than 0)
 *                1 - Success
 */
public int
set_repair_incr_cost(int val)
{
    if (val < 0)
        return 0;
    repair_incr_cost = val;
    return 1;
}

/*
 * Function name: query_repair_incr_cost
 * Description  : Queries the repair_incr_cost variable.
 * Arguments    : n/a
 * Returns      : As described
 */
public int
query_repair_incr_cost()
{
    return repair_incr_cost;
}

/*
 * Function name: hook_find_weapon
 * Description  : Tries to match the string to a weapon in the player's
 *                inventory.
 * Arguments    : str - String to match, i.e. 'second sword'.
 * Returns      : 0 - No weapon found.
 *                else Object pointer to weapon found.
 */
public object
hook_find_weapon(string str)
{
    object *temp;

    if (!sizeof(temp = FIND_STR_IN_OBJECT(str, TP)))
    {
        TO->command("scratch");
        TO->command("say I'd like to, but I don't see " +
            LANG_ADDART(str) + " on you.");
        return 0;
    }

    if (sizeof(temp) > 1)
    {
        TO->command("say Slow down, one at a time!");
        return 0;
    }

    return temp[0];
}

/*
 * Function name: hook_not_weapon
 * Description  : Fails if the given object isn't a weapon and delivers
 *                appropriate responses.
 * Arguments    : wep - Object pointer to the object to test.
 *                activity - Name of the repair being performed. I.e
 *                           "sharpen"
 * Returns      : 0 - Yes, this is a real weapon.
 *                1 - No, this isn't a real weapon.
 */
public int
hook_not_weapon(object wep, string activity)
{
    string master;

    if (!(master = function_exists("check_weapon", wep)) ||
        master != "/std/weapon")
    {
        TO->command("peer " + OB_NAME(TP));
        TO->command("say Just how bloody stupid are you? That's " +
            "not even a weapon!");
        return 1;
    }
    return 0;
}

/*
 * Function name: hook_magic_fail
 * Description  : Called by the repair routines to test if the weapon
 *                to repair is magic. If it is, we can't repair it.
 *                Appropriate failure messages are generated here.
 * Arguments    : wep - Object pointer to the weapon to test.
 *                activity - "sharpen" or "polish"
 * Returns      : 0 - Can perform 'activity' on 'wep'.
 *                1 - 'wep' is magic, can't do anything with it.
 */
public int
hook_magic_fail(object wep, string activity)
{
    return 0;
}

/*
 * Function name: hook_weapon_type_fail
 * Description  : Ensures the weapon is of a type the npc can repair.
 *                For example, a bladesmith cannot 'sharpen' a club,
 *                but a blacksmith might be able to 'strengthen' it.
 * Arguments    : wep - Object pointer to the weapon to test.
 *                activity - String identifying the repair. i.e.
 *                           "sharpen" or "polish".
 * Returns      : 0 - Yes, we can perform 'activity' repair on 'wep'.
 *                1 - Fail, cannot do 'activity' on 'wep'.
 */
public int
hook_weapon_type_fail(object wep, string activity)
{
    return 0;
}

/*
 * Function name: hook_no_repairs
 * Description  : Ensures that the given weapon needs repairs and
 *                can be repaired. If a weapon can't be repaired,
 *                the reason is given from this function.
 * Arguments    : wep - Object pointer to the weapon to repair.
 *                activity - String label for what the repair is.
 *                           Currently, either "sharpen" or "polish".
 * Returns      : 0 - 'wep' may be repaired.
 *                1 - 'wep' cannot be repaired.
 */
public int
hook_no_repairs(object wep, string activity)
{
    int oldrepair,
        val;

  /* Figure out what the type of repair is. */
    switch (activity)
    {
      /* Here, we're trying to sharpen the weapon. */
        case "sharpen":
            oldrepair = wep->query_repair_dull();
            val = wep->query_dull();

          /* Can't sharpen a weapon that doesn't need sharpening. */
            if (oldrepair == val)
            {
                TO->command("say There's nothing wrong with the edge " +
                    "on that " + W_NAMES[wep->query_wt()] + " as " +
                    "it is.");
                return 1;
            }

          /* Can't sharpen a weapon that's been sharpened as many */
          /* times as it can already. */
            else if (!F_LEGAL_WEAPON_REPAIR_DULL(oldrepair + 1, val))
            {
                TO->command("say Hmm, I don't think I can sharpen that " +
                    "anymore than it already has been, unfortunately.");
                return 1;
            }

          /* Ok, looks like we can sharpen this one. */
            else
                return 0;
            break;

      /* We want to polish the weapon (to reduce corrosion). */
        case "polish":
            oldrepair = wep->query_repair_corr();
            val = wep->query_corroded();
            if (oldrepair == val)
            {
                TO->command("say There's not enough buildup on that " + 
                     W_NAMES[wep->query_wt()] + " to bother with " +
                     "polishing.");
                return 1;
            }

            else if (!F_LEGAL_WEAPON_REPAIR_CORR(oldrepair + 1, val))
            {
                TO->command("say Hmm, I don't think polishing will help " +
                    "anymore, I'm afraid.");
                return 1;
            }
            else
                return 0;
            break;

        case "repair":
            oldrepair = wep->query_repair_dull();
            val = wep->query_dull();

            if (oldrepair == val)
            {
                TO->command("say There's nothing wrong with " +
                    "that " + W_NAMES[wep->query_wt()] + " as " +
                    "it is.");
                return 1;
            }

            else if (!F_LEGAL_WEAPON_REPAIR_DULL(oldrepair + 1, val))
            {
                TO->command("say Hmm, I don't think I can do much " +
                    "more for it, unfortunately.");
                return 1;
            }

            else
                return 0;
            break;

    }
    return 1;
}

/*
 * Function name: hook_calculate_price
 * Description  : Simply calculates the price of the repair based
 *                on the weapon's value and the number of repairs
 *                it's already had performed on it.
 * Arguments    : wep - Object pointer to the weapon to repair.
 *                activity - String describing the type of repair.
 * Returns      : the price in coppers.
 */ 
public int
hook_calculate_price(object wep, string activity)
{
    int price;
    switch (activity)
    {
        /* If we're sharpening, figure out how many times it's been */
        /* sharpened, multiply by the repair cost increment and add */
        /* that to the base to get the total % of the weapon's value */
        /* to charge as a price. */
    case "sharpen":
    case "repair":
        price = wep->query_repair_cost_dull();
        break;
        
        /* If we're polishing, perform the same calculations as for */
        /* sharpening, only figure out how many times it's been */
        /* polished instead of sharpened. */
    case "polish":
        price = wep->query_repair_cost_corr();
        break;
    }
    return price;
}

/*
 * FUnction name: hook_no_money
 * Description  : Tests and decides what to do if the player can't
 *                afford the repair, and delivers fail messages if
 *                necessary.
 * Arguments    : wep - Object pointer to the weapon to repair.
 *                activity - Name of the repair type as a string. I.e
 *                           "sharpen" or "polish".
 * Returns      : 0 - Yes, the player has the money.
 *                1 - No, the player doens't have the money.
 */
public int
hook_no_money(object wep, string activity)
{
    int price;

  /* Get the cost of the repair. */
    price = hook_calculate_price(wep, activity);

    TO->command("say It'll cost " + price + " coppers to " +
        activity + " that " + W_NAMES[wep->query_wt()] + ".");

  /* If the player doesn't have 'price' coppers, no repairs. */
    if (TOTAL_MONEY(TP) < price)
    {
        TO->command("say And I see by your face you don't have that " +
            "much. Come back when you've more coin in your " +
            "purse.\n");
        return 1;
    }

  /* Ok, player's got the money, deliver the right messages and */
  /* take the money, then allow repairs to continue. */
    write("You give " + TO->query_the_name(TP) + " the money, and " +
        "he takes your " + wep->short() + " to begin work.\n");
    say(QCTNAME(TP) + " gives " + QTNAME(TO) + " some money, who " +
        "takes " + TP->query_possessive() + " " + wep->short() +
        " to begin work.\n");
    MONEY_ADD(TP, -price);
    return 0;
}

/*
 * Function name: hook_begin_work
 * Description  : Just a simple little function that provides a 
 *                little more variety in what players see when
 *                the npc begins repairing their weapon. This
 *                particular one has 4 different responses based
 *                on the average WC of the weapon.
 * Arguments    : wep - Object pointer to the weapon to repair.
 *                string - Name of the type of repair. I.e. "sharpen"
 *                         or "polish"
 */            
public void
hook_begin_work(object wep, string activity)
{
    int wc,
        wt;

    TP->catch_msg(TO->query_The_name(TP) + " takes your " +
        wep->short() + " and examines it closely for a " +
        "moment.\n");
    say(QCTNAME(TO) + " takes " + LANG_ADDART(wep->short()) +
        " from " + QTNAME(TP) + " and examines it closely " +
        "for a moment.\n");

    wc = (wep->query_hit() + wep->query_pen()) / 2;
    wt = wep->query_wt();

    if (wc < 10)
    {
        TO->command("chuckle");
        TO->command("say This " + W_NAMES[wt] + " is barely worth " +
            activity + "ing ?");
    }
    else if (wc < 20)
    {
        TO->command("chuckle");
        TO->command("say Not much of " + LANG_ADDART(W_NAMES[wt]) +
            ", is it?");
    }
    else if (wc < 30)
    {
        TO->command("ponder");
        TO->command("say Not a bad " + W_NAMES[wt] + ", but I've seen " +
            "much better.");
    }
    else if (wc < 41)
    {
        TO->command("nod approvingly");
        TO->command("say Not bad, not bad at all. I don't often get " +
            W_NAMES[wt] + " like this in here.");
    }
    else
    {
        TO->command("whistle");
        TO->command("say Now this is a " + W_NAMES[wt] + "!");
    }
}

/*
 * Function name: do_sharpen
 * Description  : Allows someone to try and sharpen a weapon.
 * Arguments    : str - Argument passed with the 'sharpen' command,
 *                      should be the weapon the player wants to
 *                      sharpen.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
do_sharpen(string str)
{
    object wep;

  /* Fail if no arg given. */
    if (!str || !strlen(str))
    {
        NF("Sharpen what?\n");
        return 0;
    }

  /* Fail if we can't match 'str' to a single object in the player's */
  /* inventory. */
    if (!objectp(wep = hook_find_weapon(str)))
        return 1;

  /* Fail if the object found isn't a weapon. */
    if (hook_not_weapon(wep, "sharpen"))
        return 1;

  /* Fail if the weapon is magic, as we can't sharpen it. */
    if (hook_magic_fail(wep, "sharpen"))
        return 1;

  /* Fail if the weapon is of a type that can't be sharpened. */
  /* A staff or a hammer, for example. */
    if (hook_weapon_type_fail(wep, "sharpen"))
        return 1;

  /* Fail if the weapon cannot be repaired, either because it */
  /* does not need repairs, or has been repaired as many */
  /* times as it can already. */
    if (hook_no_repairs(wep, "sharpen"))
        return 1;

  /* Fail if the player doesn't have the money for the repair. */
    if (hook_no_money(wep, "sharpen"))
        return 1;

  /* Some messages when the npc begins work on the weapon. */
    hook_begin_work(wep, "sharpen");    

  /* Actually repair the weapon. No checks for success needed */
  /* here, as it was already done in hook_no_repairs(). */
    wep->set_repair_dull(wep->query_repair_dull() + 1);
    
    tell_room(environment(TO), QCTNAME(TO) + " quickly sharpens " +
        "the " + wep->short() + " with some skilled passes across " +
        "a sharpening stone, then holds it up to the light and " +
        "examines his work.\n");
    TO->command("emote nods in satisfaction.");
    TO->command("say There you go.");
    write(TO->query_The_name(TP) + " hands back your " +
        wep->short() + ".\n");
    say(QCTNAME(TO) + " hands the " + wep->short() + " back to " +
        QTNAME(TP) + ".\n");
    return 1;
}


/*
 * Function name: do_polish
 * Description  : Allows someone to try and polish a weapon.
 * Arguments    : str - Argument passed with the 'polish' command,
 *                      should be the weapon the player wants to
 *                      polish.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
do_polish(string str)
{
    object wep;

  /* Fail if no arg given. */
    if (!str || !strlen(str))
    {
        NF("Polish what?\n");
        return 0;
    }

  /* Fail if we can't match 'str' to a single object in the player's */
  /* inventory. */
    if (!objectp(wep = hook_find_weapon(str)))
        return 1;

  /* Fail if the object found isn't a weapon. */
    if (hook_not_weapon(wep, "polish"))
        return 1;

  /* Fail if the weapon is magic, as we can't sharpen it. */
    if (hook_magic_fail(wep, "polish"))
        return 1;

  /* Fail if the weapon is of a type that can't be sharpened. */
  /* A staff or a hammer, for example. */
    if (hook_weapon_type_fail(wep, "polish"))
        return 1;

  /* Fail if the weapon cannot be repaired, either because it */
  /* does not need repairs, or has been repaired as many */
  /* times as it can already. */
    if (hook_no_repairs(wep, "polish"))
        return 1;

  /* Fail if the player doesn't have the money for the repair. */
    if (hook_no_money(wep, "polish"))
        return 1;

  /* Some messages when the npc begins work on the weapon. */
    hook_begin_work(wep, "polish");    

  /* Actually repair the weapon. No checks for success needed */
  /* here, as it was already done in hook_no_repairs(). */
    wep->set_repair_corr(wep->query_repair_corr() + 1);
    
    tell_room(environment(TO), QCTNAME(TO) + " spreads a handful " +
        "of fine white shand on the " + wep->short() + " and " +
        "quickly rubs at it with a piece of leather, scouring " +
        "off the corrision.\n");
    TO->command("emote finishes the scrubbing, and blows the last of " +
        "the sand off, carefully making sure he got as much as " +
        "he can off the weapon. He then completes the task by " +
        "rubbing it lightly with some oil.");
    TO->command("say There you go.");
    write(TO->query_The_name(TP) + " hands back your " +
        wep->short() + ".\n");
    say(QCTNAME(TO) + " hands the " + wep->short() + " back to " +
        QTNAME(TP) + ".\n");
    return 1;
}

/*
 * Function name: do_repair
 * Description  : Allows someone to try and repair a weapon.
 *                Differs only from 'sharpen' in that this is used
 *                for non-edged weapons.
 * Arguments    : str - Argument passed with the 'repair' command,
 *                      should be the weapon the player wants to
 *                      sharpen.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
do_repair(string str)
{
    object wep;

  /* Fail if no arg given. */
    if (!str || !strlen(str))
    {
        NF("Repair what?\n");
        return 0;
    }

  /* Fail if we can't match 'str' to a single object in the player's */
  /* inventory. */
    if (!objectp(wep = hook_find_weapon(str)))
        return 1;

  /* Fail if the object found isn't a weapon. */
    if (hook_not_weapon(wep, "repair"))
        return 1;

  /* Fail if the weapon is magic, and we can't repair it. */
    if (hook_magic_fail(wep, "repair"))
        return 1;

  /* Fail if the weapon is of a type that can't be sharpened. */
  /* A staff or a hammer, for example. */
    if (hook_weapon_type_fail(wep, "repair"))
        return 1;

  /* Fail if the weapon cannot be repaired, either because it */
  /* does not need repairs, or has been repaired as many */
  /* times as it can already. */
    if (hook_no_repairs(wep, "repair"))
        return 1;

  /* Fail if the player doesn't have the money for the repair. */
    if (hook_no_money(wep, "repair"))
        return 1;

  /* Some messages when the npc begins work on the weapon. */
    hook_begin_work(wep, "repair");    

  /* Actually repair the weapon. No checks for success needed */
  /* here, as it was already done in hook_no_repairs(). */
    wep->set_repair_dull(wep->query_repair_dull() + 1);
    
    tell_room(environment(TO), QCTNAME(TO) + " quickly performs " +
        "some basic repairs on the " + wep->short() + " and " +
        "examines it with a critical eye.\n");
    TO->command("emote nods in satisfaction.");
    TO->command("say There you go.");
    write(TO->query_The_name(TP) + " hands back your " +
        wep->short() + ".\n");
    say(QCTNAME(TO) + " hands the " + wep->short() + " back to " +
        QTNAME(TP) + ".\n");
    return 1;
}

/*
 * - /d/Avenir/inherit/craftsman.c
 * 
 * Taken from /d/Genesis/lib/craftsman and updated
 * to be less generic and staid. See that file for
 * usage information and function headers.
 *
 * * Lucius Apr 2009: Created.
 * * Lucius Apr 2018: Some minor updates and corrections.
 *
 */
#pragma strict_types
inherit "/d/Genesis/lib/craftsman";

#include <money.h>
#include <macros.h>
#include <language.h>

public static int speak;
public static string *exclamations = ({
	"amazing", "delightful", "fabulous", "fantastic",
	"magnificent", "marvelous", "perfect", "splendid", 
});

/*
 * Function name: prefer_speech
 * Description	: Setting wherby this object will appear
 * 		  more animated, and 'speak' questions.
 * Arguments	: int 1/0 - On / Off.
 * Note		: This should only be done for npc craftsman. 
 */
public void
prefer_speech(int i)	{ speak = i; }

/*
 * Function name: exclaim
 * Description	: Return an exclamation to spice up speech.
 * Arguments	: int cap - Whether to capitalize the output or not.
 */
public string
exclaim(int cap)
{
    string word = one_of_list(exclamations) + "!";
    return (cap ? capitalize(word) : word);
}

/*
 * Function name: tell_me
 * Description	: Provide psuedo speach to make things less drab.
 * Arguments	: string what - What speak.
 * 		  object  who - Who to speak with, default is this_player().
 */
public void
tell_me(string what, object who = this_player())
{
    if (!speak)
    {
	who->catch_tell(what);
	return;
    }

    who->catch_tell(this_object()->query_The_name(who) +
	" tells you: "+ what);

    switch(random(3))
    {
    case 1:
	what = QCTNAME(this_object()) +
	    " speaks privately with "+ QTNAME(who) +".\n";
	break;
    case 2:
	what = QCTNAME(who) +
	    " speaks privately with "+
	    QTNAME(this_object()) +".\n";
	break;
    default:
	what = "";
	break;
    }

    if (strlen(what))
    {
	tell_room(environment(this_object()),
	    what, ({ who, this_object() }), this_object());
    }
}

public int
craftsman_purchase_syntax_failure_hook(string str)
{
    if (strlen(str))
	tell_me("I don't sell '"+ str +"' here.\n");

    notify_fail("Try ordering one of these instead:\n     "+
	implode(item_names, " - ") + "\n");

    return 0;
}

public int
craftsman_purchase_exceeded_max_total_orders_hook(string str)
{
    tell_me("I cannot accept any more orders at this time.\n");
    return 1;
}

public int
craftsman_purchase_exceeded_max_user_orders_hook(string str)
{
    tell_me("I cannot accept any more orders at this time.\n");
    return 1;
}

public void
craftsman_purchase_hook(string str)
{
    tell_me("How would you like your " + str + " made?\n");
}

public void 
craftsman_config_invalid_attribute_value_hook(string attr, string value)
{
    tell_me("That is an invalid selection.\n");
}

public void
craftsman_notify_completion_time_hook(int t, int id)
{
    string str;

    if (t < 60)
    {
        str = "less than a minute";
    }
    else
    {
        /* drop seconds */
        t = t / 60;
        str = "about " + t + ((t == 1) ? " minute" : " minutes");
    }

    tell_me("Your order should take " + str + " to complete.\n");
}

public void
craftsman_notify_cost_hook(int id)
{
    int cost = craftsman_calc_item_cost(0, id);

    if (cost)
        tell_me("That will cost " + MONEY_TEXT_NUM_SPLIT(cost) + ".\n");
}

public void
craftsman_notify_cancel_hook(int id)
{
    tell_me("If you change your mind, just \"cancel order\".\n");
}

public void
craftsman_notify_check_hook(int id)
{
    tell_me("You may \"check order\" to see the status "+
	"of your order.\n");
    tell_me("It is also used to retrieve completed orders.\n");
}

public void
craftsman_notify_hold_time_hook(int hold, int id)
{
    if (hold > 0)
        tell_me("I will only hold your order for a limited time.\n");
}

public void
craftsman_abort_hook(void)
{
    tell_me("Very well, your order is cancelled.\n");
}

public int 
craftsman_cancel_syntax_failure_hook(string str)
{
    tell_me("Are you wishing to \"cancel order\"?\n");
    return notify_fail("");
}

public int
craftsman_cancel_unpurchased_item_hook(void)
{
    tell_me("You would need to purchase something first!\n");
    return 1;
}

public void
craftsman_cancel_order_hook(int id)
{
    tell_me("Very well, your order is cancelled.\n");
}

public void
craftsman_timeout_hook(int id)
{
    tell_me("You are taking too long, order cancelled.\n");
}

public void
craftsman_completed_order_hook(int id, string owner)
{
    object who = find_player(owner);

    if (!objectp(who))
	return;

    if (craftsman_query_object_present(who)) {
        tell_me("Your order has been completed.\n");
    } else {
	who->catch_tell("Your order with "+
	   this_object()->query_the_name(who) +
	   " has been completed.\n");
    }
}

public int
craftsman_check_syntax_failure_hook(string str)
{
    tell_me("Are you wishing to \"check order\"?\n");
    return notify_fail("");
}

public int
craftsman_check_unpurchased_item_hook(void)
{
    tell_me("You have yet to purchase anything!\n");
    return 1;
}

public void
craftsman_check_complete_order_hook(int *ids)
{
    int count = sizeof(ids);
    tell_me(capitalize(LANG_NUM2WORD(count)) +" of your "+
	"orders "+ (count > 1 ? "have" : "has") +" been completed.\n");
}

public void
craftsman_check_incomplete_order_hook(int *ids)
{
    int count = sizeof(ids);

    if (!count)
    {
        tell_me("You have no other orders ready.\n");
        return;
    }

    tell_me("You still have " + LANG_NUM2WORD(count) +
	(count > 1 ? " orders" : " order") +" being made:\n");

    craftsman_list_orders_hook(ids);
}

public void
craftsman_check_cannot_pay_hook(int cost, object ob, int id)
{
    tell_me("But you cannot afford it!\n");
    tell_me("You will need "+  MONEY_TEXT_NUM_SPLIT(cost) +".\n");
}

public void
craftsman_check_move_player_failed_hook(object ob)
{
    tell_me("You are cannot carry the "+ ob->short() + "!\n");
}

public void
craftsman_check_move_env_failed_hook(object ob)
{
    tell_me("There is no room for the "+ ob->short() + "!\n");
}

public void
craftsman_config_prompt_attribute_hook(string attr, string *valid_attrs)
{
    // Ensure that the 'none' option is always displayed last.
    if (sorted_attrs && (member_array("none", valid_attrs) >= 0))
    {
	valid_attrs -= ({ "none" });
	valid_attrs += ({ "none" });
    }

    ::craftsman_config_prompt_attribute_hook(attr, valid_attrs);
}

#if 0
public void
craftsman_check_receive_order_hook(object ob, int id)
{
    write("You receive your " + ob->short() + ".\n");
}
#endif


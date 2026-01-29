/* craftsman.c created by Shiva@Genesis
 * 
 * An inheritable module for creating shops to sell items with
 * player-selected attributes.
 *
 * Example usage:
 *
 * inherit "/d/Emerald/shiva/craftsman";
 * inherit "/std/monster";
 *
 * void create_monster()
 * {
 *     craftsman_set_name("craftsman");
 * 
 *     // possible names for the item sold
 *     craftsman_set_sold_item_names(({ "cloak" }));
 * 
 *     // the file for the item to clone
 *     craftsman_set_item_file("/d/Emerald/shiva/newcloak");
 * 
 *     // time in seconds to complete creation of the item
 *     craftsman_set_time_to_complete(30);
 * 
 *     // the cost of an item (in cc)
 *     craftsman_set_item_cost(800);
 *
 *     // attributes for the items with possible values
 *     craftsman_add_attribute("material", ({ "leather", "silk", "velvet" }));
 *     craftsman_add_attribute("color", ({ "ivory", "purple", "grey" }));
 *     craftsman_add_attribute("quality", ({ "crude", "splendid", "shoddy" }));
 * }
 *
 * void init_living()
 * {
 *     ::init_living();
 * 
 *     // add the craftsman's commands
 *     craftsman_init();
 * }
 * 
 * void craftsman_configure_item(object who, object ob, mapping attrs)
 * {
 *     ob->set_adj(m_values(attrs));
 *
 *     switch(attrs["material"])
 *     {
 *         case "leather":
 *             ob->set_ac(10);
 *             break;
 *         case "silk":
 *             ob->set_ac(2);
 *             break;
 *         case "velvet":
 *             ob->set_ac(4);
 *             break;
 *         case "wool":
 *             ob->set_ac(6);
 *             break;
 *     }
 * }
 */

#pragma strict_types

inherit "/lib/trade";

#include <language.h>
#include <money.h>

static string clone_file = "";
static string *item_names = ({});
static mapping attributes = ([]);
static int time_to_complete;
static int completion_alarm;
static int next_completion_time;
static int item_cost;
static int max_total_orders = 10;
static int max_user_orders = 1;
static int min_hold_time = 900;

mapping m_purchased_items  = ([]);
mapping m_completed_orders = ([]);

void craftsman_config_attributes(string *attrs, object who, mapping attr_map);
void craftsman_completed_config(object who, mapping attr_map);
void craftsman_completed_order(string name);
void craftsman_reset_completion_time();
void craftsman_clean_completed_orders();
int craftsman_calc_item_cost(object who, object ob, mapping attrs);

/*
 * Function name: craftsman_purchase_syntax_failure_hook
 * Description:   Redefine this to change the message given when the
 *                user gives incorrect arguments to the "purchase"
 *                command
 * Arguments:     object who - the user
 *                string str - the arguments given to the "purchase"
 *                             command.
 * Returns:       1/0
 */
public int
craftsman_purchase_syntax_failure_hook(object who, string str)
{
    notify_fail("We don't sell those here.\n");
    return 0;
}

/*
 * Function name: craftsman_purchase_exceeded_max_total_orders_hook
 * Description:   Redefine this to change the message given when the
 *                user has exceeded the maximum number of orders allowed
 *                for all users.
 * Arguments:     object who - the user
 *                string str - arguments to the order command (the item
 *                             to be ordered)
 * Returns:       0/1
 */
public int
craftsman_purchase_exceeded_max_total_orders_hook(object who, string str)
{
    write("Cannot accept any more orders at this time.\n");
    return 1;
}

/*
 * Function name: craftsman_purchase_exceeded_max_user_orders_hook
 * Description:   Redefine this to change the message given when the
 *                user has exceeded the maximum number of orders allowed
 *                for a single user.
 * Arguments:     object who - the user
 *                string str - arguments to the order command (the item
 *                             to be ordered)
 * Returns:       0/1
 */
public int
craftsman_purchase_exceeded_max_user_orders_hook(object who, string str)
{
    write("Cannot accept any more orders at this time.\n");
    return 1;
}

/* 
 * Function name: craftsman_purchase_hook
 * Description:   Redefine this to change the message given when
 *                a user tries to purchase an item.
 * Arguments:     object who - the user
 *                string str - the name of the item purchased
 */
public void
craftsman_purchase_hook(object who, string str)
{
    who->catch_tell("How would you like your " + str + " made?\n");
}

/*
 * Function name: craftsman_config_prompt_attribute_hook
 * Description:   Redefine this to change the message given to
 *                prompt the user to enter a attribute value.
 * Arguments:     object who          - the user
 *                string attr         - the attribute name
 *                string *valid_attrs - an array of valid selections
 */
public void
craftsman_config_prompt_attribute_hook(object who, string attr,
    string *valid_attrs)
{
    who->catch_tell(sprintf("\nSelect " + LANG_ADDART(attr) + 
        " from the following (~q to exit):\n%-#50s\n:", 
        implode(valid_attrs, "\n")));
}

/*
 * Function name: craftsman_config_invalid_attribute_value_hook
 * Description:   Redefine this to change the message given when the
 *                user selects an invalid value for an attribute
 * Arguments:     object who   - the user
 *                string value - the value selected for the attribute
 *                string attr  - the attribute name
 */
public void 
craftsman_config_invalid_attribute_value_hook(object who, string value,
    string attr)
{
    who->catch_tell("Invalid selection.\n");
}

/*
 * Function name: craftsman_config_validate_chosen_attribute_hook
 * Description:   Validate an attribute chosen and give any appropriate
 *                messages.
 * Arguments:     object who       - the user
 *                string attr      - the attribute
 *                string value     - the value chosen for the attribute
 *                mapping attr_map - a mapping containg attributes already 
 *                                   chosen.
 * Returns:       1 - value is valid
 *                0 - value is invalid and should be reentered
 *               -1 - valud is invalid, and configuration should be exited
 */
public int
craftsman_config_validate_chosen_attribute_hook(object who, string attr,
    string value, mapping attr_map)
{
    string *valid_values = attributes[attr];

    if (sizeof(valid_values) && (member_array(value, valid_values) < 0))
    {
        /* Invalid selection.  Prompt and ask again */
        craftsman_config_invalid_attribute_value_hook(who, value, attr);
        return 0;
    }

    return 1;
}

/*
 * Function name: craftsman_config_validate_chosen_attributes_hook
 * Description:   Validate the attributes chosen and give any appropriate
 *                messages.  This differs from
 *                craftsman_config_validate_chosen_attribute_hook in that
 *                it is only called after all attributes have been set.
 * Arguments:     object who       - the user
 *                mapping attr_map - maps attribute names to chosen values
 * Returns:       1 - values are valid
 *                0 - values are invalid and configuration should be exited
 */
public int
craftsman_config_validate_chosen_attributes_hook(object who, mapping attr_map)
{
    return 1;
}

/*
 * Function name: craftsman_desc_order
 * Description:   Redefine this to change how individual orders
 *                are presented
 * Arguments:     mapping attr_map - the attributes for the order
 * Returns:       the formatted order description
 */
public string
craftsman_desc_order(mapping attr_map)
{
    string *attrs, str = "";
    int i;

    attrs = m_indices(attr_map);
    for (i = 0; i < sizeof(attrs); i++)
    {
        str += sprintf("%-13s %s\n", attrs[i] + ":", 
            attr_map[attrs[i]]);
    }

    return str;
}

/*
 * Function name: craftsman_notify_completion_time_hook
 * Description:   Redefine this to change the message given to notify
 *                the user of the order's completion time
 * Arguments:     object who - the user
 *                int t      - the order's completion time
 */
public void
craftsman_notify_completion_time_hook(object who, int t)
{
    string str;

    t -= time();

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

    who->catch_tell("Your order should take " + str + " to complete.\n");
}

/*
 * Function name: craftsman_notify_cost_hook
 * Descriptions:  Redefine this to change the message given
 *                to notify the user of the cost of an item.
 * Arguments:     object who -    the user
 *                mapping attrs - the attributes chosen
 */
public void
craftsman_notify_cost_hook(object who, mapping attrs)
{
    int cost;

    if (cost = craftsman_calc_item_cost(who, 0, attrs))
    {
        who->catch_tell("That will cost " + MONEY_TEXT_SPLIT(cost) + ".\n");
    }
}

/*
 * Function name: craftsman_notify_cancel_hook
 * Description:   Redefine this to change the message given
 *                when instructing the user how to cancel an order.
 * Arguments:     object who - the user
 */
public void
craftsman_notify_cancel_hook(object who)
{
    who->catch_tell("You may \"cancel order\" at any time.\n");
}

public void
craftsman_notify_check_hook(object who)
{
    who->catch_tell("You may \"check order\" to check on the status " +
        "of your order and to retrieve completed orders.\n");
}

/*
 * Function name: creaftsman_notify_hold_time_hook
 * Description:   Redefine this to change the message given to notify
 *                the user of the amount of time that the completed order
 *                will be held.
 * Arguments:     object who - the user
 */
public void
craftsman_notify_hold_time_hook(object who)
{
    if (min_hold_time >= 0)
    {
        who->catch_tell("Your order will only be held for a limited time " +
            "after completed.\n");
    }
}

/*
 * Function name: craftsman_config_completed_hook
 * Description:   Redefine this to change the message given when
 *                the user finishes selecting configuration options.
 * Arguments:     object who       - the user
 *                mapping attr_map - the attributes chosen
 *                int time         - the time at which the order will
 *                                   be finished
 */
public void
craftsman_config_completed_hook(object who, mapping attr_map, int time)
{
    if (m_sizeof(attr_map))
    {
        who->catch_tell("You have selected the following:\n" +
            craftsman_desc_order(attr_map) + "\n");
    }

    craftsman_notify_completion_time_hook(who, time);
    craftsman_notify_cost_hook(who, attr_map);
    craftsman_notify_check_hook(who);
    craftsman_notify_cancel_hook(who);
    craftsman_notify_hold_time_hook(who);
}

/*
 * Function name: craftsman_abort_hook
 * Description:   Redefine this to change the message given when
 *                aborts from an input prompt.
 * Arguments:     object who - the user
 */
public void
craftsman_abort_hook(object who)
{
    who->catch_tell("Aborted.\n");
}

/*
 * Function name: craftsman_cancel_syntax_failure_hook
 * Description:   Redefine this to change the message given when
 *                incorrect arguments are given to the "cancel" command.
 * Arguments:     object who - the user
 *                string str - the arguments given to the "cancel" command.
 * Returns:       0/1
 */
public int 
craftsman_cancel_syntax_failure_hook(object who, string str)
{
    notify_fail("Do you wish to \"cancel order\"?\n");
    return 0;
}

/*
 * Function name: craftsman_cancel_unpurchased_item_hook
 * Description:   Redefine this to change the message given when
 *                a user who has purchased nothing tries to cancel
 *                an order.
 * Arguments:     object who - the user
 * Returns:       0/1
 */
public int
craftsman_cancel_unpurchased_item_hook(object who)
{
    who->catch_tell("You haven't purchased anything.\n");
    return 1;
}

/*
 * Function name: craftsman_cancel_order_hook
 * Description:   Redefine this to change the message given when
 *                an order is cancelled.
 * Arguments:     object who          - the user
 *                mapping order_attrs - The cancelled order's attributes
 */
public void
craftsman_cancel_order_hook(object who, mapping order_attrs)
{
    who->catch_tell("Ok.\n");
}

/*
 * Function name: craftsman_list_orders_hook
 * Description:   Redefine this to change how order lists are presented
 * Arguments:     object who    - the user
 *                mixed *orders - the user's orders
 */
public void
craftsman_list_orders_hook(object who, mixed *orders)
{
    int i;

    for (i = 0; i < sizeof(orders); i++)
    {
        who->catch_tell(sprintf("%2d) %=-70s\n",
            i + 1, craftsman_desc_order(orders[i][0])));
    }
}

public int
craftsman_query_object_present(object ob)
{
    return ((environment(ob) == this_object()) ||
        (environment(ob) == environment(this_object())));
}

/*
 * Function name: craftsman_completed_order_hook
 * Descriptions:  Redefine this to change the message a user
 *                receives when an order is completed.
 * Arguments:     string name     - the user's name
 *                mapping *orders - an array of attribute mappings--one
 *                                  for each completed order.
 */
public void
craftsman_completed_order_hook(string name, mapping *orders)
{
    object who;

    if ((who = find_player(name)) && craftsman_query_object_present(who))
    {
        who->catch_tell("Your order has been completed.\n");
    }
}

/*
 * Function name: craftsman_cancel_menu_hook
 * Description:   Redefine this to change the message given to
 *                prompt the user to select an order to cancel.
 * Arguments:     object who    - the user
 *                mixed *orders - the user's unfinished orders
 */ 
public void
craftsman_cancel_menu_hook(object who, mixed *orders)
{
    craftsman_list_orders_hook(who, orders);
    who->catch_tell("Select an order to cancel (1 - " + 
        sizeof(orders) + " or ~q to exit): ");
}

/*
 * Function name: craftsman_check_syntax_failure_hook
 * Description:   Redefine this to change the message given
 *                when the wrong arguments are given to the "check"
 *                command
 * Arguments:     object who - the user
 *                string str - the argument given to the "check" command
 * Returns:       0/1
 */
public int
craftsman_check_syntax_failure_hook(object who, string str)
{
    notify_fail("Do you wish to \"check order\"?\n");
    return 0;
}

/*
 * Function name: craftsman_check_unpurchased_item_hook
 * Description:   Redefine this to change the message give when
 *                a user who has purchased nothing uses the
 *                "check" command.
 * Arguments:     who - the user
 * Returns:       0/1
 */
public int
craftsman_check_unpurchased_item_hook(object who)
{
    who->catch_tell("You haven't purchased anything.\n");
    return 1;
}

/*
 * Function name: craftsman_check_complete_order_hook
 * Description:   Redefine this to change the message given when
 *                an order is complete.
 * Arguments:     object who               - the user
 *                mapping *complete_orders - the user's orders that
 *                                           are finished.
 */
public void
craftsman_check_complete_order_hook(object who, mapping *complete_orders)
{
    who->catch_tell("Your order is complete.\n");
}

/*
 * Function name: craftsman_check_incomplete_order_hook
 * Description:   Redefine this to change how unfinished orders are
 *                presented.
 * Arguments:     object who               - the user
 *                mixed *incomplete_orders - the unfinished orders
 * Returns:       0/1
 */
public int
craftsman_check_incomplete_order_hook(object who, mixed *incomplete_orders)
{
    int i;

    if (!sizeof(incomplete_orders))
    {
        who->catch_tell("You have no other orders.\n");
        return 1;
    }

    who->catch_tell("You still have " + LANG_WNUM(sizeof(incomplete_orders)) +
        " " + ((sizeof(incomplete_orders) > 1) ? "orders" : "order") +
        " being made:\n");

    craftsman_list_orders_hook(this_player(), incomplete_orders);

    return 1;
}

/*
 * Function name: craftsman_check_cannot_pay_hook
 * Description:   Redefine this to change the message given when
 *                the user cannot pay for an item.
 * Arguments:     object who    - the user
 *                int cost      - the cost of the item in cc
 *                object ob     - the item itself
 *                mapping attrs - the attributes for the item
 */
public void
craftsman_check_cannot_pay_hook(object who, int cost,
                                object ob, mapping attrs)
{
    who->catch_tell("You can't afford it!\n");
}

/*
 * Function name: check_move_player_failed_hook
 * Description:   Redefine this to change the message when the item
 *                could not be moved to the user.
 * Arguments:     object who - the user
 *                object ob  - the item
 */
public void
craftsman_check_move_player_failed_hook(object who, object ob)
{
    who->catch_tell("You can't carry the " + ob->short() + "!\n");
}

/*
 * Function name: craftsman_check_move_env_failed_hook
 * Description:   Redefine this to change the message when the item
 *                could not be moved to the user AND it could not be
 *                moved to the user's environment.
 * Arguments:     object who - the user
 *                object ob  - the item
 */
public void
craftsman_check_move_env_failed_hook(object who, object ob)
{
    who->catch_tell("You can't carry the " + ob->short() + "!\n");
}

/*
 * Function name: craftsman_check_receive_order_hook
 * Description:   Redefine this to change the message when the user
 *                receives his item.
 * Arguments:     object who - the user
 *                object ob  - the item
 */
public void
craftsman_check_receive_order_hook(object who, object ob)
{
    who->catch_tell("You receive your " + ob->short() + ".\n");
}

public mapping
query_purchased_items() { return m_purchased_items + ([]); }

public mapping
query_attributes() { return attributes + ([]); }

/*
 * Function name: craftsman_set_attribute
 * Description:   Called to set the desired value for each attribute
 *                depending on the user's input.
 * Arguments:     object who       - the user
 *                string *attrs    - the attributes that remain unset.
 *                mapping attr_map - a mapping that maps set attribute names to
 *                                   the values specified by the user
 *                string value     - The value specified for the current
 *                                   attribute (attrs[0])
 * Returns:       1/0 - attribute set/not set
 */
public int
craftsman_set_attribute(object who, string *attrs, mapping attr_map, 
    string value)
{
    string attr = attrs[0];
    int valid;

    if (value == "~q")
    {
        craftsman_abort_hook(who);
        return 0;
    }

    /* Check if the input value is invalid for some other reason */
    valid = craftsman_config_validate_chosen_attribute_hook(who, attr, value, 
        attr_map);

    if (valid < 0)
    {
        /* Value is invalid, and we should stop */
        return 0;
    }
    
    if (valid == 0)
    {
        /* Value is invalid, and we should try again */
        craftsman_config_attributes(attrs, who, attr_map);
        return 0;
    }

    /* Add the attribute and value to the mapping */        
    attr_map[attr] = value;

    /* Remove the attribute from the list of attributes which need to be set */
    attrs = attrs[1..];
    
    if (sizeof(attrs))
    {
        /* There are still attributes that are unset, so get the next */
        craftsman_config_attributes(attrs, who, attr_map);
        return 1;
    }

    /* There are no more attributes to be set, so finish up */
    craftsman_completed_config(who, attr_map);
    return 1;
}

/*
 * Function name: craftsman_config_attributes
 * Description:   Prompt the user to input a value for an attribute.
 * Arguments:     string *attrs    - the attributes that remain unset
 *                object who       - the user
 *                mapping attr_map - a mapping that maps set attribute names
 *                                   to the values specified by the user
 */
public void
craftsman_config_attributes(string *attrs, object who, mapping attr_map)
{
    if (sizeof(attrs))
    {
        /* The first attribute in the array is the one we will set */
        string attr = attrs[0];

        /* prompt the user for input */
	craftsman_config_prompt_attribute_hook(who, attr, attributes[attr]);

	set_this_player(who);

        /* catch the player's input and set the attribute */
	input_to(&craftsman_set_attribute(who, attrs, attr_map));
    }
}

public int
craftsman_query_completion_time(object who, mapping attr_map)
{
    return time() + time_to_complete;
}

/*
 * Function name: craftsman_completed_config
 * Description:   Called when the user has finished selecting attributes,
 *                this function adds the item to the list of items being
 *                created.
 * Arguments:     object who       - the user
 *                mapping attr_map - a mapping that maps set attribute names
 *                                   to the values specified by the user
 * Returns:       1/0 - configuration successful/unsuccessful
 */
public int
craftsman_completed_config(object who, mapping attr_map)
{
    string name = who->query_real_name();
    mixed *already_purchased = m_purchased_items[name];
    int t;

    /* Validate the chosen values */
    if (!craftsman_config_validate_chosen_attributes_hook(who, attr_map))
    {
        return 0;
    }

    /* Add the order */

    t = craftsman_query_completion_time(who, attr_map);

    if (!pointerp(already_purchased))
    {
        already_purchased  = ({ ({ attr_map, t }) });
    }
    else
    {
        already_purchased += ({ ({ attr_map, t }) });
    }

    m_purchased_items[name] = already_purchased;

    craftsman_config_completed_hook(who, attr_map, t);

    /* Start creation */

    if (!next_completion_time || (t < next_completion_time))
    {
        if (completion_alarm)
        {
            remove_alarm(completion_alarm);
        }

        next_completion_time = t;
        completion_alarm = set_alarm(itof(t - time()), 0.0, 
            &craftsman_completed_order(name));
    }

    /* This is a good point to clean up old completed orders */
    craftsman_clean_completed_orders();

    return 1;
}

/* 
 * Function name: craftsman_calc_item_cost
 * Descriptions:  Give the cost in cc for an item.  By default,
 *                this simply returns the value given in
 *                set_item_cost(), but it can be redefined to
 *                dynamically calculate the cost for an item.
 * Arguments:     object who       - the user
 *                object ob        - the item itself.  If the item has
 *                                   not been completed this will be 0.
 *                mapping attr_map - the attributes
 * Returns:       int - the cost of the item in copper
 */
public int
craftsman_calc_item_cost(object who, object ob, mapping attr_map)
{
    return item_cost;
}

/*
 * Function name: craftsman_completed_order
 * Description:   Called when creation of an item is complete, this function
 *                adds the item to the list of completed items and starts
 *                creation of the next item.
 * Arguments:     string name - the name of the user for whom the item is
 *                              being made.
 */
public void
craftsman_completed_order(string name)
{
    object who, env;
    mapping *complete = ({}), *already_completed;
    mixed  *incomplete = ({ }), *orders;
    int i, t;

    /* Separate the complete orders from the incomplete orders */
    t = time();
    orders = m_purchased_items[name];
    for (i = 0; i < sizeof(orders); i++)
    {
        if (orders[i][1] <= t)
        {
            complete += ({ orders[i] });
        }
        else
        {
            incomplete += ({ orders[i] });
        }
    }

    if (sizeof(incomplete))
    {
        m_purchased_items[name] = incomplete;
    }
    else
    {
        m_purchased_items = m_delete(m_purchased_items, name);
    }

    /* Add the newly completed orders to the completed orders mapping */

    if (!pointerp(already_completed = m_completed_orders[name]))
    {
        already_completed = ({});
    }

    m_completed_orders[name] = already_completed + complete;

    craftsman_completed_order_hook(name, complete);

    /* Start the alarm for the next item */
    craftsman_reset_completion_time();
}
   
/*
 * Function name: purchase
 * Description:   the "purchase" command.  Starts off item configuration.
 * Arguments:     string str - argument string to the "purchase" command
 * Returns:       1/0 - success/failure
 */ 
public int
craftsman_purchase(string str)
{
    mixed *orders;
    int i, num_orders;

    if (member_array(str, item_names) < 0)
    {
        return craftsman_purchase_syntax_failure_hook(this_player(), str);
    }

    if (max_total_orders >= 0)
    {
        orders = m_values(m_purchased_items);
        for (i = 0; i < sizeof(orders); i++)
	{
            num_orders += sizeof(orders[i]);
	}

        if (num_orders >= max_total_orders)
	{
            return craftsman_purchase_exceeded_max_total_orders_hook(
                this_player(), str);
	}
    }

    if ((max_user_orders >= 0) && 
        (sizeof(m_purchased_items[this_player()->query_real_name()]) >= 
        max_user_orders))
    {
        return craftsman_purchase_exceeded_max_user_orders_hook(this_player(),
            str);
    }

    craftsman_purchase_hook(this_player(), str);

    craftsman_config_attributes(m_indices(attributes), this_player(), ([]));
    return 1;
}

/*
 * Function name: reset_completion_time
 * Description:   Start a new alarm to signal the completion of
 *                the next item.
 */
public void
craftsman_reset_completion_time()
{
    string *names, name;
    int i, j;
    mixed *orders;

    if (get_alarm(completion_alarm))
    {
        remove_alarm(completion_alarm);
    }

    next_completion_time = 0;

    names = m_indices(m_purchased_items);
    for (i = 0; i < sizeof(names); i++)
    {
        orders = m_purchased_items[names[i]];
        for (j = 0; j < sizeof(orders); j++)
        {
            if (!next_completion_time || 
                (orders[j][1] < next_completion_time))
            {
                next_completion_time = orders[j][1];
                name = names[i];
            }
        }
    }

    if (next_completion_time)
    {
        set_alarm(itof(next_completion_time - time()),
            0.0, &craftsman_completed_order(name));
    }
}

/*
 * Function name: cancel_order
 * Description:   This function cancels the given order
 * Arguments:     object who      - the user for whom to cancel the order
 *                int which_order - which of the user's orders to cancel.
 *                                  this should be the order's index in
 *                                  in the appropriate array value in the
 *                                  m_purchased_items mapping.
 */
public void
craftsman_cancel_order(object who, int which_order)
{
    string name = who->query_real_name();
    mixed *orders = m_purchased_items[name], *order_to_cancel;

    order_to_cancel = orders[which_order];
    orders = exclude_array(orders, which_order, which_order);

    if (sizeof(orders))
    {
        m_purchased_items[name] = orders;
    }
    else
    {
        m_purchased_items = m_delete(m_purchased_items, name);
    }

    if (order_to_cancel[1] == next_completion_time)
    {
        craftsman_reset_completion_time();
    }

    craftsman_cancel_order_hook(who, order_to_cancel[0]);
}

/*
 * Function name: cancel_order_input
 * Description:   Accept user input and cancel the specified order
 * Arguments:     object who - the user
 *                string str - the order number to cancel
 * Returns:       1/0 - order cancelled/not cancelled
 */
public int
cancel_order_input(object who, string str)
{
    int i;
    string name;
    mixed *orders;

    if (str == "~q")
    {
        craftsman_abort_hook(who);
        return 0;
    }

    name = who->query_real_name();
    orders = m_purchased_items[name];
    if (!sscanf(str, "%d", i) || (i < 1) || (i > sizeof(orders)))
    {
        craftsman_cancel_menu_hook(who, orders);
        set_this_player(who);
        input_to(&cancel_order_input(who));
        return 0;
    }
    
    craftsman_cancel_order(who, i - 1);
    return 1;
}

/*
 * Function name: craftsman_cancel
 * Description:   The "cancel" command.  This function cancels the
 *                user's order or prompts the user to select an order
 *                to cancil if he has more than one being made.
 * Arguments:     string str - the arguments to the "cancel" command
 * Returns:       1/0 - success/failure
 */
public int
craftsman_cancel(string str)
{
    mixed *orders;
    string name;

    if (str != "order")
    {
        return craftsman_cancel_syntax_failure_hook(this_player(), str);
    }

    name = this_player()->query_real_name();

    if (!sizeof(orders = m_purchased_items[name]))
    {
        return craftsman_cancel_unpurchased_item_hook(this_player());
    }

    if (sizeof(orders) == 1)
    {
        craftsman_cancel_order(this_player(), 0);
        return 1;
    } 

    craftsman_cancel_menu_hook(this_player(), orders);
    input_to(&cancel_order_input(this_player()));
    return 1;
}

/*
 * Function name: craftsman_configure_item
 * Description:   Redefine this to configure your final item
 * Arguments:     object who    - the user
 *                object item   - the item to be configured
 *                mapping attrs - a mapping that maps set attribute names to
 *                                the values specified by the user.
 */
void craftsman_configure_item(object who, object item, mapping attrs)
{
}

/*
 * Function name: craftsman_clone_item
 * Description:   clone the item to be configured.
 *                items from a variety of files, 
 * Arguments:     object who    - the user
 *                mapping attrs - a mapping that maps set attribute names to
 *                                the values specified by the user.
 * Returns:       An instance of the item to be sold.
 */
public object
craftsman_clone_item(object who, mapping attrs)
{
    setuid();
    seteuid(getuid());
    return clone_object(clone_file);
}

/*
 * Function name: craftsman_move_item
 * Description:   move the purchased item to the user
 * Arguments:     object ob  - the item to be sold
 *                object who - the user
 * Returns:       1 - object successfully moved to player or player's
 *                    environment. 
 *                0 - object could not be moved to player or player's
 *                    environment.
 */
public int
craftsman_move_item(object ob, object who)
{
    if (ob->move(who))
    {
        if (ob->move(environment(who)))
        {
            craftsman_check_move_env_failed_hook(who, ob);
            ob->remove_object();
            return 0;
        }

        craftsman_check_move_player_failed_hook(who, ob);
        return 1;
    }

    return 1;
}  

/* 
 * Function name: craftsman_charge_for_item
 * Description:   Charge for the ordered item
 * Arguments:     object ob      - the item to be sold
 *                object who     - the user
 *                mapping attris - the chosen attributes for the item
 * Returns:       1/0 - item was paid for/was not paid for
 */ 
public int
charge_for_item(object ob, object who, mapping attrs)
{
    int cost = craftsman_calc_item_cost(who, ob, attrs);
    if (!MONEY_ADD(who, -cost))
    {
        craftsman_check_cannot_pay_hook(who, cost, ob, attrs);
        ob->remove_object();
        return 0;
    }
 
    return 1;
}
      
/*
 * Function name: craftsman_present_order
 * Description:   Clone a fresh item, configure it, and give it to the user
 * Arguments:     object who    - the user
 *                mapping attrs - a mapping that maps set attribute names to
 *                                the values specified by the user.
 * Returns:       1 - purchase was resolved and can be removed
 *                0 - purchase was not resolved
 */
public int
craftsman_present_order(object who, mapping attrs) 
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = craftsman_clone_item(who, attrs);
    craftsman_configure_item(who, ob, attrs);

    if (!charge_for_item(ob, who, attrs))
    {
        return 0;
    }

    if (!craftsman_move_item(ob, who))
    {
        return 0;
    }

    craftsman_check_receive_order_hook(who, ob);
    return 1;
}

/*
 * Function name: craftsman_check
 * Description:   The "check" command.  Tell the user about the
 *                status of his orders.  If any are complete, let him
 *                have them.
 * Arguments:     string str - the arguments give to the "check" command
 * Returns:       1/0 - success/failure
 */
int craftsman_check(string str)
{
    string name;
    mixed *incomplete_orders;
    mapping *complete_orders;
    int i;

    if (str != "order")
    {
        return craftsman_check_syntax_failure_hook(this_player(), str);
    } 

    name = this_player()->query_real_name();
   
    if (!sizeof(incomplete_orders = m_purchased_items[name]) &&
        !sizeof(complete_orders = m_completed_orders[name]))    
    {
        return craftsman_check_unpurchased_item_hook(this_player());
    }

    if (sizeof(complete_orders))
    {
        craftsman_check_complete_order_hook(this_player(), complete_orders);

    	complete_orders = filter(complete_orders, 
    	    not @ &craftsman_present_order(this_player()) @ &operator([])(,0));
       
    	if (!sizeof(complete_orders))
    	{
    	    m_completed_orders = m_delete(m_completed_orders, name);
    	}
    	else
    	{
    	    m_completed_orders[name] = complete_orders;
        }

        return 1;
    }

    return craftsman_check_incomplete_order_hook(this_player(), 
        incomplete_orders);
}

/*
 * Function name: craftsman_clean_completed_orders
 * Description:   Remove old orders that have not been picked up
 */
public void
craftsman_clean_completed_orders()
{
    int i, j;
    string *names;
    mixed *orders;

    if (min_hold_time < 0)
    {
        return;
    }

    names = m_indices(m_completed_orders);
    for (i = 0; i < sizeof(names); i++)
    {
        orders = m_completed_orders[names[i]];
        orders = filter(orders, 
            &operator(>)(, time() - min_hold_time) @ &operator([])(, 1));
   
        if (!sizeof(orders))
	{
            m_completed_orders = m_delete(m_completed_orders, names[i]);
	}
        else
	{
            m_completed_orders[names[i]] = orders;
	}
    }
}
/*
 * Function name: craftsman_init
 * Description:   adds the craftsman's commands.  Call this from the
 *                init()/init_living().
 */
public void
craftsman_init()
{
    add_action(craftsman_purchase, "purchase");
    add_action(craftsman_purchase, "buy");
    add_action(craftsman_purchase, "order");
    add_action(craftsman_cancel,   "cancel");
    add_action(craftsman_check,    "check");
}

/*
 * Function name: craftsman_add_attribute
 * Description:   add a configuration option.  The user will be prompted
 *                to select a value from the given values.
 * Arguments:     string attribute     - the name of the attribute
 *                string *valid_values - possible selections for the attribute
 * Returns:       1/0 - success/failure
 */
public int
craftsman_add_attribute(string attribute, string *valid_values)
{
    attributes[attribute] = valid_values;
    return 1;
}

/*
 * Function name: craftsman_set_sold_item_names
 * Description:   give the names of the item which the craftsman sells.
 *                These will be used to determine correct syntax for the
 *                "purchase" command.
 * Arguments:     string *names - the names to use
 * Returns:       1/0 - success/failure
 */
public int
craftsman_set_sold_item_names(string *names)
{
    item_names = names + ({});
    return 1;
}    

public string *
query_sold_item_names() { return item_names + ({}); }

/*
 * Function name: craftsman_set_time_to_complete
 * Description:   give the amount of time in seconds it takes to create
 *                an item.
 * Arguments:     int t - the time in seconds
 * Returns:       1/0 - success/failure
 */
public int
craftsman_set_time_to_complete(int t)
{
    time_to_complete = t;
    return 1;
}

public int
query_time_to_complete() { return time_to_complete; }

/*
 * Function name: craftsman_set_item_file
 * Description:   set the pathname to the item which will be created
 * Arguments:     string f - the filename
 * Returns:       1/0 - success/failure
 */
public int
craftsman_set_item_file(string f)
{
    clone_file = f;
    return 1;
}

public string
query_item_file() { return clone_file; }

/*
 * Function name: craftsman_set_item_cost
 * Description:   Set the cost of an item
 * Arguments:     int i - the cost in copper coins
 * Returns:       1/0 - success/failure
 */
public int
craftsman_set_item_cost(int i)
{
    item_cost = i;
    return 1;
}

public int
query_item_cost() { return item_cost; }

/*
 * Function name: craftsman_set_max_total_orders
 * Description:   Set the max number of orders that can be active at once
 * Arguments:     int i - the max number of orders
 * Returns:       1/0 - success/failure
 */
public int
craftsman_set_max_total_orders(int i)
{
    max_total_orders = i;
    return 1;
}

/*
 * Function name: craftsman_set_max_user_orders
 * Description:   Set the max number of orders that can be active at once for
 *                a single order.
 * Arguments:     int i - the max number of orders
 * Returns:       1/0 - success/failure
 */
public int
craftsman_set_max_user_orders(int i)
{
    max_user_orders = i;
    return 1;
} 

/*
 * Function name: craftsman_set_hold_time
 * Description:   Set the minimum amount of time that the craftsman will hold a
 *                completed order.  If set to a negative value, orders will
 *                be held indefinitely.
 * Arguments:     int i - the time in seconds
 * Returns:       1/0 - success/failure
 */
public int
craftsman_set_hold_time(int i)
{
    min_hold_time = i;
    return 1;
}

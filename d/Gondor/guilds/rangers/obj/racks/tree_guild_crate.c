/*
 * Modification log:
 *   October 2010 - Added saving rack functionality (Gorboth)
 */

inherit "/std/container";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <wa_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>
#include <config.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

int rack_type;


public void
create_rack()
{
}


public void
create_container()
{
    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 2000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);
    
    create_rack();
    
    if (!IS_CLONE)
    {
        return;
    }

    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());
}


/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    ::describe_contents(for_obj, obarr);
    
    for_obj->catch_tell("\nDo <list> to show all items in the rack, " +
        "or <list [category]> to show specific items.\n");
}


/*
 * Function name: is_armour
 * Description  : Armour filter
 * Arguments    : ob - the object to test
 * Returns      : 0 when not an armour, 1 when it is
 */
int is_armour(object ob)
{
    return IS_ARMOUR_OBJECT(ob);
}


/*
 * Function name: is_weapon
 * Description  : weapon filter
 * Arguments    : ob - the object to test
 * Returns      : 0 when not an weapon, 1 when it is
 */
int is_weapon(object ob)
{
    return IS_WEAPON_OBJECT(ob);
}


/*
 * Function name: figure_category
 * Description:   Figure out which category ob belongs to
 * Arguments:     ob - the object to describe
 * Returns:       The category - weapon type, armour type or "General"
 */
public string
query_category(object ob)
{
    int val;
    string short_descr;

//    if (ob->check_weapon())
    if (IS_WEAPON_OBJECT(ob))
        switch(ob->query_wt())
        {
            case W_SWORD: return "Sword";
            case W_AXE: return "Axe";
            case W_KNIFE: return "Knife";
            case W_CLUB: return "Club";
            case W_POLEARM: return "Polearm";
            case W_MISSILE: return "Missile";
            case W_JAVELIN: return "Javelin";
            default: return "Weapon";
        }
        if(ob->function_exists("create_arrow", ob))
            return "Arrow";

//    if (ob->check_armour())
    if (IS_ARMOUR_OBJECT(ob))
    {
        switch(ob->query_at())
        {
            case A_ARMS: return "Arms";
            case A_L_ARM: return "Arms";
            case A_R_ARM: return "Arms";
            case W_LEFT: return "Arms";
            case W_RIGHT: return "Arms";
            case A_BACK: return "Back";
            case A_BODY: return "Torso";
            case A_TORSO: return "Torso";
            case A_FEET: return "Feet";
            case A_L_FOOT: return "Feet";
            case A_R_FOOT: return "Feet";
            case A_EARS: return "Ears";
            case A_L_EAR: return "Ears";
            case A_R_EAR: return "Ears";
            case A_FINGERS: return "Ring";
            case A_ANY_FINGER: return "Ring";
            case A_L_FINGER: return "Ring";
            case A_R_FINGER: return "Ring";
            case A_HANDS: return "Hands";
            case A_L_HAND: return "Hands";
            case A_R_HAND: return "Hands";
            case A_HEAD: return "Helmet";
            case A_LEGS: return "Legs";
            case A_NECK: return "Neck";
            case A_ROBE: return "Robe";
            case A_SHIELD: return "Shield";
            case A_SHOULDERS: "Shoulders";
            case A_L_SHOULDER: "Shoulders";
            case A_R_SHOULDER: "Shoulders";
            case A_WRISTS: return "Wrists";
            case A_L_WRIST: return "Wrists";
            case A_R_WRIST: return "Wrists";
            case A_WAIST: return "Waist";
            case A_L_HIP: return "Hips";
            case A_L_HIP: return "Hips";
            case A_L_ANKLE: return "Ankles";
            case A_R_ANKLE: return "Ankles";

        }
        return "Armour";
    }

    if (IS_LEFTOVER_OBJECT(ob))
        return "Body Part";
    else if(IS_HERB_OBJECT(ob))
        return "Herb";
    else if(IS_DRINK_OBJECT(ob))
        return "Drink";
    else if(IS_FOOD_OBJECT(ob))
        return "Food";
    else if(IS_COINS_OBJECT(ob))
        return "Money";
    else if (ob->query_gem())
        return "Gem";

    return "General";

}


/*
 * Function name: compare_object_arrays
 * Description:   Sort the list of objects through sort_array
 * Arguments:     a, b - arrays of identical objects
 * Returns:       1 if a after b, else -1
 */
public int
compare_object_arrays(object *a, object *b)
{
    if (b[0]->check_weapon() && !a[0]->check_weapon()) return 1;
    if (!b[0]->check_weapon() && a[0]->check_weapon()) return -1;
    if (b[0]->check_armour() && !a[0]->check_armour()) return 1;
    if (!b[0]->check_armour() && a[0]->check_armour()) return -1;
    if (query_category(a[0]) < query_category(b[0])) return -1;
    if (query_category(a[0]) > query_category(b[0])) return 1;
    if (a[0]->short() < b[0]->short()) return -1;
    return 1;
}


/*
 * Function name: sort_inventory
 * Description  : Goes through the inventory and sort the items based on 
 *              : category.
 * Returns      : an array with items
 */
mixed *sort_inventory(object *oblist)
{
    oblist = filter(oblist, objectp);
    oblist = FILTER_DEAD(oblist);
    oblist = unique_array(oblist, "short", 0);
    oblist = sort_array(oblist, "compare_object_arrays", this_object());

    return oblist;
}


/*
 * Function name: list_cmd
 * Description:   List the equipment in the rack
 * Arguments:     args - command line arguments
 * Returns:       0 on failure, 1 on success
 */
int list_cmd(string args)
{
    object *obs;
    mixed  *sorted;
    int     i;
    string  result, prev_category, category;

    // Find all objects in our inventory
    obs = all_inventory(this_object());
    obs = filter(obs, &->check_seen(this_player()));

    // Default argument is 'all'
    if(!stringp(args) || !strlen(args))
        args = "all";

    // Add filtering
    switch(args)
    {
        case "all":
        {
            // No filtering to do here
            break;
        }

        case "general":
        {
            obs = filter(obs, not @ is_weapon);
            obs = filter(obs, not @ is_armour);
            break;
        }

        // Armour listings
        case "armour":
        case "armours":
        {
            obs = filter(obs, is_armour);
            break;
        }

        case "body":
        {
            obs = filter(obs, &operator(&)(A_BODY) @ &->query_at()) + 
                filter(obs, &operator(&)(A_BACK) @ &->query_at());
            break;
        }

        case "shield":
        case "shields":
        {
            obs = filter(obs, &operator(==)(A_SHIELD) @ &->query_at());
            break;
        }

        case "glove":
        case "gloves":
        {
            obs = filter(obs, &operator(&)(A_HANDS) @ &->query_at());
            break;
        }

        case "helm":
        case "helms":
        case "helmet":
        case "helmets":
        {
            obs = filter(obs, &operator(==)(A_HEAD) @ &->query_at());
            break;
        }

        case "ring":
        case "rings":
        {
            obs = filter(obs, &operator(&)(A_FINGERS) @ &->query_at());
            break;
        }

        case "boot":
        case "boots":
        {
            obs = filter(obs, &operator(&)(A_FEET) @ &->query_at());
            break;
        }

        case "leg":
        case "legs":
        {
            obs = filter(obs, &operator(&)(A_LEGS) @ &->query_at());
            break;
        }

        case "arm":
        case "arms":
        {
            obs = filter(obs, &operator(&)(A_ARMS) @ &->query_at());
            break;
        }

        // Weapon listings
        case "weapon":
        case "weapons":
        {
            obs = filter(obs, is_weapon);
            break;
        }

        case "sword":
        case "swords":
        {
            obs = filter(obs, is_weapon);
            obs = filter(obs, &operator(==)(W_SWORD) @ &->query_wt());
            break;
        }

        case "axe":
        case "axes":
        {
            obs = filter(obs, &operator(==)(W_AXE) @ &->query_wt());
            break;
        }

        case "knife":
        case "knives":
        {
            obs = filter(obs, &operator(==)(W_KNIFE) @ &->query_wt());
            break;       
        }

        case "club":
        case "clubs":
        {
            obs = filter(obs, &operator(==)(W_CLUB) @ &->query_wt());
            break;       
        }

        case "polearm":
        case "polearms":
        {
            obs = filter(obs, &operator(==)(W_POLEARM) @ &->query_wt());
            break;       
        }

        case "missile":
        case "missiles":
        {
            obs = filter(obs, &operator(==)(W_MISSILE) @ &->query_wt());
            break;       
        }

        case "javelin":
        case "javelins":
        {
            obs = filter(obs, &operator(==)(W_JAVELIN) @ &->query_wt());
            break;       
        }

        // Fallback
        default:
        {
            // Unknown type
            notify_fail("You cannot list the '" + args + "' equipment, " +
                "it's not a known type.\n");
            return 0;
        }
    }

    // See if we have any equipment
    if(!sizeof(obs))
    {
        if(args == "all")
        {
            write("The equipment rack is completely empty.\n");
        }
        else
        {
            write("The equipment rack does not contain any '" + 
                args + "'.\n");
        }
        return 1;
    }

    // List the equipment
    sorted = sort_inventory(obs);
    result = "The rack contains:\n";
    result += "+---------------------------------------------------------+------------+\n";
    result += "| Qty. |                   Name                           |  Category  |\n",
    result += "+---------------------------------------------------------+------------+\n";
    for(i=0;i<sizeof(sorted);i++)
    {
        category = query_category(sorted[i][0]);
        if(category != prev_category)
        {
            prev_category = category;
            result += "|      |                                                  |            |\n";
        }

        result += sprintf("| %4d | %-48s | %-10s |\n",
            sizeof(sorted[i]), extract(sorted[i][0]->short(), 0, 49), category);
    }
//    result += "|      |                                                  |          |\n";
    result += "+---------------------------------------------------------+------------+\n";

    this_player()->more(result, 0);
    return 1;
}


/*
 * Function name: filter_allow_rack
 * Description  : Filter out any items that cannot be dropped, given etc
 * Arguments    : ob - the object to check
 * Returns      : 1 to keep it, 0 to not
 */
int filter_allow_rack(object ob, int keepcheck = 0)
{
    // Check for the various properties
    if(ob->query_prop(OBJ_M_NO_DROP)) return 0;
    if(ob->query_prop(OBJ_M_NO_GIVE)) return 0;
    if(ob->query_prop(OBJ_I_BROKEN)) return 0;
    if(ob->query_prop(OBJ_M_NO_INS)) return 0;
    if(ob->query_worn()) return 0;
    if(ob->query_wielded()) return 0;
    if(ob->query_auto_load()) return 0;
    if(keepcheck) if(ob->query_keep()) return 0;

    return 1;
}


/*
 * Function name: query_nosort_message
 * Description  : Determine what message to write on failure
 * Arguments    : obs - the objects to check
 * Returns      : the message
 */
string query_nosort_message(object *obs)
{
    mixed ret;

    // For multiple objects it's easy
    if(sizeof(obs) > 1)
        return "You cannot sort " + COMPOSITE_DEAD(obs) + ".\n";

    // Check for no drop
    ret = obs[0]->query_prop(OBJ_M_NO_DROP);
    if(ret)
    {
        if(stringp(ret)) return ret;
        return "The " + obs[0]->short() + " cannot be dropped.\n";
    }

    // Check for no give
    ret = obs[0]->query_prop(OBJ_M_NO_GIVE);
    if(ret)
    {
        if(stringp(ret)) return ret;
        return "The " + obs[0]->short() + " cannot be given away.\n";
    }

    // Check for no insert
    ret = obs[0]->query_prop(OBJ_M_NO_INS);
    if(ret)
    {
        if(stringp(ret)) return ret;
        return "The " + obs[0]->short() + " cannot be placed inside " +
            "the rack.\n";
    }

    if(obs[0]->query_worn() || obs[0]->query_wielded())
    {
        return "You are using the " + obs[0]->short() + ".\n";
    }

    // Check for broken items
    if(obs[0]->query_prop(OBJ_I_BROKEN))
    {
         return "The " + obs[0]->short() + " is broken.\n";
    }

    if(obs[0]->query_keep())
    {
        return "The " + obs[0]->short() + " is keep protected, 'unkeep' " +
            "it first.\n";
    }

    return "Unable to sort " + obs[0]->query_short() + ".\n";
}

object *filter_rackable_objects(object *obs) {
    object *valid_items = ({ });
    valid_items += filter(obs, is_weapon);
    valid_items += filter(obs, is_armour);    
    return valid_items;
}


/*
 * Function name: sort_cmd
 * Description  : Command which allows players to sort equipment quickly
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
int sort_cmd(string args)
{
    object  *selected_obs;
    object  *useable_obs;
    object  *rack_obs;
    mixed   parse_result;
    int     keepcheck;

    // Force arguments
    if(!stringp(args) || !strlen(args))
    {
        notify_fail("Sort what?\n", 0);
        return 0;
    }
    
    // If the arguments starts with !, the keepcheck will be skipped
    if(args[0] == '!')
    {
        // Drop the keepcheck and fix the args
        keepcheck = 0;
        args = args[1..];
    }
    else
    {
        keepcheck = 1;
    }

    // What if they want to sort all
    if((args == "all") || (args == "everything"))
    {
        selected_obs = all_inventory(this_player());
    }
    else
    {
        // Find the intended items
        if(!parse_command(args, this_player(), "%i", selected_obs))
        {
            notify_fail("You don't carry any '" + args + "' to sort.\n");
            return 0;
        }

        selected_obs = NORMAL_ACCESS(selected_obs, 0, 0);
    }

    // See if we have anything
    if(!sizeof(selected_obs))
    {
        notify_fail("You don't have anything to sort.\n");
        return 0;
    }

    // Filter out unwanted objects
    useable_obs = filter(selected_obs, &filter_allow_rack(, keepcheck));
    if(!sizeof(useable_obs))
    {
        this_player()->catch_msg(query_nosort_message(selected_obs));
        return 1;
    }

    // Make sure the items belongs in the rack'
    rack_obs = filter_rackable_objects(useable_obs);

    // Do another check
    if(!sizeof(rack_obs))
    {
        this_player()->catch_msg("You cannot sort " + 
            COMPOSITE_DEAD(useable_obs) + " into this rack.\n");
        return 1;
    }

    // Do the actual racking
    this_player()->catch_msg("You place " + COMPOSITE_DEAD(rack_obs) + 
        " into the equipment rack.\n");
    say(QCTNAME(this_player()) + " places " + COMPOSITE_DEAD(rack_obs) + 
        " into the equipment rack.\n");
    rack_obs->move(this_object());
    return 1;
}


/*
 * Function name: init
 * Description  : Add commands
 */
void init()
{
    ::init();
    add_action(list_cmd,    "list");
    add_action(sort_cmd,    "sort");
}


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (from == this_object())
    {
        return;
    }
    
    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);
}


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
}

/*
 * /d/Faerun/guilds/fire_knives/obj/member_armor_chest.c
 *
 * Nerull 2018
 */

#include <filter_funs.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>
#include "../guild.h"

inherit FIREKNIVES_OBJ_DIR + "guild_rack";

int rack_type;

public void
create_rack()
{
    set_name("chest");
	
	
    set_adj("large");
    add_adj("oak");
    
    set_short("large oak chest");
    set_long("A very large and deep chest made from laquered brown "
    +"oak with gold fittings. The lid is inlaid with carvings of "
    +"the mark of the fireknives in the middle with a big adamantium "
    +"lock to connect to the lower part of the chest. Use 'listchest' "
    +"to list the content.\n");

    set_no_show_composite(0);

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 2000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

    rack_type = 0;
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
 * Function name: set_rack_type
 * Description  : Set the type of rack
 * Arguments    : type - the type of the rack (0 - saving items, 1 - non
 *              :   saving items without mark, 2 - non saving with mark)
 */
void set_rack_type(int type)
{
    rack_type = type;
}


/*
 * Function name: is_recoverable
 * Description  : See if we can recover this item
 * Arguments    : ob - the item to check
 * Returns      : 0 when unrecoverable, 1 when it is
 */
int is_recoverable(object ob)
{
    if(ob->query_recover() && !ob->may_not_recover())
        return 1;

    return 0;
}


object *filter_rackable_objects(object *obs) 
{
    object *rack_obs = ::filter_rackable_objects(obs);
    
    switch(rack_type)
    {
        // Saving items
        case 0:
        {
            rack_obs = filter(rack_obs, is_recoverable);
            break;
        }
    }
    
    return rack_obs;
}


/*
 * Function name: init
 * Description  : Add commands
 */
void init()
{
    ::init();
    add_action(list_cmd,    "listchest");
    //add_action(sort_cmd,    "sort");
}
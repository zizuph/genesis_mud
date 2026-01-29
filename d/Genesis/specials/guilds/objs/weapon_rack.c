/* 
 * General Weapon Rack for the Guilds of Genesis
 *  
 * This weapon rack is based on the describable rack system. It customizes
 * the messages as it relates to weapons.
 *
 * Created by Petros, July 2009
 */

inherit "/d/Genesis/specials/guilds/objs/describable_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

void
create_rack()
{
    remove_name("rack");
    set_name("chest");
    add_name("weapons chest");
    set_adj("weapons");
    add_adj("large");
    set_short("large weapons chest");
    set_long("This is a standard weapons chest to be used in guilds.\n"); 
}

/*
 * Function:    valid_item_for_rack
 * Description: Mask this to indicate what type of items can actually
 *              enter the racks.
 */
public int
valid_item_for_rack(object obj)
{
    if (obj->query_prop(OBJ_I_BROKEN))
    {
        write("Why would you want to put broken things in the " + short() 
            + "?\n");
        return 0;
    }

    if (!(obj->check_weapon()))
    {
        write("The " + obj->short() + " will not fit in the " + short() 
            + ".\n");
        return 0;
    }
    
    return 1;
}

/*
 * Function:    format_list_item_row
 * Description: Given the item information, it prints out a formatted
 *              row including whatever information it needs for the
 *              columns. It should match the number of columns that are
 *              printed in format_header_and_footer.
 *              The last argument "obj" can be used to glean more info
 *              to be printed.
 */
public string
format_list_item_row(string short_desc, int count, int recoverable, object obj)
{
    string row_content, prepend_text, weapon_type;
    
    if (recoverable == 1)
    {
        prepend_text = "+ ";
    }
    else
    {
        prepend_text = "  ";
    }
    
    switch (obj->query_wt())
    {
    case W_SWORD:
        weapon_type = "sword";
        break;
    case W_POLEARM:
        weapon_type = "polearm";
        break;
    case W_AXE:
        weapon_type = "axe";
        break;
    case W_KNIFE:
        weapon_type = "knife";
        break;
    case W_CLUB:
        weapon_type = "club";
        break;
    case W_MISSILE:
        weapon_type = "missile";
        break;
    case W_JAVELIN:
        weapon_type = "javelin";
        break;
    default:        
        weapon_type = "unknown";
    }
    
    return sprintf("|  %-50s | %|10s | %5d  |\n", 
                            prepend_text + short_desc, 
                            weapon_type, count);
}

/*
 * Function:    format_header_and_footer
 * Description: This prints the header and the footer that surrounds
 *              the item rows. It should match the number of columns that
 *              are printed in format_list_item_row.
 */
public string
format_header_and_footer(string contents)
{
    return  "\nYou take some time to assess which weapons are currently"
             + " stocked:\n\n"
             + sprintf("%54s-%12s-%8s\n"
               ," .----------------------------------------------------."
               ,"-----------."
               ,"------. ")
             + sprintf("|   %-49s | %|10s | %5s  |\n", 
                       "Description", "Type", "Qty") 
             + sprintf("%-54s-%12s-%6s\n"
               ," >----------------------------------------------------+"
               ,"-----------+"
               ,"------< ") + contents
             + sprintf("%54s-%12s-%8s\n"
               ," `----------------------------------------------------^"
               ,"-----------^"
               ,"------' ")
             + "\n + Indicates a lasting item\n";               
}

/*
 * Function:    hook_list_commands
 * Description: The list of available commands will be listed after the
 *              contents of the rack. Customize this for each specific
 *              rack for their commands.
 */
public void
hook_list_commands(object for_obj)
{
    for_obj->catch_tell(
            "                         ----> [Commands for Use] <----\n\n"
          + "   <list rack>         - An organized display of the curre"
          + "ntly stocked items\n"
          + "   <list [item name]>  - Displays only items of the specifi"
          + "ed name in stock\n"
          + "   <list [weapontype]> - Displays only items of the specifi"
          + "ed type in stock\n"
          + "   <kick rack>         - Send all non-lasting items tumbling"
          + " to the floor\n");    
}

/*
 * Function:    colect_weapons_of_type
 * Description: Returns all the objects contained which match the
 *              type given. This allows one to filter the contents
 *              by the type of weapon that they want to see.
 */
static object *
collect_weapons_of_type(string type, int first)
{
    object * all_weapons, * weapons;
        
    all_weapons = all_inventory(this_object());
    weapons = ({ });
    foreach (object weapon : all_weapons)
    {
        if (weapon->weapon_type() == type
            || IN_ARRAY(type, weapon->query_names()))
        {
            weapons += ({ weapon });
            if (first)
            {
                // Only want one weapon.
                return weapons;
            }
        }
    }
    
    return weapons;
}

/*
 * Function:    list_cmd
 * Description: Customization of the list command to allow players to
 *              filter by weapon type.
 */
public int
list_cmd(string arg)
{
    object * weapons;
    int first;
    string singular;
    
    if (!arg)
    {
        // Without an argument, we just default to the parent.
        return ::list_cmd(arg);
    }
    
    singular = LANG_SWORD(arg);
    first = 0;
    if (singular == arg)
    {
        first = 1;
    }
    weapons = ({ });

    switch (singular)
    {
    case "sword":        
    case "polearm":
    case "axe":
    case "knife":
    case "club":
    case "missile":
    case "javelin":
        weapons = collect_weapons_of_type(singular, first);
        break;
    }
    
    if (sizeof(weapons) > 0)
    {
        print_list(this_player(), weapons);
        return 1;
    }
        
    return ::list_cmd(arg);
}

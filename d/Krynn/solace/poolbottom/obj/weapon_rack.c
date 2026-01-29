/* 
 * General Weapon Rack for the Guilds of Genesis
 *  
 * This weapon rack is based on the describable rack system. It customizes
 * the messages as it relates to weapons.
 *
 * Created by Arman based on code by Petros, Jan 2016
 */

inherit "/d/Genesis/specials/guilds/objs/weapon_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

void
create_rack()
{
    set_name("stand");
    set_adj("weapons");
    set_short("weapons stand");
    set_long("This is a simple but sturdy hardwood stand for weapons.\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);
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

    if (obj->query_name() == "staff")
    {
        write("Staves should be stored in the staff rack.\n");
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



/*
 * Filename:    new_glow_rack
 * Description: Equipment rack for knights, made to hold lasting items.
 *
 * Creator:     Carnak, 2017-09-21
 */
inherit "/d/Genesis/specials/guilds/objs/describable_rack";

#include "../../guild.h"
#include <stdproperties.h>
#include <macros.h>

/*
 * Function:    hook_prepend_describe_contents
 * Description: Allows one to customize the text that goes above the
 *              listing of the contents in the rack object.
 */
public void
hook_prepend_describe_contents(object for_obj, object * obarr)
{
} /* hook_prepend_describe_contents */

/*
 * Function:    hook_append_describe_contents
 * Description: Allows one to customize the text that goes after the
 *              listing of the contents in the rack object.
 */
public void
hook_append_describe_contents(object for_obj, object * obarr)
{
} /* hook_append_describe_contents */

/*
 * Function:    format_header_and_footer
 * Description: This prints the header and the footer that surrounds
 *              the item rows. It should match the number of columns that
 *              are printed in format_list_item_row.
 */
public string
format_header_and_footer(string contents)
{
    /* Masked to remove the + indication for non-lasting rack */
    return  "\nThe " + this_object()->short() + " contains: \n\n"
             + "\t" + sprintf("%-54s-%8s\n"
               ," .----------------------------------------------------."
               ,"------. ")
             + "\t" + sprintf("|   %-49s | %5s  |\n", "Description", "Qty") 
             + "\t" + sprintf("%-54s-%6s\n"
               ," >----------------------------------------------------+"
               ,"------< ") + contents
             + "\t" + sprintf("%-54s-%8s\n"
               ," `----------------------------------------------------^"
               ,"------' ")
             + "\n\t+ Indicates a lasting item\n"; 
} /* format_header_and_footer */


/*
 * Function name: log_rack_item
 * Description:   Saves every entry and exit from the rack.
 *                (modified: Added indicator for saving item.)
 */
public void
log_rack_item(object obj, string type)
{
    if (!strlen(query_rack_log_file()))
        return;
    
    setuid();
    seteuid(getuid());
    
    if (file_size(query_rack_log_file() + ".o") == -1)
        save_map(([]), query_rack_log_file());
    
    // We write to the log file in the style of a mapping.
    // This log file can be loaded using restore_map and accessed for
    // display purposes later.
    write_file(query_rack_log_file() + ".o", "timestamp_" + sprintf("%i", time())
    + " ({\"" + this_player()->query_real_name() + "\",\""
    + (obj->check_recoverable() ? "+" : " ") + "\",\"" + obj->short() + "\",\""
    + type + "\",})\n");
} /* log_rack_item */

/*
 * Function:    create_rack
 * Description: Mask this to initialize your own variables
 */
public void
create_rack()
{
    set_name("rack");
    set_adj("complex");
    add_adj("equipment");
    set_short("complex equipment rack");
    set_pname("complex equipment racks");
    set_long("Covering the entire wall is a complex set of storage "
    + "possibilities for any weapon or armour. Constructed of metal and wood, "
    + "this rack is part bin and part closet. Many methods to hang or stack or "
    + "carefully store any type of item exist. Big enough to supply a small "
    + "army.\n");

    set_no_show_composite(1);
    set_rack_log_file(VLOG + "rack_log_test");

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 99999999);
    add_prop(CONT_I_MAX_WEIGHT, 99999999);
    add_prop(CONT_I_VOLUME,     5000);
    add_prop(CONT_I_WEIGHT,     25000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED,     0);
} /* create_rack */

/*
 * Function:    valid_item_for_rack
 * Description: Mask this to indicate what type of items can actually
 *              enter the racks.
 * Arguments:   (object) - obj to verify if it can enter
 * Returns:     (int) 1 - Success, 0 - Failure
 */
public int
valid_item_for_rack(object obj)
{
    /* Only accept armours and weapons */
    if (!obj->check_armour() && !obj->check_weapon())
    {
        write("The " + short() + " is no place for " + obj->short() + ".\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */


/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    object attendant;
    
    /* Prevent access to the rack for disgraced players */
    if (objectp(this_player()) && this_player()->query_skill(SS_DISGRACED))
    {
        attendant = environment(this_object())->query_rack_attendant();
        if (objectp(attendant))
        {
            this_player()->catch_msg(QCTNAME(attendant) + " stops you from "
            + "accessing the " + short() + ".\n");
            this_player()->tell_watcher(QCTNAME(attendant) + " stops "
            + QTNAME(this_player()) + " from accessing the " + short() + ".\n");
        }
        else
        {
            this_player()->catch_msg("You have been disgraced and do not have "
            + "access to the " + short() + ".\n");
            this_player()->tell_watcher(QCTNAME(this_player()) + " is "
            + "experiencing an internal conflict as "
            + this_player()->query_pronoun() + " approaches the " + short()
            + "\n");
        }
        return 1;
    }
    
    return 0;
} /* prevent_leave */
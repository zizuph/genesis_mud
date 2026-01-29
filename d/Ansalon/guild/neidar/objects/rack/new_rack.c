/*
 * Filename:    new_rack
 * Description: Equipment rack for neidars.
 *
 * Creator:     Carnak, 2017-11-22
 */
inherit "/d/Genesis/specials/guilds/objs/describable_rack";

#include "../../guild.h"
#include <stdproperties.h>
#include <macros.h>

mapping rack_log = ([]);
int     transaction = 0;

/*
 * Function name:   query_rack_log
 * Description:     Returns the current mapping of the rack log
 * Arguments:       None
 * Returns:         (mapping) current rack log
 */
public mapping
query_rack_log()
{
    if (!m_sizeof(rack_log))
        rack_log = restore_map(query_rack_log_file());
    
    if (!mappingp(rack_log))
        rack_log = ([]);
    
    return rack_log;
} /* query_rack_log */

/*
 * Function name:   load_rack_log
 * Description:     Loads the rack log mapping
 * Arguments:       None
 * Returns:         (int) size of racklog
 */
public int
load_rack_log()
{
    if (!mappingp(rack_log = restore_map(query_rack_log_file())))
        rack_log = ([]);
        
    return m_sizeof(rack_log);
} /* reload_rack_log */

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
    mapping bak_log;
    string *log_list;
    int     i;
    
    if (!strlen(query_rack_log_file()))
        return;
    
    setuid();
    seteuid(getuid());
    
    if (file_size(query_rack_log_file() + ".o") == -1)
        save_map(rack_log, query_rack_log_file());
    
    if (load_rack_log() >= 500)
    {
        log_list = sort_array(m_indexes(rack_log))[0..(m_sizeof(rack_log) - 250)];
        
        foreach(string stamp: log_list)
        {
            if (!mappingp(bak_log))
                bak_log = ([]);
            
            bak_log[stamp] = rack_log[stamp];
            m_delkey(rack_log, stamp);
        }
        
        if (m_sizeof(bak_log))
        {
            if (file_size(query_rack_log_file() + "_bak") > -1)
                rm(query_rack_log_file() + "_bak");
            
            save_map(bak_log, query_rack_log_file() + "_bak");
        }
    }
    
    /* To give each transaction a unique number */
    transaction++;
    
    rack_log["timestamp_" + sprintf("%i", time()) + "_" + transaction] = ({
        this_player()->query_real_name(),
        (obj->check_recoverable() ? "+" : " "),
        obj->short(),
        type
    });
    
    save_map(rack_log, query_rack_log_file());
} /* log_rack_item */

/*
 * Function:    create_rack
 * Description: Mask this to initialize your own variables
 */
public void
create_rack()
{
    set_name("rack");
    set_adj(({"large", "wooden"}));
    set_short("large wooden rack");
    set_long("This is a large rack, made from a blackwood "
    + "pine native to this area. It has been designed to hold "
    + "various items.\n");

    set_no_show_composite(0);

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 90000000);
    add_prop(CONT_I_MAX_WEIGHT, 90000000);
    add_prop(CONT_I_VOLUME,     750000);
    add_prop(CONT_I_WEIGHT,     100000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED,     0);
} /* create_rack */

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
    return 0;
} /* prevent_leave */
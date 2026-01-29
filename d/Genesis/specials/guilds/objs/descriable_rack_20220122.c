/* 
 * Descriptive Rack 
 * 
 * A rack that pretties up the display of the contents rather than just
 * using a composite list. This rack also has special functionality
 * baked in.
 *   - Rack Logging (see set_rack_log_file)
 *   - ability to auto-save content (see item_recovery_lib)
 * 
 * Created by Petros, September 2008
 * 
 * Modifications:
 *   - Changed the list to be even more modularized, allowing specialized
 *     lists like weapon lists and armour lists. Petros, July 2009
 *   - Added support for auto-save using item recovery library. Petros, October 2010
 */

inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

// Global variables
public string   m_racklog;

// Prototypes
public int      list_cmd(string arg);
public int      do_kick(string arg);
public void     print_list(object for_obj, object *obarr);

// Hooks to Allow Customization
public void hook_prepend_describe_contents(object for_obj, object * obarr);
public void hook_list_commands(object for_obj);
public void hook_append_describe_contents(object for_obj, object * obarr);
public void hook_list_cmd_fail();
public void hook_print_empty_list(object for_obj);
public void hook_kick_failed_message();
public void hook_kick_no_nonglowing_message();
public void hook_kick_nonglowing_message(object * nonglowing);
public int  valid_item_for_rack(object obj);
public string   format_list_item_row(string short_desc, int count, 
                                     int recoverable, object obj);
public string   format_header_and_footer(string contents);

/*
 * Function:    hook_prepend_describe_contents
 * Description: Allows one to customize the text that goes above the
 *              listing of the contents in the rack object.
 */
public void
hook_prepend_describe_contents(object for_obj, object * obarr)
{
    for_obj->catch_tell(
        "==========================================================="
      + "=====================\n"
      + " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~  Current Contents  ~*~*~*~*~"
      + "*~*~*~*~*~*~*~*~*~*~ \n"
      + "==========================================================="
      + "=====================\n");
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
          + "   <kick rack>         - Send all non-lasting items tumbling"
          + " to the floor\n");
}

/*
 * Function:    hook_append_describe_contents
 * Description: Allows one to customize the text that goes after the
 *              listing of the contents in the rack object.
 */
public void
hook_append_describe_contents(object for_obj, object * obarr)
{
    string name = query_name();
    for_obj->catch_tell(
        "==========================================================="
      + "=====================\n"
      + " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
      + "*~*~*~*~*~*~*~*~*~*~* \n"
      + "==========================================================="
      + "=====================\n\n");
    hook_list_commands(for_obj);
}

/*
 * Function:    hook_list_cmd_fail
 * Description: Hook that allows one to customize the message that is 
 *              returned when the list command fails.
 */
public void
hook_list_cmd_fail()
{
    notify_fail("List what objects?\n");
}

/*
 * Function:    hook_print_empty_list
 * Description: This gets called when the rack is empty.
 */
public void
hook_print_empty_list(object for_obj)
{
    for_obj->catch_tell("The " + this_object()->short() + " is "
                      + "empty.\n");
}

/*
 * Function:    hook_kick_failed_message
 * Description: This message is sent when someone doesn't kick 
 *              this particular rack. It's a notify_fail so it
 *              defers to the next items to catch the verb.
 */
public void
hook_kick_failed_message()
{
    notify_fail(capitalize(query_verb()) + " what? The " + short() 
        + "? <" + query_verb() + " " + short() + ">\n");
}

/*
 * Function:    hook_kick_no_nonglowing_message
 * Description: This hook is called when there is nothing in the rack to
 *              kick out of it. Everything in the rack is glowing, or
 *              there is nothing in the rack.
 */
public void
hook_kick_no_nonglowing_message()
{
    write("You " + query_verb() + " the " + short() + " but nothing "
        + "falls out.\n");
}

/*
 * Function:    hook_kick_nonglowing_message
 * Description: This hook is called when there are objects that tumble
 *              out. It passes the objects for the message to customize.
 */
public void
hook_kick_nonglowing_message(object * nonglowing)
{
    write("You " + query_verb() + " the " + short() + " and out tumbles "
        + COMPOSITE_ALL_DEAD(nonglowing) + ".\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
        + " " + query_verb() + "s the " + short() + " and out tumbles "
        + COMPOSITE_ALL_DEAD(nonglowing) + ".\n", this_player());
}

/*
 * Function:    valid_item_for_rack
 * Description: Mask this to indicate what type of items can actually
 *              enter the racks.
 */
public int
valid_item_for_rack(object obj)
{
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
    string row_content, prepend_text;
    
    if (recoverable == 1)
    {
        prepend_text = "+ ";
    }
    else
    {
        prepend_text = "  ";
    }
    
    return "\t" + sprintf("|  %-50s | %5d  |\n", prepend_text + short_desc, 
                        count);
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
             + "\n\t + Indicates a lasting item\n";             
}

//    END HOOK CUSTOMIZATIONS   //


/*
 * Function:    create_rack
 * Description: Mask this to initialize your own variables
 */
public void
create_rack()
{
}

/*
 * Function:    create_container
 * Description: Simply calls create_rack. Cannot be masked.
 */
public nomask void
create_container()
{
    set_name("rack");
    set_long("This is a standard describable rack.\n");
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);    
    add_prop(OBJ_M_NO_GET, "The " + short() + " is simply too heavy to "
        + "be taken.\n");    

    // Call the customized create_rack
    create_rack();

    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        // Only perform Steps 2 and 3 for clones
        return;
    }

    // Step 2. Set the options of whether you want to enable logging or recovery
    set_enable_logging(0); // this logging is different from the rack logging for seeing who is taking and removing items
    set_enable_recovery(1);
    
    // Step 3. Initialize the Database and call recover_objects_from_database
    //         using an alarm.
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());   
}

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object obj)
{
    if (!valid_item_for_rack(obj))
    {
        return 1;
    }
   
    return ::prevent_enter(obj);
}

public void
init()
{
    ::init();
    add_action(list_cmd, "list");  
    add_action(do_kick, "kick");  
}

public void
describe_contents(object for_obj, object *obarr)
{
    hook_prepend_describe_contents(for_obj, obarr);
    ::describe_contents(for_obj, obarr);
    hook_append_describe_contents(for_obj, obarr);
}

/* 
 * Function:    resolve_argument
 * Description: Helper function to allow the user to specify different 
 *              items that they want to list.
 */
public object *
resolve_arguments(string arg)
{
    mixed * matches;
    object  rack;
        
    // See if the user typed something like "list weapon rack"
    if (parse_command(arg, all_inventory(environment(this_player())),
                      "[the] %i", matches))
    {
        if (matches[0] == 1 && matches[1] == this_object())
        {
            // Simply get the first object in the array
            rack = matches[1];
            return all_inventory(rack);
        }
        else if (matches[0] < 0 
                 && sizeof(matches) > (matches[0] * -1)
                 && matches[(matches[0] * -1)] == this_object())
        {
            // player used something like "first, second, third"
            rack = matches[(matches[0] * -1)];
            return all_inventory(rack);
        }
    }

    // Now see if the user is trying to list something inside the rack
    if (parse_command(arg, all_inventory(this_object()), 
                      "[the] %i", matches))
    {
        if (matches[0] == 0)
        {
            // parse matched multiple objects
            return matches[1..];
        }
        else if (matches[0] > 0) // # of items to return
        {
            int index = matches[0];
            if (sizeof(matches) > matches[0])
            {
                return matches[1..index];
            }
        }
        else if (matches[0] < 0) // which item. eg. second, third
        {
            // player used something like "first, second, third"
            int index = matches[0] * -1;
            if (sizeof(matches) > index)
            {
                return ({ matches[index] });
            }
        }
    }
    
    return 0;
}

/*
 * Function:    list_cmd
 * Description: The actual list command function. It simply resolves
 *              the command into proper objects and prints the list
 *              to the player.
 */
public int
list_cmd(string arg)
{
    object * results;
    
    if (!arg)
    {
        hook_list_cmd_fail();
        return 0;
    }
    
    results = resolve_arguments(arg);
    if (pointerp(results))
    {
        print_list(this_player(), results);
        return 1;
    }
    
    hook_list_cmd_fail();
    return 0;
}

public void
print_list(object for_obj, object *obarr)
{
    mapping     object_count; /* tracks number of same object */
    mapping     recoverable;
    mapping     object_map;
    string *    eq_order;
    string      contents, key;
    int         nAmount;
        
    if (sizeof(obarr) == 0)
    {
        hook_print_empty_list(for_obj);
        return;
    }
    
    object_map = ([ ]);
    object_count = ([ ]);
    recoverable = ([ ]);
    eq_order = ({ });
    contents = "";
    foreach (object obj : obarr)
    {
        nAmount = 1;
        if (obj->query_prop(HEAP_I_IS))
        {
            nAmount = obj->num_heap();
        }
        key = obj->short();
        if (!IN_ARRAY(key, m_indices(object_count)))
        {
            object_count[key] = 0;
            recoverable[key] = 0;
            eq_order += ({ key });
            object_map[key] = obj;
        }
        object_count[key] += nAmount;
        if (obj->check_recoverable())
        {
            recoverable[key] = 1;
        }
    }
    
    foreach (string short_desc : eq_order)
    {
        contents += format_list_item_row(short_desc, 
            object_count[short_desc], recoverable[short_desc], 
            object_map[short_desc]);
    }
    
    contents = format_header_and_footer(contents);
    for_obj->catch_tell(contents + "\n");
}

/*
 * Function:    do_kick
 * Description: Function that separates out the non-saving items from the
 *              rack. This is useful for during armageddon.
 */
public int
do_kick(string arg)
{
    mixed matches;
    object * nonglowing;
    object rack;
    
    if (!strlen(arg))
    {
        return 0;
    }
    
    if (parse_command(arg, all_inventory(environment(this_player())),
                      "[the] %i", matches))
    {
        if (matches[0] == 1 && matches[1] == this_object())
        {
            rack = this_object();
        }
    }

    if (!objectp(rack))
    {
        hook_kick_failed_message();
        return 0;
    }
    
    nonglowing = filter(all_inventory(), &operator(==)(0) @ &->check_recoverable());
    if (!sizeof(nonglowing))
    {
        hook_kick_no_nonglowing_message();
        return 1;
    }
    
    nonglowing->move(environment());
    
    // Send message of what was removed from the rack inventory
    hook_kick_nonglowing_message(nonglowing);
    
    return 1;
}

/*
 * Function:    do_help
 * Description: Default help command function. One can add it to the
 *              rack by doing an add_action
 */
public int
do_help(string arg)
{
    hook_list_commands(this_player());
    return 1;
}

// LOGGING FUNCTIONS //
// The describable rack supports logging. By default, there is no
// logging. By calling set_rack_log_file, it starts the logging

public void
set_rack_log_file(string filename)
{
    m_racklog = filename;
}

public string
query_rack_log_file()
{
    return m_racklog;
}

public void
log_rack_item(object obj, string type)
{
    if (strlen(query_rack_log_file()) == 0)
    {
        // If the file is not set, don't log anything
        return;
    }
    
    setuid();
    seteuid(getuid());
    // We write to the log file in the style of a mapping.
    // This log file can be loaded using restore_map and accessed for
    // display purposes later.
    write_file(query_rack_log_file(),
        "timestamp_" + sprintf("%i", time()) + " ({\"" + this_player()->query_real_name()
      + "\",\"" + obj->short() + "\",\"" + type + "\",})\n");
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

    // We log this_player() as the person that added this item
    // to the rack.
    log_rack_item(ob, "enter");    
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

    // Even if to is 0 we must remove the rack entry as this happen when the item is
    // is destructed.
    if (to == this_object())
    {
        // Not actually leaving this container, just return
        return;
    }
    
    // We log this_player() as the person that removed this
    // item from the rack
    log_rack_item(ob, "leave");
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
}

// END LOGGING FUNCTIONS //

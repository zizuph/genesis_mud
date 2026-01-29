
/* 
 * Descriptive Rack 
 * 
 * A rack that pretties up the display of the contents rather than just
 * using a composite list.
 * 
 * Created by Petros, September 2008
 */

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

// Prototypes
public int      list_cmd(string arg);
public void     print_list(object for_obj, object *obarr);


void
create_rack()
{
}

void
create_container()
{
    create_rack();
}

public int
valid_item_for_rack(object obj)
{
    return 1;
}

public int
prevent_enter(object obj)
{
    if (!valid_item_for_rack(obj))
    {
        return 1;
    }
   
    ::prevent_enter(obj);
}

void
init()
{
    ::init();
    add_action(list_cmd, "list");    
}

public void
describe_contents(object for_obj, object *obarr)
{
    string name = query_name();
    for_obj->catch_tell("You can use <list " + this_object()->short()
                      + "> to see the contents of the " + name 
                      + " in a list.\nYou can also use <list> to filter "
                      + "the " + name + ". eg. <list swords>\n\n");
    ::describe_contents(for_obj, obarr);
}

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
        else if (matches[0] == 1)
        {
            // Simply get the first object in the array
            return ({ matches[1] });
        }
        else if (matches[0] < 0 
                 && sizeof(matches) > (matches[0] * -1))
        {
            // player used something like "first, second, third"
            return ({ matches[(matches[0] * -1)] });
        }
    }
    
    return 0;
}

public int
list_cmd(string arg)
{
    object * results;
    
    if (!arg)
    {
        notify_fail("List what objects?\n");
        return 0;
    }
    
    results = resolve_arguments(arg);
    if (pointerp(results))
    {
        print_list(this_player(), results);
        return 1;
    }
    
    notify_fail("List what objects?\n");
    return 0;
}

public void
print_list(object for_obj, object *obarr)
{
    mapping     object_count; /* tracks number of same object */
    mapping     recoverable;
    string *    eq_order;
    string      contents, key;
    int         nAmount;
        
    if (sizeof(obarr) == 0)
    {
        for_obj->catch_tell("The " + this_object()->short() + " is "
                          + "empty.\n");
        return;
    }
    
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
        }
        object_count[key] += nAmount;
        if (obj->check_recoverable())
        {
            recoverable[key] = 1;
        }
    }
    
    foreach (string short_desc : eq_order)
    {
        if (recoverable[short_desc] == 1)
        {
            contents += sprintf("| %-50s | %5d |\n", "+ " + short_desc, 
                                object_count[short_desc]);
        }
        else
        {
            contents += sprintf("| %-50s | %5d |\n", "  " + short_desc, 
                                object_count[short_desc]);
        }            
    }
    
    contents = "\nThe " + this_object()->short() + " contains: \n"
             + sprintf("%-53s-%8s\n"
               ,"-----------------------------------------------------"
               ,"--------")
             + sprintf("| %-50s | %5s |\n", "Description", "Qty") 
             + sprintf("%-53s-%6s\n"
               ,"-----------------------------------------------------"
               ,"--------") + contents
             + sprintf("%-53s-%8s\n"
               ,"-----------------------------------------------------"
               ,"--------");
    contents += "\n + Indicates a lasting item\n";
    for_obj->catch_tell(contents + "\n");
}


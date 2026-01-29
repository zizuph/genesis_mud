#include "defs.h"
#include <files.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#pragma save_binary

inherit RACK;


void
remove_object()
{
    if (living(previous_object()))
       log_file("rack", previous_object()->query_name() +
                       " destructed rack.\n");
    ::remove_object();
}

void
create_rack()
{
	set_adj("weapon");
	set_long(
            "This rack has many attachments for holding all sorts of weapons." +
            "\n");
}

int
fits(object ob)
{
  	return member("weapon", ob->query_names());
  //return ob->query_dt() && ob->query_hit();
}

public void
print_list(object for_obj, object *obarr)
{
    mapping     object_count; /* tracks number of same object */
    mapping     weapon_types; /* tracks the weapon type of the object */
    mapping     recoverable;
    string *    eq_order;
    string      contents, key, weapon_type;
    int         nAmount;
    
    if (sizeof(obarr) == 0)
    {
        for_obj->catch_tell("The " + this_object()->short() + " is "
                          + "empty.\n");
        return;
    }
    
    // Initialize variables
    object_count = ([ ]);
    weapon_types = ([ ]);
    recoverable = ([ ]);
    eq_order = ({ });
    contents = "";
    foreach (object obj : obarr)
    {
        if (!IS_WEAPON_OBJECT(obj))
        {
            // We only process weapons
            continue;
        }
        
        nAmount = 1;
        if (obj->query_prop(HEAP_I_IS))
        {
            nAmount = obj->num_heap();
        }
        key = obj->short();
        if (!IN_ARRAY(key, m_indices(object_count)))
        {
            object_count[key] = 0;
            weapon_types[key] = obj->query_wt();
            eq_order += ({ key });
            recoverable[key] = 0;
        }
        object_count[key] += nAmount;
        if (obj->check_recoverable())
        {
            recoverable[key] = 1;
        }
        
    }
    
    foreach (string short_desc : eq_order)
    {
        switch (weapon_types[short_desc])
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
        if (recoverable[short_desc] == 1)
        {        
            contents += sprintf("| %-50s | %|10s | %5d |\n", 
                                "+ " + short_desc, 
                                weapon_type, object_count[short_desc]);
        }
        else
        {
            contents += sprintf("| %-50s | %|10s | %5d |\n", 
                                "  " + short_desc,
                                weapon_type, object_count[short_desc]);
        }
    }
    
    contents = "\nThe " + this_object()->short() + " contains: \n"
             + sprintf("%53s-%12s-%8s\n"
               ,"-----------------------------------------------------"
               ,"------------"
               ,"--------")
             + sprintf("| %-50s | %|10s | %5s |\n", 
                       "Description", "Type", "Qty") 
             + sprintf("%-53s-%12s-%6s\n"
               ,"-----------------------------------------------------"
               ,"------------"
               ,"--------") + contents
             + sprintf("%53s-%12s-%8s\n"
               ,"-----------------------------------------------------"
               ,"------------"
               ,"--------");
    contents += "\n + Indicates a lasting item\n";               
    for_obj->catch_tell(contents + "\n");
}


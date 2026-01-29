/*
 * Storeless Shop Support Library
 *
 * This library adds functionality that allows items to be bought and sold
 * without an actual storeroom. Instead, the items are stored in a data
 * file when sold, and cloned from the data file when purchased. Obviously
 * great care should be used in the types of objects allowed to be sold
 * or bought, as this library cannot support the storage of properties
 * for each individual items.
 *
 * Most likely, you should not need to inherit this library directly.
 * Instead, you should inherit storeless_shop.c instead.
 *
 * Created by Petros, May 2010
 */
#pragma strict_types;

#include <filter_funs.h>
#include <macros.h>
#include <language.h>
#include <files.h>

inherit "/d/Sparkle/area/city/lib/utility_functions"; // to safely load master files

// Global variables
public mapping      object_list = 0;
public string       data_file = 0;
public int          save_alarm = 0;

/*
 * Function:    set_data_filename
 * Description: Sets the location of the file that should store the object list
 *              data, which includes which objects are in the store and the
 *              actual quantities. This filename should be a full path.
 */
public void
set_data_filename(string filename)
{
    data_file = filename;
}

/*
 * Function:    query_data_filename
 * Description: Returns the location of the file that should store the object list
 *              data, which includes which objects are in the store and the
 *              actual quantities
 */
public string
query_data_filename()
{
    if (!strlen(data_file))
    {
        // Default it to objectlist.o in the current directory
        string current_directory = implode(explode(MASTER_OB(this_object()), "/")[..-2], "/");
        return current_directory + "/objectlist";
    }
    return data_file;
}

/*
 * Function:    load_object_data
 * Description: Restores the map from disk
 */
public void
load_object_data()
{
    if (object_list)
    {
        // Don't reload the herb data.
        return;
    }
    setuid(); seteuid(getuid());
    object_list = restore_map(query_data_filename());
}

/*
 * Function:    save_object_data
 * Description: Saves the current object_list to disk.
 */
public void
save_object_data()
{
    setuid(); seteuid(getuid());
    if (!mappingp(object_list))
    {
        save_map( ([ ]), query_data_filename());
    }
    else
    {
        save_map(object_list, query_data_filename());
    }
}

public void
alarmed_save_object_data()
{
    if (get_alarm(save_alarm))
    {
        remove_alarm(save_alarm);
    }
    
    save_alarm = set_alarm(1.0, 0.0, save_object_data);
}

/*
 * Function:    update_object_entry
 * Description: Updates the object entry in the mapping. It stores information
 *              about the object file and the quantity that
 *              is in the store.
 * Arguments:   filename - the filename of the object
 *              quantity - the quantity that is in the store
 */
public int
update_object_entry(string filename, int quantity)
{
    if (!mappingp(object_list))
    {
        // Load the data map if it hasn't been loaded before
        load_object_data();
    }
    
    if (!strlen(filename))
    {
        // Invalid string for filename, don't do anything.
        return 0;
    }
    
    if (quantity == 0)
    {
        // Remove the entry if the quantity is set to 0. This filename may
        // not be in the proper format. Eg. /d/Krynn/common/herbs/chicory.c
        m_delkey(object_list, filename);
    }
    
    // Mapping has entries with this format: ([ herb_name : ({ herb_filename, quantity }), ... ])
    // First we need to get the herb name from the herb file itself
    object master_obj = safely_load_master_file(filename);
    if (!objectp(master_obj))
    {
        return 0; // couldn't find the master file 
    }
    
    if (quantity == 0)
    {
        // Remove the entry if the quantity is set to 0. Called a second time
        // here to remove the proper entry.
        m_delkey(object_list, MASTER_OB(master_obj));
        alarmed_save_object_data();
        return 1;
    }

    object_list[MASTER_OB(master_obj)] = quantity;
    
    // Save the changes to disk
    alarmed_save_object_data();
    return 1;
}

/*
 * Function:    find_objects_using_name
 * Description: Locates objects in the store based on the names that
 *              it has.
 * Arguments:   name - the name that the object should be identified by
 * Returns:     a list of objects that match the name.
 */
public object *
find_objects_using_name(string name)
{
    object * matching_objects = ({ });
    if (!strlen(name))
    {
        return matching_objects;
    }
    
    string singular_name = LANG_SWORD(name);    
    foreach (string filename, int quantity : object_list)
    {
        object current_object = safely_load_master_file(filename);
        if (!objectp(current_object))
        {
            continue;
        }
        // Special processing for herbs since they have a special identified name
        if (IS_HERB_OBJECT(current_object))
        {
            string herbname = current_object->query_herb_name();
            if (herbname == name || herbname == singular_name)
            {
                matching_objects += ({ current_object });
                continue;
            }            
        }
        // All other objects, we use parse_command to check if it matches
        if (parse_command(name, current_object, " %i "))
        {
            matching_objects += ({ current_object });
        }
    }
    
    return matching_objects;
}

/*
 * Function:    query_object_quantity
 * Description: Retrieves the quantity of the objects in the object list.
 */ 
public int
query_object_quantity(object current_object)
{
    if (!objectp(current_object))
    {
        return 0;
    }
    string master_file = MASTER_OB(current_object);
    return max(0, object_list[master_file]);
}

/*
 * Function:    hook_print_object_header()
 * Description: Mask this to customize the header that gets printed for normal
 *              objects.
 */
public string
hook_print_object_header()
{
    return 
        "___________________________________________________________________________\n" +
        "|                  Description                       |  Qty |  P  G  S  C |\n" +
        "===========================================================================\n";
}

/*
 * Function:    hook_print_herb_header()
 * Description: Mask this to customize the header that gets printed for herbs
 */
public string
hook_print_herb_header()
{
    return 
        "___________________________________________________________________________\n" +
        "|     Name     |             Description             |  Qty |  P  G  S  C |\n" +
        "===========================================================================\n";
}

/*
 * Function:    hook_print_object_footer
 * Description: Mask this to customize the footer that gets printed for normal objects
 */
public string
hook_print_object_footer()
{
    return 
        "===========================================================================\n";
}

/*
 * Function:    hook_print_herb_footer
 * Description: Mask this to customize the footer that gets printed for herb listings
 */
public string
hook_print_herb_footer()
{
    return 
        "===========================================================================\n";
}

/*
 * Function:    hook_print_object_item
 * Desrciption: Given a single object, it will print out the
 *              line for the store item. Mask this to customize your own
 *              display.
 */
public string
hook_print_object_item(object current_object)
{
    string output = "";
    string line_format = "| %-50.50s | %4d | %2d %2d %2d %2d |\n";
    int price = this_object()->query_buy_price(current_object);
    int quantity = query_object_quantity(current_object);
    output += sprintf(line_format, 
        current_object->short(), 
        quantity,
        price / 1728, 
        (price % 1728) / 144, 
        (price % 144) / 12, 
        price % 12);
    return output;
}

/*
 * Function:    hook_print_herb_item
 * Desrciption: Given a single object, it will print out the
 *              line for the store item. Mask this to customize your own
 *              display.
 */
public string
hook_print_herb_item(object current_object)
{
    string output = "";
    string line_format = "| %-12.12s | %-35.35s | %4d | %2d %2d %2d %2d |\n";
    int price = this_object()->query_buy_price(current_object);
    int quantity = query_object_quantity(current_object);
    output += sprintf(line_format, 
        current_object->query_herb_name(),  
        current_object->short(), 
        quantity,
        price / 1728, 
        (price % 1728) / 144, 
        (price % 144) / 12, 
        price % 12);
    return output;
}

/*
 * Function:    sort_herbs_by_name
 * Description: Sort function to be passed into sort_array when sorting
 *              a list of herb objects.
 */
static int
sort_herbs_by_name(object a, object b)
{
    string a_name = a->query_herb_name();
    string b_name = b->query_herb_name();
    if (a_name < b_name)
    {
        return -1;
    }
    else if (b_name < a_name)
    {
        return 1;
    }
    return 0;
}

/*
 * Function:    print_object_list
 * Description: Given a list of objects, prints out a nicely formated
 *              list of objects and the price and quantity in the store.
 */
public string
print_object_list(object * matching_objects)
{
    string output = "";
    
    if (!sizeof(matching_objects))
    {
        return output;
    }
    
    output += hook_print_object_header();
    foreach (object current_object : matching_objects)
    {
        output += hook_print_object_item(current_object);
    }
    output += hook_print_object_footer();
    
    return output;
}

/*
 * Function:    print_herb_list
 * Description: Given a list of objects, prints out a nicely formated
 *              list of objects and the price and quantity in the store.
 */
public string
print_herb_list(object * matching_objects)
{
    string output = "";
    
    if (!sizeof(matching_objects))
    {
        return output;
    }
    
    output += hook_print_herb_header();
    object * sorted_objects = sort_array(matching_objects, sort_herbs_by_name);
    foreach (object current_object : sorted_objects)
    {
        output += hook_print_herb_item(current_object);
    }
    output += hook_print_herb_footer();
    
    return output;
}

/*
 * Function:    clone_object_quantity
 * Description: Clones the desired quantity of a certain object.
 */
public object *
clone_object_quantity(object master_object, int desired_quantity)
{
    string master_file = MASTER_OB(master_object);
    object * cloned_objects = ({ });
    // Clone all the objects
    if (IS_HEAP_OBJECT(master_object))
    {
        object new_object = clone_object(master_file);
        new_object->set_heap_size(desired_quantity);
        cloned_objects += ({ new_object });
    }
    else
    {
        for (int index = 0; index < desired_quantity; ++index)
        {
            cloned_objects += ({ clone_object(master_file) });
        }     
    }
   
    return cloned_objects;
}

/*
 * Function:    clone_object_quantity_from_store
 * Description: Takes a certain amount of object quantity from the store.
 *              Will not clone more than is available in the store. It
 *              is the responsibility of the caller to properly update
 *              the store quantity by calling update_object_entry.
 */
public object *
clone_object_quantity_from_store(string str)
{
    object * matching_objects = find_objects_using_name(str);
    if (!sizeof(matching_objects))
    {
        return 0;
    }
    
    object matching_object = matching_objects[0];
    int stock_quantity = query_object_quantity(matching_object);
    int desired_quantity;
    string unit;
    if (sscanf(str, "%d %s", desired_quantity, unit) != 2)
    {
        desired_quantity = 1;
        unit = str;
    }
    if (desired_quantity > stock_quantity) // not enough in store
    {
        return 0;
    }
    
    return clone_object_quantity(matching_object, desired_quantity);
}


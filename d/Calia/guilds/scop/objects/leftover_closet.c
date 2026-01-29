
/* 
 *  Leftover Closet for the Spirit Circle of Psuchae
 *
 *  Petros - September 2008
 *    Changed the rack to use a describable rack system so that one
 *    can list objects by type and see it in a nicely formatted list.
 */

inherit "/d/Calia/guilds/scop/objects/describable_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

// Defines
#define     LEFTOVER_DATA   (SPIRIT_TEXTS + "leftover_data")

// Global Variables
public mixed *      leftover_data = ({ });
public int          save_data_alarm = 0;

// Prototypes
public void         restore_leftover(string race, string organ, int quantity);

/*
 * Function:    load_data
 * Description: Loads the data from the data file and stores it locally.
 *              An alarm should be started based on this data to regenerate
 *              all the leftovers.
 */
public void
load_data()
{
    // Clean up the leftovers by deleting everything
    all_inventory(this_object())->remove_object();
    
    // Load the map and clone objects
    mapping data = restore_map(LEFTOVER_DATA);
    foreach (mixed * leftover_item : data["data"])
    {
        // Use an alarm so that it won't hit the exec limit
        set_alarm(0.0, 0.0, 
            &restore_leftover(leftover_item[0], leftover_item[1], leftover_item[2]));
    }
}

/*
 * Function:    restore_leftover
 * Description: Given a specification for a leftover, clones it, initializes
 *              it, and sets the quantity. Finally, move it to the container.
 */
public void
restore_leftover(string race, string organ, int quantity)
{
    object leftover = clone_object("/std/leftover");
    leftover->leftover_init(organ, race);
    leftover->set_heap_size(max(quantity, 1));
    leftover->move(this_object());    
}

/*
 * Function:    save_data
 * Description: Saves the information about the leftovers in the data
 *              file so that it can be restored later.
 */
public void
save_data()
{
    // The list stores items with these pieces of information
    // ({ race, organ, quantity })  
    leftover_data = ({ });
    foreach (object obj : all_inventory(this_object()))
    {
        if (!IS_LEFTOVER_OBJECT(obj))
        {
            continue;
        }
        
        if (!strlen(obj->query_race())
            || !strlen(obj->query_organ()))
        {
            // If it's not validly created, we don't bother saving it
            // for later use. this includes things like the heads from
            // the Ogre guild.
            continue;
        }
        
        leftover_data += ({ ({ obj->query_race(), obj->query_organ(), obj->num_heap() }) });
    }
    save_map( ([ "data" : leftover_data ]), LEFTOVER_DATA);
}

void
create_rack()
{
    set_name("closet");
    set_adj("tall");
    add_adj("double-doored");    
    set_short("tall double-doored closet");
    set_long("This is a tall double-doored closet made of a deep brown "
           + "oak. Crafted with much care but also with simplicity in "
           + "mind. The doors are inlaid with small grey-hued windows "
           + "that flicker light and shadow. Carved and emblazensed "
           + "across the surfaces, crossing both the glass and front "
           + "doors are three large circles, entwined and outlined by a "
           + "single greater circle.\n");

    add_item( ({ "oak", "deep brown oak", "brown oak" }),
              "The closet is made of solid deep brown oak. The "
            + "oak is carefully crafted, and appears ageless.\n" );
    
    add_item( ({ "doors", "windows", "light", "shadow" }),
              "The doors of the closet are exquisite. The light and "
            + "shadow that reflect off of them mesmerize you as you "
            + "examine them.\n" );
    
    add_item( ({ "circles", "three circles", "large circles", "circle",
                "three large circles", "symbol", "symbols" }),
              "The symbols are a reminder of where you stand, the Holy "
            + "Temple of Psuchae.\n" );
    
    add_item( ({ "shelf", "shelves" }),
              "The shelves contain places where leftovers are usually "
            + "stored.\n" );
            
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The tall double-doored closet can't be taken, "
           + "it is entirely too heavy.\n");
    
    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    // Load the data from the file, which clones all the leftover objects
    load_data();
}

/*
 * Function:    remove_object
 * Description: Function that gets called when the object is destructed.
 *              By masking this function, we are making sure that the
 *              very latest data is stored when the object gets destructed.
 *              Reloading the object will load the data and restore the
 *              leftovers.
 */
public void
remove_object()
{
    if (IS_CLONE)
    {
        catch(save_data()); // catch any errors so that we can safely delete.
    }
    ::remove_object();
}

public int
valid_item_for_rack(object obj)
{
    if (!IS_LEFTOVER_OBJECT(obj))
    {
        write("You can't seem to find any place to put the "
            + obj->short() + " in the " + short() + ".\n");
        return 0;
    }

    return 1;
}

public void
describe_contents(object for_obj, object *obarr)
{
    string name = query_name();
    for_obj->catch_tell("You can use <list leftovers> to see the contents "
                      + "of the " + name 
                      + " in a list.\nYou can also use <list> to filter "
                      + "the " + name + ". eg. <list intestines>\n\n");
}

public void
print_list(object for_obj, object *obarr)
{
    mapping     leftover_data;
    mapping     race_data;
    string *    race_order;
    string *    type_order;
    int         nAmount;
    string      leftoverRace, leftoverType, contents;
    
    leftover_data = ([ ]);
    race_order = ({ });
    type_order = ({ });
    contents = "";
    foreach (object obj : obarr)
    {
        // Leftovers are heaps. We keep track of the leftover type,
        // leftover race, and leftover quantities
        if (!IS_LEFTOVER_OBJECT(obj))
        {
            // We only process leftovers
            continue;
        }
        
        // Leftover Quantity
        nAmount = obj->num_heap();
        // Leftover Race
        leftoverRace = obj->query_race();
        if (!IN_ARRAY(leftoverRace, race_order))
        {
            race_order += ({ leftoverRace });
        }
        // Leftover Type
        leftoverType = obj->query_organ();
        if (!IN_ARRAY(leftoverType, type_order))
        {
            type_order += ({ leftoverType });
        }
        
        // Add the data point
        if (!IN_ARRAY(leftoverType, m_indices(leftover_data)))
        {
            leftover_data[leftoverType] = ([ ]);
        }
        
        race_data = leftover_data[leftoverType];
        if (!IN_ARRAY(leftoverRace, m_indices(race_data)))
        {
            race_data[leftoverRace] = 0;
        }
        
        race_data[leftoverRace] += nAmount;
    }
    
    // We've added up all the leftovers by here. We will print out
    // to the player.
    if (sizeof(m_indices(leftover_data)) == 1)
    {
        // We only have a single leftover type. In this case, we will
        // print out the race names.
        leftoverType = (m_indices(leftover_data))[0];
        mapping race_data = leftover_data[leftoverType];
        foreach (string race : race_order)
        {            
            contents += sprintf("| %-50s | %5d |\n", race + " " 
                                + leftoverType, race_data[race]); 
        }

        contents = "\nYou make a quick assessment of the shelf containing "
                 + LANG_PWORD(leftoverType) + " and find: \n"
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------")
                 + sprintf("| %-50s | %5s |\n", "Leftover", "Qty") 
                 + sprintf("%-53s-%6s\n"
                   ,"-----------------------------------------------------"
                   ,"--------") + contents
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------");        
    }
    else if (sizeof(m_indices(leftover_data)) > 1)
    {
        foreach (string type : type_order)
        {
            mapping race_data = leftover_data[type];
            int nCount = 0;
            foreach (string race : m_indices(race_data))
            {
                nCount += race_data[race];
            }
            contents += sprintf("| %-50s | %5d |\n", LANG_PWORD(type), 
                                nCount);
        }
        contents = "\nYou peruse the various shelves of the " + short()
                 + " and estimate the collection to comprise of: \n"
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------")
                 + sprintf("| %-50s | %5s |\n", "Part", "Qty") 
                 + sprintf("%-53s-%6s\n"
                   ,"-----------------------------------------------------"
                   ,"--------") + contents
                 + sprintf("%-53s-%8s\n"
                   ,"-----------------------------------------------------"
                   ,"--------");
        contents += "\nYou can examine a particular shelf using "
                  + "\"list <part>\"\n";
    }
    else
    {
        contents = "You peruse the various shelves of the " + short()
                  + ", but you do not find what you are looking for.\n";
    }
        
    for_obj->catch_tell(contents + "\n");
}

public int
list_cmd(string arg)
{
    object * results;    
    int result;
    
    result = ::list_cmd(arg);
    if (!result && arg == "leftovers")
    {
        print_list(this_player(), ({ }));
        return 1;
    }
    
    return result;
}

public void
alarmed_save_data(object obj)
{
    obj->save_data();
    save_data_alarm = 0;
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
    remove_alarm(save_data_alarm);
    save_data_alarm = set_alarm(5.0, 0.0, &alarmed_save_data(this_object()));
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
    remove_alarm(save_data_alarm);
    save_data_alarm = set_alarm(5.0, 0.0, &alarmed_save_data(this_object()));        
}

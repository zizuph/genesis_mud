/**********************************************************************
 * - rack_base.c                                                    - *
 * - This is a base file to create racks for various items for      - *
 * - Gladiator Guild.                                               - *
 * - Created by Damaris@Genesis 09/2005                             - *
 * - Updated to allow slightly more reporting from the log of items - *
 *   by Mirandus 02/2018
 **********************************************************************/
#pragma strict_types
#pragma save_binary

inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <cmdparse.h>
#include <macros.h>
#include "../defs.h"
#include "../../guild.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define SPECIAL_ITEMS_MASTER    (GLAD_OBJ + "racks/special_items_master")
#define RACK_LOG                (GLAD_LOG + "rack_log")
#define LOG_REPORT_SIZE         5000

// Prototypes
public int          special(string str);

public void
create_rack()
{
}

public nomask void
create_container()
{
    set_name("rack");
    set_pname("racks");
    set_short("rack");
    set_pshort("racks");
    set_long("This rack is obviously meant to hold and "+
	     "store items of all different shapes and sizes.\n");
	
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_GET, "Even a half-giant couldn't lift this "+
	     "thing.\n");

    create_rack();
    
    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    // Step 2. Set the options of whether you want to enable logging or recovery
    set_enable_logging(0);
    set_enable_recovery(1);
    
    // Step 3. Initialize the Database and call recover_objects_from_database
    //         using an alarm.
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());
}



/**********************************************************************
 * - A check to see if they may take from the rack or if rack       - *
 * - privilages have been revoked.                                  - *
 **********************************************************************/

public void
leave_inv(object ob, object to)
{
    object player;
    
    ::leave_inv(ob, to);

    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    if (living(to) && CHECK_PUNISHMENT(to->query_real_name(), PUN_CHEST))
    {
    	ob->move(this_object());
    	tell_object(to, "Your rack privileges have been "+
    		    "revoked.\n");
        return;
    }    

    // If we get here, then we successfully removed the item from the
    // rack.
    if (SPECIAL_ITEMS_MASTER->query_is_special_item(ob))
    {
        if (to == environment())
        {
            player = this_player();
        }
        else
        {
            player = to;
        }
        write_file(RACK_LOG, ctime(time())[..10] + ctime(time())[-4..]
            + ": " + ob->short() + " removed from rack by "
            + capitalize(player->query_real_name()) + ".\n");
    }    

    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);        
}

public int
sort(string str)
{
    int num;
    object *inv;
    string x = "";
    string rack;

    if (!stringp(str))
    {
	notify_fail("Sort what?\n");
	return 0;
    }

    // Prevent someone who does not have rack privileges from getting
    // non-recoverable items.
    if (CHECK_PUNISHMENT(this_player()->query_real_name(), PUN_CHEST))
    {
        notify_fail("Your rack privileges have been revoked.\n");
        return 0;
    }
    
    inv = FIND_STR_IN_OBJECT(str, environment());
    switch(sizeof(inv))
    {
    case 0:
        notify_fail("Which rack do you want to sort?\n");
        return 0;
    case 1:
        /* Intended behaviour. One rack selected. */
        break;
    default:
	notify_fail("You should only sort one rack at a time.\n");
	return 0;
    }

    if (inv[0] != this_object())
    {
	notify_fail("Sort what?\n");
	return 0;
    }
    
    inv = filter(all_inventory(), not @ &->check_recoverable());
    num = sizeof(inv);

    if     (num < 1)  {x += "nothing falls out.\n";}
    else if(num == 1) {x += "something falls out.\n";}
    else              {x += "some equipment falls out.\n";}

    write("You sort the " + short() + " and "+x);
    say(QCTNAME(this_player()) + " sorts the " + QSHORT(this_object()) + 
	" and " + x);
    inv->move(environment());
    return 1;
}

public void
init()
{
    ::init();
    add_action(sort, "sort");
    add_action(special, "special");
}

/* 
 * Function     : format_two_columns
 * Description  : Prints out the items ordered and in two columns.
 * Arguments    : list - array of strings to print
 * Returns      : string of the 2 column formatted list
*/
private string
format_two_columns(string * list)
{
    int total, rows, leftcolumn;
    string result;
    
    result = "";
    if (!list || sizeof(list) == 0)
    {
        return result;
    }
    
    total = sizeof(list);

    rows = total / 2; // rounds down
    leftcolumn = rows + (total % 2);    
    for (int index = 0; index < rows; ++index)
    {
        result +=
            sprintf("%3d: %-34s%3d: %-34s\n", index + 1, list[index],
                    leftcolumn + index + 1, list[index + leftcolumn]);
    }
    // Finally, add the last row if the number of items was odd. This
    // means that only column one will be printed. Nothing should be
    // there for column 2
    if (total % 2 != 0)
    {
        result +=
            sprintf("%3d: %-34s\n", leftcolumn, list[leftcolumn - 1]);
    }
    result += "\n";
    return result;
}

/* 
 * Function     : format_special_list
 * Description  : This prints the string of the specials list
 *                formatted for readability. It categorizes all
 *                the objects so that they are easy to find.
*/
private void
format_special_list(string * special_items)
{
    string * weapons, * armours, * errors;
    object item;
    
    weapons = ({ });
    armours = ({ });
    foreach (string filename : special_items)
    {
        // Go through each specials item, and load it to
        // properly categorize it.
        if (!objectp(item = find_object(filename)) 
            && (LOAD_ERR(filename)
                || !objectp(item = find_object(filename))))
        {
            continue;
        }
        
        if (IS_WEAPON_OBJECT(item))
        {
            weapons += ({ item->short() });
        }
        else if (IS_ARMOUR_OBJECT(item))
        {
            armours += ({ item->short() });
        }
    }
    
    if (sizeof(weapons) > 0)
    {      
        write(sprintf("%|70s\n", "Weapons"));
        write(sprintf("%|70s\n", "======="));
        write(format_two_columns(sort_array(weapons)));
    }    
    
    if (sizeof(armours) > 0)
    {
        write(sprintf("%|70s\n", "Armours"));
        write(sprintf("%|70s\n", "======="));
        write(format_two_columns(sort_array(armours)));
    }
}

public int
is_overseer(object player)
{
    string player_name;
    
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_wiz_level())
    {
        // Wizards are allowed to see the special items and modify
        // them as well.
        return 1;
    }
    
    player_name = player->query_real_name();
    foreach (int pos : POS_ALL)
    {
        if (MANAGER->query_overseer(pos) == player_name)
        {
            return 1;
        }
    }
    
    return 0;
}

/*
 *  Function:     special
 *  Description:  An action function allowing Gladiators to note 
 *                an item as especially important in the racks,
 *                remove such an item from the list, or show a
 *                list of all of them. 
 */ 
public int
special(string str)
{
    object tp = this_player();
    string * special_items;    
    object * items;

    setuid();
    seteuid(getuid());
    
    if (!is_overseer(this_player()))
    {
        return 0;
    }
    
    special_items = SPECIAL_ITEMS_MASTER->query_special_items();
    notify_fail("Syntax: special add  <item>\n" + 
                "        special remove <item>\n" + 
                "        special list\n" +
                "        special log\n");

    if (!stringp(str))
    {
        return 0;
    }
    
    if (str == "list")
    {
        if (!sizeof(special_items))
        {
            notify_fail("The rack guard looks at you confused, and "
                + "and indicates that he has not been instructed "
                + "to watch for any special items.\n"); 
            return 0; 
        } 

        write("The rack guard listens carefully to your request and calmly "
            + "says: Oh mighty Overseer! These are the items that you "
            + "have asked me to watch carefully.\n\n");
        format_special_list(special_items);
        return 1; 
    }
    
    string item;
    if (sscanf(str, "add %s", item) == 1)
    {
        if (SPECIAL_ITEMS_MASTER->query_specials_full())
        {
            notify_fail("The list is full, a listed item has to " +
                        "be removed if you want to add another.\n"); 
            return 0; 
        }
         
        items = FIND_STR_IN_ARR(item, all_inventory(this_player())); 
        if (sizeof(items) > 1) 
        {
            notify_fail("Please refer to one specific item in your "
                + "inventory.\n"); 
            return 0; 
        } 
        else if (!sizeof(items)) 
        {
            notify_fail("There is no such item in your inventory.\n"); 
            return 0; 
        }
         
        if (IN_ARRAY(MASTER_OB(items[0]), special_items))
        {
            notify_fail("That item is already in the list!\n"); 
            return 0; 
        } 

        SPECIAL_ITEMS_MASTER->add_special_item(items[0]);
        write("The rack guard listens carefully to your request and says: "
            + "Oh mighty Overseer! I will surely begin to watch the "
            + items[0]->short() + " carefully.\n");
        return 1;         
    }
    else if (sscanf(str, "remove %s", item) == 1)
    {
        if (!sizeof(special_items))
        {
            notify_fail("There are no items in the list.\n"); 
            return 0; 
        }  

        if (!SPECIAL_ITEMS_MASTER->remove_special_item_by_short(item))
        {
            notify_fail("There is no such item in the list.\n"); 
            return 0; 
        }
                    
        write("The rack guard listens carefully to your request and says: "
            + "Oh mighty Overseer! I'll no longer look for the "
            + item + " in the racks.\n");
        return 1;
    }
    else if (str == "log")
    {
        // Get the last 20 entries in the log file
        int size = file_size(RACK_LOG);
        string * lines;
        if (size == 0)
        {
            write("The rack guard has nothing to tell you.\n");
            return 1;
        }
        else if (size < LOG_REPORT_SIZE)
        {
            lines = explode(read_file(RACK_LOG), "\n");
        }
        else
        {
            lines = explode(read_bytes(RACK_LOG, size - LOG_REPORT_SIZE, LOG_REPORT_SIZE), "\n");
            lines = lines[1..]; // drop first probably truncated entry
        }
        
        write("The rack guard listens carefully to your request and says: "
            + "Oh mighty Overseer! Allow me to give you a report of "
            + "what I have been observing per your requests.\n");
        foreach (string line : lines)
        {
            string date, name, item;
            string action = "", datestr = "Earlier";
            
            if (sscanf(line, "%s: %s added to rack by %s.", date, item, name) == 3)
            {
                action = " adding the ";
            }
            else if (sscanf(line, "%s: %s removed from rack by %s.", date, item, name) == 3)
            {
                action = " removing the ";
            }
            else
            {
                continue;
            }
            string today = ctime(time())[..10] + ctime(time())[-4..];
            string yesterday = ctime(time() - 86400)[..10] 
                + ctime(time() - 86400)[-4..];
            if (date == today)
            {
                datestr = "Today";
            }
            else if (date == yesterday)
            {
                datestr = "Yesterday";
            }
            write("The rack guard says: " + datestr + ", I observed " + name 
                + action + item + ".\n");
        }
        return 1;
    }
    
    return 0; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (from == this_object())
    {
        return;
    }
    
    if (SPECIAL_ITEMS_MASTER->query_is_special_item(ob))
    {
        write_file(RACK_LOG, ctime(time())[..10] + ctime(time())[-4..]
            + ": " + ob->short() + " added to rack by "
            + capitalize(from->query_real_name()) + ".\n");
    }

    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);
}

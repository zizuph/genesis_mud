/* Rack room in the Crystalline palace.
 * 
 * History:
 *        5/6/08    nicely formatted the special items   Petros
 *       11/7/02    added rack log for special items     Maniac
          1/7/00    racked items desc bug fixed          Maniac
          10/6/00   added "special items" feature        Maniac
          20/4/97   added ROOM_I_NO_CLEANUP              Uhclem
          15/4/97   bug corrected                        Maniac
 *        10/10/96  modifications                        Maniac
 *        12/9/96   "kick rack" - non-recoverable items fall off    Maniac
 *         9/9/96   "force rack" option                  Maniac
 *        19/8/96   Don't rack things with keep set      Maniac
 *        20/6/96   Don't rack things of no value        Maniac
 *        18/9/95   don't rack containers with things
 *                  in them                              Maniac
 *         5/9/95   don't rack messages                  Maniac
 *        18/8/95   ROOM_I_INSIDE added                  Maniac
 *         7/8/95   bug corrected                        Maniac
 *        24.3.95   deep_inv -> all_inv                  Maniac
 *        3.3.95    Minor modification                   Maniac
 *        16.2.95   Rack debugged, recr stuff removed    Maniac
 *        23.1.95         Divided                        Glykron
 *         3.1.95         Created                        Maniac & Malcontent
 *
 */

#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <std.h>
#include "defs.h"
#include COUNCIL_HEADER

#pragma save_binary

#define MAX_SPECIAL_RACK_ITEMS 50
#define RACK_SPECIALS (CRPALACE_TEXTS + "rack_specials")

inherit "/std/room";

mapping special_items = ([ ]); 

static object this, weapon_rack, armour_rack, misc_rack, garbage_rack;

string
read_sign()
{
    return
     "The sign says:\n" +
     "    Here are the commands for the rack:\n" +
     "        rack                 - rack everything\n" +
     "        rack <items>         - rack the specified <items>\n" +
     "        rack weapons         - rack all weapons\n" +
     "        rack armours         - rack all armour\n" +
     "        rack misc[ellaneous] - rack all non-weapons and -armour\n" +
     "        appraise <item>      - use appraise skill on <items>. Can \n" +
     "                               also \"appraise <item> in rack\".\n" +
     "        kick <rack>          - separate non-recoverable items\n" +
     "        special              - information about the command \"special\".\n" + 
     "    The command `frack' (forced rack) works the same as the `rack'\n"+
     "    command except that it also racks items which have `keep'\n" +
     "    turned on. Tacking a ! on the end of either verb will include\n" +
     "    rackable worn/wielded stuff into what you rack.\n" +
     "";
}


void
create_room()
{
    set_short("Calian Equipment Room");
    set_long(
        "This is a trapezoidal-shaped room whose east and west walls " +
        "slope away to the south.  " +
        "There is a sign on the wall.  " +
        "\n");

    this = THIS;
    add_item("sign",
        "The sign in on the north wall.  It is framed with wood.\n");
    add_cmd_item("sign", "read", "@@read_sign");
    add_exit(ROOM("light_guild"),"west", 0, 0);
    add_exit(ROOM("light_sanctuary"),"east", 0, 0);

    add_prop(ROOM_I_INSIDE, 1);

/*  Following line prevents room from being removed from memory
    (and contents lost) by automatic cleanup routine.  */

    add_prop(ROOM_I_NO_CLEANUP, 1);

    setuid();
    seteuid(getuid());
    clone_object(CRPALACE_OBJECTS + "rack_log_book")->move(this); 
    misc_rack = clone_object(OBJECT("misc_rack"));
    misc_rack->move(this);
    armour_rack = clone_object(OBJECT("armour_rack"));
    armour_rack->move(this);
    weapon_rack = clone_object(OBJECT("weapon_rack"));
    weapon_rack->move(this);
    garbage_rack = clone_object("/d/Calia/guilds/calians/objects/garbage_bin");
    garbage_rack->move(this);

    restore_object(RACK_SPECIALS); 
}


int
kick_rack(string str)
{
    object *racks, tp;
    string msg;
    int i;

    if (!stringp(str))
        return 0;

    tp = this_player();

    if (str == "all racks")
       str = "racks";

    racks = FIND_STR_IN_ARR(str, all_inventory(this_object()));

    if (!sizeof(racks)) {
        notify_fail("Kick what rack?\n");
        return 0;
    }

    msg = COMPOSITE_DEAD(racks);
    tp->catch_msg("You kick " + msg + ".\n");
    tell_room(this_object(), QCTNAME(tp) + " kicks " + msg + ".\n", tp);

    for (i = 0; i < sizeof(racks); i++)
        racks[i]->kick_rack();

    return 1;
}


int
rack(string str)
{
    object tp, *obs, ob, *weapons, *armour, *misc;
    int i, size, forced, ww;
    string v, *names;

    tp = TP;
    obs = all_inventory(tp);
    if (str == "miscellaneous")
        str = "misc";
    if (str && str != "" && str != "misc")
        obs = FIND_STR_IN_ARR(str, obs);

    v = query_verb();
    forced = (v == "frack");
    ww = (v[strlen(v)-1] == '!');

    size = sizeof(obs);
    weapons = ({ });
    armour = ({ });
    misc = ({ });
    for (i = 0; i < size; i++)
    {
        ob = obs[i];
     names = ob->query_names();
     if (!ob->query_prop(OBJ_I_VALUE) ||
            ob->query_prop(OBJ_M_NO_DROP) ||
            ob->query_prop(OBJ_M_NO_GIVE) ||
            member("coin", names) ||
            ob->query_prop(LIVE_I_IS))
           continue;

        if (!forced && ob->query_keep())
         continue;

        if (!ww && (ob->query_worn() || ob->query_wielded()))
            continue;

        if (ob->query_prop(CONT_I_IN) &&
            sizeof(all_inventory(ob)))
            continue;

        if (member("weapon", names)) {
            if (str != "misc") {
                if (!ob->move(weapon_rack))
                    weapons += ({ ob });
            }
        }
        else if (member("armour", names)) {
            if (str != "misc") {
                if (!ob->move(armour_rack))
                    armour += ({ ob });
            }
        }
        else {
            if (!ob->move(misc_rack))
                misc += ({ ob });
        }
    }

    if (!sizeof(weapons + armour + misc))
    {
        NF("Nothing racked.\n");
        return 0;
    }

    if (sizeof(weapons))
    {
        str = COMPOSITE_DEAD(weapons);
        write("You put " + str + " in the weapons rack.\n");
        say(QCTNAME(tp) + " put " + str + " in the weapons rack.\n");
    }

    if (sizeof(armour))
    {
        str = COMPOSITE_DEAD(armour);
        write("You put " + str + " in the armour rack.\n");
        say(QCTNAME(tp) + " put " + str + " in the armour rack.\n");
    }

    if (sizeof(misc))
    {
        str = COMPOSITE_DEAD(misc);
        write("You put " + str + " in the miscellaneous equipment rack.\n");
        say(QCTNAME(tp) + " put " + str +
            " in the miscellaneous equipment rack.\n");
    }

    return 1;
}


int
query_special_item(object item)
{
    return stringp(special_items[MASTER_OB(item)]); 
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
 * Arguments    : none
 * Returns      : nothing
*/
private void
format_special_list()
{
    string * weapons, * armours, * misc, * errors;
    object item;
    
    weapons = ({ });
    armours = ({ });
    misc = ({ });
    errors = ({ });
    foreach (string filename : m_indices(special_items))
    {
        // Go through each specials item, and load it to
        // properly categorize it.
        if (LOAD_ERR(filename))
        {
            // If it doesn't load properly, report it as an
            // error object
            errors += ({ special_items[filename] });
            continue;
        }
        
        item = find_object(filename);
        if (IS_WEAPON_OBJECT(item))
        {
            weapons += ({ special_items[filename] });
        }
        else if (IS_ARMOUR_OBJECT(item))
        {
            armours += ({ special_items[filename] });
        }
        else
        {
            misc += ({ special_items[filename] });
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
    
    if (sizeof(misc) > 0)
    {      
        write(sprintf("%|70s\n", "Misc"));
        write(sprintf("%|70s\n", "===="));        
        write(format_two_columns(sort_array(misc)));
    }
    
    if (sizeof(errors) > 0)
    {
        write("These items contain errors. Please report it to the "
            + "guildmaster.\n");
        write(format_two_columns(sort_array(errors)));
    }
}

/*
 *  Function:     special
 *  Description:  An action function allowing Calians to note 
 *                an item as especially important in the racks,
 *                remove such an item from the list, or show a
 *                list of all of them. 
 */ 
int
special(string str)
{
    object tp = this_player(); 
    string *tmp, fn;
    int i; 
    object *items;

    if (stringp(str)) {
        if (str == "list") {
            if (!sizeof(tmp = m_values(special_items))) {
                tell_object(tp, "There are no special items " +
                            "registered.\n"); 
                return 1; 
            } 
 
            tp->catch_msg("The following types of item are listed " +
                          "as especially important for the racks: \n\n");
            format_special_list();
            return 1; 
        } 
        tmp = explode(str, " "); 
        if (sizeof(tmp) > 1) { 
            if (!COUNCIL_CODE->is_council_member(tp->query_real_name()) &&
                !SECURITY->valid_write(file_name(this_object()), tp,
                                       "write_file")) { 
                notify_fail("You do not have the authority to do " +
                            "that.\n"); 
                return 0; 
            } 
            if (tmp[0] == "add") {
                if (m_sizeof(special_items) >= MAX_SPECIAL_RACK_ITEMS) {
                    notify_fail("The list is full, a listed item has to " +
                                "be removed if you want to add another.\n"); 
                    return 0; 
                } 
                str = implode(tmp[1 ..], " "); 
                items = FIND_STR_IN_ARR(str, all_inventory(tp)); 
                if (sizeof(items) > 1) {
                    notify_fail("Please refer to one specific item " +
                                "in your inventory.\n"); 
                    return 0; 
                } 
                else if (!sizeof(items)) {
                    notify_fail("There is no such item in your " +
                                "inventory.\n"); 
                    return 0; 
                } 
                if (stringp(special_items[fn = MASTER_OB(items[0])])) {
                    notify_fail("That item is already in the list!\n"); 
                    return 0; 
                } 
                special_items += ([ fn : items[0]->short() ]); 
                save_object(RACK_SPECIALS); 
                tell_object(tp, "Ok.\n"); 
                return 1; 
            } 
            else if (tmp[0] == "remove") {
                str = implode(tmp[1 ..], " "); 
                if (!sizeof(tmp = m_indexes(special_items))) {
                    notify_fail("There are no items in the list.\n"); 
                    return 0; 
                }  
                items = FIND_STR_IN_ARR(str, all_inventory(tp)); 
                if (sizeof(items) > 1) { 
                    notify_fail("That refers to more than one item " +
                                "in your inventory, you have to " +
                                "refer to one in particular.\n"); 
                    return 0; 
                } 
                if (sizeof(items) == 1) {
                    if (stringp(special_items[fn = MASTER_OB(items[0])])) {
                        special_items = m_delete(special_items, fn); 
                        tell_object(tp, "Ok.\n"); 
                        save_object(RACK_SPECIALS); 
                        return 1; 
                    } 
                    notify_fail("There is no such item in the list.\n"); 
                    return 0; 
                } 
                tmp = m_indexes(special_items); 
                for (i = 0; i < sizeof(tmp); i++) { 
                    if (special_items[tmp[i]] == str) { 
                        special_items = m_delete(special_items, tmp[i]); 
                        save_object(RACK_SPECIALS); 
                        tell_object(tp, "Ok.\n"); 
                        return 1; 
                    } 
                } 
                notify_fail("There is no such item in the list, are " +
                            "you sure you referred to it by its full " +
                            "name as listed?\n"); 
                return 0; 
            } 
        } 
        notify_fail("Syntax: special add  <item>\n" + 
                    "        special remove <item>\n" + 
                    "        special list.\n");
        return 0; 
    }

    tp->more(read_file(CRPALACE_TEXTS + "special_items")); 

    return 1;
}


void 
init()
{
    ::init(); 
    add_action(special, "special"); 
    add_action(kick_rack, "kick");
    add_action(rack, "rack");
    add_action(rack, "frack");
    add_action(rack, "rack!");
    add_action(rack, "frack!");
}

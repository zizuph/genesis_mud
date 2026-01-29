
/* 
   Coded by Glykron & Maniac
   These are racks to keep things tidy, they do not have a save
   feature. They do handle the rack points system for the calian 
   rack club though. 

   History:
          23-sep-2007 For wizards, make a separate log     Mercade
           2/12/02    Added indication of recoverability   Maniac
           7/8/02     fixed special item logging bug       Maniac
           8/7/02     added special item logging           Maniac
           14/6/2000  added "special item" feature         Maniac
           27/8/99    appraise handling more efficient,
                      rack points system updated           Maniac
           2/10/98    Fixed rack points bug                Maniac
          25/11/97    updated enter/leave handling         Maniac
          26/4/97     armours handled properly now for
                      rack club                            Maniac
          13/11/96    rack points system smartened up      Maniac
           9/11/96    rack points system added             Maniac
           13/9/96    kick_rack functionality added        Maniac
           20/6/96    made more efficient                  Maniac
             5/9/95   modified                             Maniac
             7/8/95   Cheat check added                    Maniac
            20.3.95   LANG_THESHORT used for shorts        Maniac
*/

#pragma save_binary

#include <macros.h>
#include <config.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <wa_types.h>
#include <std.h>
#include "defs.h"
#include CALIAN_HEADER

#define CALIAN_RACK_ROOM (CRPALACE_LIGHT_ROOMS + "rack")

inherit "/std/container";

// Prototypes
public int          list_cmd(string arg);
public void         print_list(object for_obj, object *obarr);

// Global Variables
object this;

void
remove_object()
{
    int x;

    if (objectp(this_interactive()))
       log_file("rack", ctime(time()) + ": " + 
                this_interactive()->query_real_name() + " removed rack.\n"); 

    ::remove_object();
}

void
create_rack()
{
}

nomask void
create_container()
{
    set_name("rack");
    add_prop(OBJ_M_NO_GET, "It is attached to the wall.\n");
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);

    this = THIS;
    create_rack();
    seteuid(getuid()); 
}

int
fits(object ob)
{
    return 1;
}


private void
log_racked_special_item(object who, object what)
{
    (CRPALACE_OBJECTS + "rack_log_book")->update_log_book(
        ctime(time()) + " " + capitalize(who->query_real_name()) +
	" racked " + LANG_ASHORT(what) + (what->check_recoverable() ? 
        "!\n" : ".\n"), who->query_wiz_level()); 
}


private void
log_borrowed_special_item(object who, object what)
{
    (CRPALACE_OBJECTS + "rack_log_book")->update_log_book(
        capitalize(who->query_real_name()) + " borrowed " + 
        LANG_ASHORT(what) + (what->check_recoverable() ? 
        "!\n" : ".\n"), who->query_wiz_level()); 
}


private void
rack_points_add(object ob, object from)
{
    int pen, tohit, ac, avg, pt, sk, si;

    if (!objectp(ob) || !interactive(from)) 
        return;

    if (!ob->check_recoverable() && 
        ARMAGEDDON->shutdown_active())
        return;

    if (si = CALIAN_RACK_ROOM->query_special_item(ob)) 
    { 
        log_racked_special_item(from, ob); 
    } 

    if ((pen = ob->query_pen()) && 
        (tohit = ob->query_hit())) { 
        if ((ob->query_wt() != W_SWORD) && (ob->query_wt() != W_POLEARM))  
             return;

        if (RACK_WEP_OK(tohit, pen)) { 
            avg = from->query_average_stat(); 
            avg = F_RACK_AVG_STAT(avg); 

            if (ob->query_prop(OBJ_I_IS_MAGIC_WEAPON)) { 
                from->set_skill(CALIAN_RACK_POINTS, 
                    from->query_skill(CALIAN_RACK_POINTS) + 
                    F_RACK_POINTS_WEP(tohit, pen, avg) * 
                   (si ? 6 : 2)); 
            } 
            else {
                from->set_skill(CALIAN_RACK_POINTS, 
                    from->query_skill(CALIAN_RACK_POINTS) + 
                    F_RACK_POINTS_WEP(tohit, pen, avg)); 
            } 
            present(MEDALLION_ID, from)->update_tint(from); 
        } 
        return;
    } 

    if (ac = ob->query_ac()) { 

        if (RACK_ARM_OK(ac))  { 
            avg = from->query_average_stat(); 
            avg = F_RACK_AVG_STAT(avg); 

            if (ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR)) { 
                from->set_skill(CALIAN_RACK_POINTS, 
                    from->query_skill(CALIAN_RACK_POINTS) + 
                    F_RACK_POINTS_ARM(ac, avg) * 
                   (si ? 6 : 2)); 
            } 
            else {
                from->set_skill(CALIAN_RACK_POINTS, 
                    from->query_skill(CALIAN_RACK_POINTS) + 
                    F_RACK_POINTS_ARM(ac, avg)); 
            } 
            present(MEDALLION_ID, from)->update_tint(from); 
        } 
        return;
    } 
}


private void
rack_points_remove(object ob, object to)
{
    int pen, tohit, ac, avg, pt, sk, si;

    if (!objectp(ob) || !interactive(to)) 
        return;

    if (!ob->check_recoverable() && 
        ARMAGEDDON->shutdown_active())
        return;

    if (si = CALIAN_RACK_ROOM->query_special_item(ob)) 
    { 
        log_borrowed_special_item(to, ob); 
    } 

    if ((pen = ob->query_pen()) && 
        (tohit = ob->query_hit())) { 
        if ((ob->query_wt() != W_SWORD) && (ob->query_wt() != W_POLEARM))  
             return;

        if (RACK_WEP_OK(tohit, pen)) { 
            avg = to->query_average_stat(); 
            avg = F_RACK_AVG_STAT(avg); 


            if (ob->query_prop(OBJ_I_IS_MAGIC_WEAPON)) { 

                to->set_skill(CALIAN_RACK_POINTS, 
                    to->query_skill(CALIAN_RACK_POINTS) -
                    F_RACK_POINTS_WEP(tohit, pen, avg) * 
                   (si ? 6 : 2)); 
            } 
            else {
                to->set_skill(CALIAN_RACK_POINTS, 
                    to->query_skill(CALIAN_RACK_POINTS) - 
                    F_RACK_POINTS_WEP(tohit, pen, avg)); 
            } 
            present(MEDALLION_ID, to)->update_tint(to); 
        } 
        return;
    } 

    if (ac = ob->query_ac()) { 
        if (RACK_ARM_OK(ac))  { 
            avg = to->query_average_stat(); 
            avg = F_RACK_AVG_STAT(avg); 

            if (ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR)) { 

                to->set_skill(CALIAN_RACK_POINTS, 
                    to->query_skill(CALIAN_RACK_POINTS) -
                    F_RACK_POINTS_ARM(ac, avg) * 
                   (si ? 6 : 2)); 
            } 
            else {
                to->set_skill(CALIAN_RACK_POINTS, 
                    to->query_skill(CALIAN_RACK_POINTS) - 
                    F_RACK_POINTS_ARM(ac, avg)); 
            } 
            present(MEDALLION_ID, to)->update_tint(to); 
        } 
        return;
    } 
} 


/* 
 * Function: prevent_enter
 * Stops an object being put in a rack if it doesn't fit, by returning 1;  
 */ 
int
prevent_enter(object ob)
{
    if (fits(ob)) 
        return 0;

    write(capitalize(LANG_THESHORT(ob)) + " won't fit in " + 
          LANG_THESHORT(this_object()) + ".\n");  
    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    rack_points_add(ob, from); 
}


void
leave_inv(object ob, object to)
{
    string str;

    ::leave_inv(ob, to);

    if (objectp(to)) {
        if ((stringp(str = geteuid(to)) && str != geteuid() &&
             SECURITY->query_wiz_rank(str)) ||
            (stringp(str = geteuid(this_player())) && 
             SECURITY->query_wiz_rank(str) && 
             str != geteuid()))
            log_file("rack_take", "Item: " + ob->short() + 
                              " moved by wizard, euid causing move: " + 
                               str + ".\n"); 

        if (to->query_npc() || (living(to) && 
            to->query_guild_name_occ() != "Calian warrior's guild")) 
                log_file("rack_take", "Item: " + ob->short() +
                         ", moved to non-Calian: " + to->query_real_name() +  
                         " (" + file_name(to) + ").\n"); 
    }
    rack_points_remove(ob, to); 
}


int
appraise(string str)
{
    mixed * obs;
    object ob;
    int place;
    
    if (parse_command(str, this_player(), "[the] %i", obs))
    {
        // If the item is on the player, allow the normal appraise
        // to continue.
        return 0;
    }
    else if (parse_command(str, this_object(), 
                           "[the] %i [in] [rack]", obs))
    {
        switch (obs[0])
        {
        case 1:
            // This matched one item. Go ahead and just appraise it
            ob = obs[1];
            break;
        case 0:
            // This matched multiple items. give a message that the player
            // needs to be more specific
            notify_fail("It's difficult to appraise more than one item at "
                      + "a time.\n");
            return 0;
            
        default:
            // Specified "first", "second", etc.
            place = obs[0] * -1;
            if (sizeof(obs) <=  place)
            {
                return 0;
            }
            ob = obs[place];
        }
        this_player()->catch_msg("You peer at " + LANG_THESHORT(ob) + 
                      " inside " + LANG_THESHORT(this_object()) + 
                      ".\n");
        ob->appraise_object();
        return 1;        
    }
    
    return 0;
}


int
reject_object(object ob, object env)
{
    if (ob->move(env) == 0) {  
        tell_room(env, 
                  capitalize(LANG_THESHORT(ob)) + " falls off " + 
                  LANG_THESHORT(this_object()) + ".\n"); 
        return 1; 
    } 
    return 0; 
}


void
recoverable_check(object ob, object env, object tp)
{
    if (ob->check_recoverable()) 
        return;

    if (reject_object(ob, env))
        rack_points_remove(ob, tp); 
}


void
kick_rack()
{
    map(all_inventory(this_object()), 
         &recoverable_check(,environment(this_object()), this_player())); 
}


void
init()
{
    ::init();
    add_action(appraise, "appraise");
    add_action(list_cmd, "list");
}

public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell("You can use <list " + this_object()->short()
                      + "> to see the contents of the rack in a list.\n"
                      + "You can also use <list> to filter the rack. "
                      + "eg. <list swords>\n\n");
    ::describe_contents(for_obj, obarr);
}

public int
list_cmd(string arg)
{
    mixed * matches;
    object  rack;
    
    if (!arg)
    {
        notify_fail("List which rack or list what objects?\n");
        return 0;
    }
    
    // See if the user typed something like "list weapon rack"
    if (parse_command(arg, all_inventory(environment(this_player())),
                      "[the] %i", matches))
    {
        if (matches[0] == 1 && matches[1] == this_object())
        {
            // Simply get the first object in the array
            rack = matches[1];
            print_list(this_player(), all_inventory(rack));
            return 1;
        }
        else if (matches[0] < 0 
                 && sizeof(matches) > (matches[0] * -1)
                 && matches[(matches[0] * -1)] == this_object())
        {
            // player used something like "first, second, third"
            rack = matches[(matches[0] * -1)];
            print_list(this_player(), all_inventory(rack));
            return 1;
        }
    }

    // Now see if the user is trying to list something inside the rack
    if (parse_command(arg, all_inventory(this_object()), 
                      "[the] %i", matches))
    {
        if (matches[0] == 0)
        {
            // parse matched multiple objects
            print_list(this_player(), matches[1..]);
            return 1;
        }
        else if (matches[0] == 1)
        {
            // Simply get the first object in the array
            print_list(this_player(), ({ matches[1] }));
            return 1;
        }
        else if (matches[0] < 0 
                 && sizeof(matches) > (matches[0] * -1))
        {
            // player used something like "first, second, third"
            print_list(this_player(), ({ matches[(matches[0] * -1)] }));
            return 1;
        }
    }
    
    notify_fail("List which rack or list what objects?\n");
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

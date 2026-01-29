
/* 
   Coded by Glykron & Maniac
   These are racks to keep things tidy, they do not have a save
   feature. They do handle the rack points system for the calian 
   rack club though. 

   History:
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

#define CALIAN_RACK_ROOM (GLYKRON_LIGHT_ROOMS + "rack")

inherit "/std/container";

object this;

void
remove_object()
{
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
rack_points_add(object ob, object from)
{
    int pen, tohit, ac, avg, pt, sk;

    if (!objectp(ob) || !interactive(from)) 
        return;

    if (!ob->check_recoverable() && 
        ARMAGEDDON->shutdown_active())
        return;

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
                   (CALIAN_RACK_ROOM->query_special_item(ob) ? 6 : 2)); 
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
                   (CALIAN_RACK_ROOM->query_special_item(ob) ? 6 : 2)); 
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
    int pen, tohit, ac, avg, pt, sk;

    if (!objectp(ob) || !interactive(to)) 
        return;

    if (!ob->check_recoverable() && 
        ARMAGEDDON->shutdown_active())
        return;

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
                   (CALIAN_RACK_ROOM->query_special_item(ob) ? 6 : 2)); 
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
                   (CALIAN_RACK_ROOM->query_special_item(ob) ? 6 : 2)); 
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
    object *obs, ob;

    if (sizeof(obs = FIND_STR_IN_OBJECT(str, this))) {
        ob = obs[0];
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
}


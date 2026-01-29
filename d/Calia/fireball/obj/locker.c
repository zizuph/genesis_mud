
/*
 *  /d/Calia/fireball/obj/locker.c  
 *
 *  A clonable locker for storing the non-autoloading belongings 
 *  of Fireball players. Has a timer lasting 30 minutes by 
 *  which time the player must have re-claimed the items  
 *  or they will be lost. 
 *   
 *  Coded by Maniac@Genesis, October 1997
 *
 *  Revised by Maniac 28/4/99 
 * 
 *  Copyright (C) Miguel Leith 1997 
 */ 

#include "defs.h"
#include FIREBALL_HEADER

inherit "/std/container"; 

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <files.h>

int expire_alarm;
string owner;  

void
create_container()
{
    set_name("locker"); 
    set_adj("fireball"); 
    set_long("A fireball locker.\n"); 
    add_prop(CONT_I_WEIGHT, 10000); 
    add_prop(CONT_I_MAX_WEIGHT, 400000); 
    add_prop(CONT_I_VOLUME, 10000); 
    add_prop(CONT_I_MAX_VOLUME, 400000); 
    add_prop(OBJ_M_NO_GET, 1); 
}


int
lockable(object o)
{
    return !(stringp(o->query_auto_load()) || 
             o->query_prop(OBJ_M_NO_DROP)); 
}


private void
warn_owner() 
{
    object pl; 

    if (objectp(pl = find_player(owner))) {
        tell_object(pl, "\nYou remember that your locker time " +
                    "at the Firedrome will expire quite soon. " +
                    "You'd better collect your stuff or book " +
                    "another game fast.\n\n"); 
        expire_alarm = set_alarm(200.0, 0.0, remove_object); 
        return; 
    } 
    remove_object(); 
}


void
reset_locker_time()
{
    if (expire_alarm) 
        remove_alarm(expire_alarm);
    expire_alarm = set_alarm(1600.0, 0.0, warn_owner); 
}


int
is_container(object ob)
{
    return IS_CONTAINER_OBJECT(ob);  
}


void
store(object player) 
{
    object *moved, *obs, *tmp; 
    int i, s, cannot_pass;
    string os; 

    owner = player->query_real_name(); 
    cannot_pass = 0; 
    obs = all_inventory(player); 
    if (s = sizeof(moved = filter(obs, is_container))) {   
        obs -= moved; 
        /* The lockable contents of unlockable containers should be
           freed up. */ 
        tmp = ({ }); 
        for (i = 0; i < s; i++) {  
            if (!lockable(moved[i]) || moved[i]->move(this_object())) { 
                if (sizeof(filter(deep_inventory(moved[i]), lockable))) 
                    tmp += ({ moved[i] });
                else 
                    moved[i] = 0; 
            } 
        } 
        moved -= ({ 0 });  

        if (sizeof(tmp)) {
            moved -= tmp; 
            player->catch_msg("A guard tells you that you will " +
                              "have to free up the lockable contents of " + 
                              COMPOSITE_DEAD(tmp) + ".\n");
            cannot_pass = 1; 
        }  
    }  

    if (s = sizeof(obs = filter(obs, lockable))) {
        tmp = ({ }); 
        for (i = 0; i < s; i++) 
            if (obs[i]->move(this_object()))
                tmp += ({ obs[i] }); 

        if (sizeof(tmp)) { 
            obs -= tmp; 
            player->catch_msg("A guard tells you that you will have to " +
                    "free up " + COMPOSITE_DEAD(tmp) + " before you may " +
                    "pass.\n"); 
            cannot_pass = 1; 
        } 

        if (sizeof(obs)) 
            moved += obs; 
    } 

    if (sizeof(moved)) {
        reset_locker_time(); 
        os = COMPOSITE_DEAD(moved);  
        player->catch_msg("You store " + os + " in a locker.\n"); 
        tell_room(environment(player), QCTNAME(player) + 
                  " stores " + os + " in a locker.\n", player); 

        tell_object(player, "Your locker time will expire in half an hour, " + 
                            "you must <lclaim> your stuff before then or " +
                            "lose it.\n"); 
        return; 
    } 

    if (!cannot_pass) 
        tell_object(player, "You do not have anything that needs to be put " +
                            "in a locker.\n");
}


void
claim(object player)
{
    int s, i; 
    object *o, *tmp;  
    string os;

    s = sizeof(o = all_inventory(this_object())); 

    tmp = ({ }); 
    for (i = 0; i < s; i++) 
       if (o[i]->move(player))
           tmp += ({ o[i] }); 

    o -= tmp;  
    if (sizeof(o)) { 
        os = COMPOSITE_DEAD(o);  
        player->catch_msg("You claim " + os +  " from a locker.\n"); 
        tell_room(environment(player), QCTNAME(player) + 
                  " claims " + os + " from a locker.\n", 
                  player); 
    } 

    if (sizeof(tmp)) { 
        player->catch_msg("You will have to free up some space for " + 
                COMPOSITE_DEAD(tmp) + " and <lclaim> again.\n"); 
        return;
    } 

    remove_object(); 
}

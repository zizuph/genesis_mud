
/*
   With this net one can "automatically" catch corpses of sea creatures 
   before they sink.  

   Coded by Maniac, 21-24/9/96

   Increased max weight and volume so it can catch some bigger
   creatures - Arman, 2021.
*/ 

#pragma save_binary
#pragma strict_types

inherit "/std/container"; 
inherit "/lib/keep";

#include <stdproperties.h> 
#include <language.h>
#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Calia/sys/water.h"

#include "defs.h"


int carve_alarm; 

void
create_container()
{
    set_name("net"); 
    add_name(SEA_NET_ID); 
    set_adj("fishing"); 

    set_long("A fishing net. This will allow you to react quickly " +
             "after killing a sea creature and <net> it before it " +
             "sinks. You can also <carve> up dead creatures " +
             "that you have netted.\n"); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 1000); 
    add_prop(CONT_I_MAX_WEIGHT, 1500000); 
    add_prop(CONT_I_VOLUME, 1000); 
    add_prop(CONT_I_MAX_VOLUME, 1500000); 
    add_prop(OBJ_I_VALUE, 20); 
}


void
fall_out(object ob)
{
    object env; 

    if (objectp(ob) && objectp(present(ob, this_object())))  {  
        env = environment(this_object()); 
        if (living(env)) {  
            env->catch_msg(capitalize(LANG_THESHORT(ob)) + 
                 ((ob->num_heap() < 2) ? " falls " : " fall ") + 
                 "through your " + short() + ".\n"); 
            ob->move(environment(env)); 
            return;
        } 
        if (env->query_prop(ROOM_I_IS)) { 
            tell_room(capitalize(LANG_THESHORT(ob)) + 
                 ((ob->num_heap() < 2) ? " falls " : " fall ") + 
                    "through the " + short() + ".\n"); 
            ob->move(env); 
            return;
        } 
   } 
}


/* Small stuff falls out! */ 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if ((ob->query_prop(OBJ_I_VOLUME) < 5) ||   
        (ob->query_prop(HEAP_I_IS) && 
         (ob->query_prop(HEAP_I_UNIT_VOLUME) < 5))) 
        set_alarm(1.0, 0.0, &fall_out(ob)); 
}


/* 
 * This function acts dually as an action function 
 * and a directly called function from sea_creature 
 * code 
 */ 
varargs int
do_net(mixed arg, object player)
{
    int s;
    object tp, *obs, ob;

    if (!stringp(arg) && !objectp(arg)) { 
        notify_fail("Net what?\n"); 
        return 0;
    } 

    if (!objectp(player)) 
        tp = this_player(); 
    else {  
        tp = player; 
        set_this_player(player); 
    } 

    if (!objectp(present(this_object(), tp))) { 
        notify_fail("You aren't carrying the " + short() + ".\n");  
        return 0;
    } 

    if (!UNDER_WATER(tp) && !IN_WATER(tp)) { 
        notify_fail("You may only net something when you " +
                    "are in a water room!\n"); 
        return 0;
    } 

    if (stringp(arg)) { 

        if (!(s = sizeof(obs = 
              FIND_STR_IN_ARR(arg, all_inventory(environment(tp)))))) {  
            notify_fail("Net what?\n"); 
            return 0;
        } 

        if (s > 1) { 
            notify_fail("You can't net more than one thing at once!\n"); 
            return 0;
        }

        ob = obs[0]; 

        if (!ob->id("corpse")) { 
            notify_fail("You may only net corpses with this " + 
                        short() + ".\n"); 
            return 0;
        } 
    } 
    else 
         ob = arg; 

    if (ob->move(this_object())) {  
        notify_fail("You try but fail to net the corpse! It must be too " +
                    "big for you!\n"); 
        return 0;
    }

    tp->catch_msg("You net " + LANG_THESHORT(ob) + ".\n"); 
    say(QCTNAME(tp) + " nets " + LANG_THESHORT(ob) + ".\n"); 
    return 1;
}

/*
 * Function:    alarmed_sea_creature_do_die_post_actions
 * Description: When a sea creature dies, players with nets get an opportunity
 *              to net the corpse before it drops down.
 */
public void
alarmed_sea_creature_do_die_post_actions(object killer)
{
    object * players = FILTER_PLAYER_OBJECTS(all_inventory(environment(killer)));
    object * corpses = FILTER_CORPSE_OBJECTS(all_inventory(environment(killer)));

    // Make sure that the killer gets first dibs to net the creature.
    players -= ({ killer });
    players = ({ killer }) + players; 

    // Each player has a chance to net all the corpses
    foreach (object player : players)
    {
        object net = present(SEA_NET_ID, player);
        if (!objectp(net))
        {
            continue;
        }
        object * remaining_corpses = ({ });
        foreach (object corpse : corpses)
        {
            if (!net->do_net(corpse, player))
            {
                remaining_corpses += ({ corpse });
            }
        }
        corpses = remaining_corpses;
    }
}

/*
 * Function:    alarmed_sea_creature_do_die_post_actions
 * Description: When a sea creature dies, players with nets get an opportunity
 *              to net the corpse before it drops down. This function is called
 *              by the sea creature's do_die function
 */
public void
sea_creature_do_die_post_actions(object killer)
{
    set_alarm(0.0, 0.0, &alarmed_sea_creature_do_die_post_actions(killer));
}


void
carve_now(object tp, object ob, mixed lf, int i, int total)
{
    int j, s;
    object p;

    if (!objectp(tp) || !objectp(ob) || !pointerp(lf)) 
        return;

    s = sizeof(lf); 

    if ((i < s) && lf[i][2] != 0) { 
        if ((lf[i][2] > 5) || (lf[i][2] == -1)) 
            lf[i][2] = 5; 
        for (j = 0; j < lf[i][2]; j++) { 
             p = clone_object(lf[i][0]);
             p->leftover_init(lf[i][1], ob->query_prop(CORPSE_S_RACE)); 
             if (p->move(this_object())) 
                 p->move(environment(tp)); 
        } 
        ob->remove_leftover(lf[i][1]); 
    } 

    i++; 
    if (i >= total) {  
        tp->catch_msg("You finish carving up " + LANG_THESHORT(ob) + ".\n"); 
        tell_room(environment(tp), QCTNAME(tp) + " finishes carving up " + 
                    LANG_THESHORT(ob) + ".\n", tp); 
        ob->remove_object();
        return;
    } 

    remove_alarm(carve_alarm); 
    carve_alarm = set_alarm(1.0, 0.0, &carve_now(tp, ob, lf, i, total)); 
}


int
can_carve(object ob)
{
    return (ob->query_dt() & W_SLASH); 
}


/* Carve up a corpse in the net */ 
int
do_carve(string str)
{
    object *objs, ob, tp, par; 
    int carve_time;
    mixed lf;

    tp = this_player(); 

    if (!objectp(present(this_object(), tp))) { 
        notify_fail("You aren't carrying the " + short() + ".\n");  
        return 0;
    } 

    if (objectp(tp->query_attack()))
    {
        notify_fail("But you are in the middle of a fight!\n"); 
        return 0;
    }

    if (!sizeof(filter(tp->query_weapon(-1), can_carve))) { 
        notify_fail("You aren't wielding anything that you can " +
                    "carve with.\n");  
        return 0;
    } 

    objs = filter(all_inventory(this_object()), &->id("corpse"));

    if (!sizeof(objs)) { 
        notify_fail("There are no corpses for you to carve in your " + 
                    short() + ".\n"); 
        return 0;
    } 

    if (stringp(str) && strlen(str)) { 
         objs = FIND_STR_IN_ARR(str, objs); 
         if (!sizeof(objs)) { 
             notify_fail("Carve what in the " + short() + "?\n"); 
             return 0;
         } 
         if (sizeof(objs) > 1) {  
              notify_fail("You can't carve more than one corpse at once!\n"); 
              return 0;
         } 
    } 

   ob = objs[0]; 
   lf = ob->query_leftover(); 
   if (!pointerp(lf)) 
       lf = ({ });
   lf = ({ }) + lf; 

   carve_time = sizeof(lf); 

   if (!carve_time)
       carve_time = 1; 

   tp->catch_msg("You start to carve up " + LANG_THESHORT(ob) + ".\n");   
   tell_room(environment(tp), QCTNAME(tp) + " starts to carve up " + 
            LANG_THESHORT(ob) + ".\n", tp); 

   seteuid(getuid());  

   remove_alarm(carve_alarm); 
   carve_alarm = set_alarm(1.0, 0.0, &carve_now(tp, ob, lf, 0, carve_time)); 
   par = clone_object("/std/paralyze"); 
   par->set_standard_paralyze("carving " + LANG_THESHORT(ob));  
   par->set_stop_fun("stop_carve"); 
   par->set_stop_object(this_object()); 
   par->set_remove_time(carve_time); 
   par->move(tp, 1); 

   return 1;
}


int
stop_carve(mixed arg)
{
    if (!objectp(arg)) 
        remove_alarm(carve_alarm); 
    return 0;
}


void
init()
{
    ::init(); 

    add_action(do_net, "net"); 
    add_action(do_net, "catch"); 
    add_action(do_carve, "carve"); 
}


/* 
 * Poison for overeatting Capanella. This is based on the skunkberry
 * poison from Earthsea, originally coded By Amelia in 1997 and cleaned
 * up by Ckrik. 
 *
 * Unlike the skunkberry herb, players do not combust, but they will
 * get sicker and sicker until they passout for a couple of min. When
 * they do passout and become unconcious, they can't move for a minimum
 * of 4 minutes. They will have some heath remaining but they better 
 * become uncouncious in a safe area because the fight won't stop.
 * - Finwe, March 2009
*/

#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <terrain.h>

#define COMBUST_THRESHOLD_START 20
#define DISCOMFORT_THRESHOLD 15
#define DAMAGE 60
#define EFFECT 40
#define CAP_POISON "_capanella_poison_"

private float interval = 30.0, p_time = 300.0, time_left;
private int is_combusting = 0, gas = 0, a_time, a_dam, recovery;
private int max_poisons = 2 + random(3);
private object victim;

public void
create_object()
{
    set_name(CAP_POISON);
    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
}

public int
query_gas()
{
    return gas;
}

public void
set_combusting(int i)
{
    is_combusting = i;
}

public int
query_combusting()
{
    return is_combusting;
}

public int
player_is_combusting()
{
    object *inv;
    int i;
    
    inv = all_inventory(victim);
    
    for(i = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->query_name() == CAP_POISON)
        {
            if(inv[i]->query_combusting())
            {
                return 1;
            }
        }
    }
    
    return 0;
}

public object
exists_fire()
{
//    int i;
//    object *inv;
//    
//    /* Right now we only account for torches */
//    inv = all_inventory(victim);
//    
//    for(i = 0; i < sizeof(inv); i++)
//    {
//        if(function_exists("create_object", inv[i]) == "/std/torch")
//        {
//            if(inv[i]->query_lit() != 0)
//            {
//                return inv[i];
//            }
//        }
//    }
    
    return 0;  
}

public void
destroy_poison()
{
    if(a_time)
    {
        remove_alarm(a_time);
    }
    
    a_time = 0;
    
    if(a_dam)
    {
        remove_alarm(a_dam);
    }
    
    a_dam = 0;  
    remove_object();
}

public void
kill_player()
{
    int i;
    object *inv, corpse, env;
    
    inv = all_inventory(victim);
    
    for(i = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->query_name() == CAP_POISON &&
            inv[i] != this_object())
        {
            inv[i]->destroy_poison();
        }
    }
    
    env = environment(victim);
    
    log_file("cap_combust_log", victim->query_name() + " passed out " +
        ctime(time()) + "\n");
//    victim->do_die(this_object());
//    corpse = present("corpse", env);
    clone_object(HERB_POISON + "stun.c")->move(victim, 1);
    
//    if(corpse)
//    {
//        corpse->set_short("charred " + corpse->short());
//    }
    
    victim = 0;
    destroy_poison();
}

public int
query_skunk_poisons()
{
    int i, count;
    object *inv;
    
    inv = all_inventory(victim);
    
    for(i = 0, count = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->query_name() == CAP_POISON)
        {
            count += inv[i]->query_gas();
        }
    }
    
    return count;
}

public void
start_combust()
{
    int i;
    object *inv;
    
    inv = all_inventory(victim);
    
    for(i = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->query_name() == CAP_POISON)
        {
            inv[i]->set_combusting(1);
        }
    }
}

public void
stop_combust()
{
    int i;
    object *inv;
    
    inv = all_inventory(victim);
    
    for(i = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->query_name() == CAP_POISON)
        {
            inv[i]->set_combusting(0);
        }
    }
}

public int
tell_damage_player()
{
    int j, gas_count, rand, res, dam;
    object fire, env = environment(victim);
    
    if(victim->query_ghost())
    {
        remove_object();
        return 1;
    }
    
    if(max_poisons >= query_skunk_poisons())
    {
        is_combusting = 1;
    }
    

    if(!is_combusting)
    {
        gas++;
        j = random(4);
        
        switch(j)
        {
            case 0:
                victim->catch_tell("You mind becomes clearer.");
                victim->add_mana(EFFECT);
            break;
            
            case 1:
                victim->catch_tell("You feel mentally stronger.");
                victim->add_mana(EFFECT);
            break;
            
            case 2:
                victim->catch_tell("You feel mentally recharged.");
                victim->add_mana(EFFECT);
            break;
            
            case 3:
                victim->add_mana(EFFECT);
                victim->catch_tell("You feel mentally refreshed.");
            break;
        }
        
        if(max_poisons >= query_skunk_poisons())
        {
            if(random(2))
            {
                victim->command("groan");
            } else 
            {
                victim->catch_tell("You double over in pain.\n");
            }
            is_combusting = 1;
        }
    } 
    else 
    {
        tell_room(environment(victim), QCTNAME(victim) + 
            " doubles over in pain.\n", victim);
        
        /* Deal fire damage here */
        /* Take into account resistence */
        res = 100 - victim->query_magic_res(MAGIC_I_RES_MAGIC);
        dam = ((DAMAGE + random(DAMAGE)) * res) / 100;
        
        /* If intoxicated, deal more damage ;) */
        dam = (dam * (victim->query_intoxicated() + 100)) / 100;
        
        switch(dam * 100 / victim->query_hp())
        {
            case 0:
                victim->catch_tell("You feel nauseous and sweaty.\n");
            break;
            
            case 1..10:
                victim->catch_tell("The shooting pains in your gut are bearable.\n");
            break;
            
            case 11..20:
                victim->catch_tell("You grit your teeth and supress an urge to cry out.\n");
            break;
            
            case 21..40:
                victim->catch_tell("You see the world spin around before your eyes.\n");
            break;
            
            default:
                victim->catch_tell("The world fades from your vision as you blackout.\n");
            break;
        }
        
        victim->reduce_hit_point(dam);
// We're not gonna kill them completely, we'll let the npcs do 
// that if necessary.
        if(victim->query_hp() <= 200)
        {
            tell_room(environment(victim), QCTNAME(victim) + " sways a few times then falls to the ground unconscious.\n", victim);
            
            /* We dont kill them, we just knock them out.
             * They better hope they passed out somewhere safe.
            */
            victim->catch_tell("You sway a few times as the world fades from view, then fall to the ground unconscious!\n");
//            kill_player();
            clone_object(HERB_SPECIALS + "stun.c")->move(victim, 1);
        }
    }
    
    return 1;
}

public int
remove_it(object to, object player)
{
    if(is_combusting)
    {
        if(query_skunk_poisons() != gas)
        {
            player->catch_tell("The pain in your gut subsides a little.\n");
        } 
        else 
        {
            player->catch_tell("The pain in your gut fades away.\n");
        }
    } 
    else 
    {
        player->catch_tell("Your gut feels a little better.\n");
    }
    
    to->destroy_poison();
    
    return 1;
}

public void
enter_env(object env, object from)
{
    object to = this_object();
    
    ::enter_env(env, from);
    
    if(interactive(env))
    {
        victim = env;
        
        if(player_is_combusting())
        {
            is_combusting = 1;
        }
        
        a_dam = set_alarm(3.0, interval, &tell_damage_player());
        a_time = set_alarm(p_time, -1.0, &remove_it(to, env));
        env->catch_tell("Your stomach feels a bit queasy.\n");
    }
}

public void
linkdeath_hook(object player, int linkdeath)
{
    mixed arr;
    
    /* Player linkdies. */
    if(linkdeath)
    {
        /* Access failure. */
        if(!a_time)
        {
            return;
        }
        
        /* Find out how much time there is left. */
        if(sizeof(arr = get_alarm(a_time)))
        {
            time_left = arr[2];
        } else {
            time_left = 0.0;
        }
        
        remove_alarm(a_time);
        a_time = 0;
        remove_alarm(a_dam);
        a_dam = 0;
    } else { /* Player revives from linkdeath. */
        if(!time_left)
        {
            return;
        }
        
        if(interval)
        {
            a_dam = set_alarm((interval / 2.0) + (rnd() * interval), 0.0,
                &tell_damage_player());
        }
        
        a_time = set_alarm(time_left, 0.0, &remove_it(this_object(),
            victim));
    }
}

public nomask string
query_auto_load()
{
    mixed arr;
    
    if(is_combusting)
    {
        if(!a_time)
        {
            if(!floatp(time_left))
            {
                time_left = 0.0;
            }
        } else if(sizeof(arr = get_alarm(a_time))) {
            time_left = arr[2];
        }
        
        return MASTER + ":" + ftoi(time_left) + "," +
            ftoi(interval) + "," + gas + "," + is_combusting;
    }
    
    return "";
}

public nomask void
init_arg(string arg)
{
    int index, dam;
    string *arglist;
    object to = this_object();
    
    /* Set that this is a recovery after someone quit */
    recovery = 1;
    
    arglist = explode(arg, ",");
    
    sscanf(arglist[0], "%f", p_time);
    sscanf(arglist[1], "%f", interval);
    sscanf(arglist[2], "%d", gas);
    sscanf(arglist[3], "%d", is_combusting);
    
    if(is_combusting)
    {
        write("You still feel sick to your stomach.\n");
    }
    
    a_dam = set_alarm(itof(random(5) + 3), interval, &tell_damage_player());
    a_time = set_alarm(p_time, -1.0, &remove_it(to, environment(to)));
}

public float
query_time_left()
{
    mixed arr;
    
    if(a_time && sizeof(arr = get_alarm(a_time)))
    {
        return arr[2];
    } else if(time_left){
        return time_left;
    }
    
    return 0.0;
}

public string
stat_object()
{
    return ::stat_object() +
        "Time        : " + ftoi(p_time) + "\n" +
        "Time left   : " + ftoi(query_time_left()) + "\n" +
        "Interval    : " + ftoi(interval) + "\n" +
        "Max Poisons : " + max_poisons + "\n" +
        "# of Poisons: " + query_skunk_poisons() + "\n" +
        "Combusting  : " + is_combusting + "\n";
}

/* coded by Amelia, 5/14/97
 *  pseudo poison, for skunk berries
 *  Earthsea herbs
 *  has healing effect, with undesirable social side-effects
 *
 *  Ckrik 9/2003 added a negative side effect if someone
 *  eats too many of the berries.  When one eats more than 2
 *  there is an increasing probability of spontaneous
 *  combustion in the victim resulting in massive fire damage
 *  especially if there is fire nearby, right now lighting
 *  a lamp or torch is dangerous.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <terrain.h>

#define COMBUST_THRESHOLD_START 20
#define DISCOMFORT_THRESHOLD 15
#define DAMAGE 50
#define EFFECT 30

private float interval = 30.0, p_time = 300.0, time_left;
private int is_combusting = 0, gas = 0, a_time, a_dam, recovery;
private object victim;

public void
create_object()
{
    set_name("_skunk_poison_");
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
        if(inv[i]->query_name() == "_skunk_poison_")
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
    object *fires = filter(all_inventory(victim), &->query_prop(OBJ_I_HAS_FIRE));

    if (sizeof(fires) > 0)
        return fires[0];

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
        if(inv[i]->query_name() == "_skunk_poison_" &&
            inv[i] != this_object())
        {
            inv[i]->destroy_poison();
        }
    }
    
    env = environment(victim);
    
    log_file("skunk_combust_log", victim->query_name() + " combusted " +
        ctime(time()) + "\n");
    victim->do_die(this_object());
    corpse = present("corpse", env);
    
    if(corpse)
    {
        corpse->set_short("charred " + corpse->short());
    }
    
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
        if(inv[i]->query_name() == "_skunk_poison_")
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
        if(inv[i]->query_name() == "_skunk_poison_")
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
        if(inv[i]->query_name() == "_skunk_poison_")
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
    
    gas_count = query_skunk_poisons();
    
    if(env->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
        env->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER ||
        env->terrain_includes_any(TERRAIN_UNDERWATER) ||
        env->query_prop(OBJ_I_CONTAIN_WATER) ||
        env->query_prop(OBJ_I_CONTAIN_WATER) == -1)
    {
        if(is_combusting)
        {
            tell_room(environment(victim),
            "The flames around " + QCTNAME(victim) + " go out.\n",
                victim);
            victim->catch_tell("The flames around you go out.\n");
            stop_combust();

            // evaporate 100ml of water if possible
            if(env->query_prop(OBJ_I_CONTAIN_WATER) > 1)
            {
                env->add_prop(OBJ_I_CONTAIN_WATER,
                    MAX(0, env->query_prop(OBJ_I_CONTAIN_WATER) - 100));
            }
        }
    } else if(gas_count > COMBUST_THRESHOLD_START && !is_combusting) {
        fire = exists_fire();
        
        if(fire)
        {
            /* Make the threshold lower when they have fire in inventory */
            j = -5;
            rand = 5;
        } else {
            j = 0;
            rand = 20;
        }
        
        /* At 20 + COMBUST_THRESHOLD_START gas clouds, 
        * combustion is 100% certain, the figure
        * goes down to 5 + COMBUST_THRESHOLD_START 
        * if a torch/lamp is lit in the player's 
        * inventory.
        */
        if(random(rand) < gas_count - (COMBUST_THRESHOLD_START + j))
        {
            start_combust();
            
            if(fire)
            {
                tell_room(environment(victim), 
                    QCTNAME(victim) + " suddenly bursts into flames " +
                    "as fire leaping from " + victim->query_possessive() +
                    " " + fire->query_short() +
                    " ignites air surrounding " + 
                    victim->query_objective() +
                    "!\n", victim);
                victim->catch_msg("Suddenly fire from your " + 
                    fire->query_short() + 
                    " ignite air surrounding you. " +
                    "You burst into flames!\n");
            } else {
                tell_room(environment(victim), 
                    QCTNAME(victim) + " suddenly bursts into flames.\n",
                    victim);
                victim->catch_tell("You suddenly feel a tremendous heat rise " +
                    "from within. You burst into flames!\n");
            }
        }
    }
    
    if(!is_combusting)
    {
        gas++;
        j = random(4);
        
        switch(j)
        {
            case 0:
                victim->command("$fart");
                    tell_room(environment(victim), "A smelly cloud fills the "+
                    "room.\n", victim);
                victim->catch_tell("A smelly cloud fills the room. ");
                victim->heal_hp(EFFECT);
            break;
            
            case 1:
                victim->command("$burp");
                victim->catch_tell("Your breath smells awful. ");
                victim->heal_hp(EFFECT);
            break;
            
            case 2:
                victim->catch_tell("You feel a little bilious. ");
                victim->heal_hp(EFFECT);
            break;
            
            case 3:
                victim->command("$fart");
                victim->heal_hp(EFFECT);
                victim->catch_tell("You feel the nutritional benefits of "+
                    "the herb going to work in your body. ");
            break;
        }
        
        if(gas_count >= DISCOMFORT_THRESHOLD)
        {
            if(random(2))
            {
                victim->command("$sweat");
            } else {
                victim->catch_tell("You are starting to feel rather " +
                    "hot and uncomfortable.\n");
            }
        } else {
            victim->catch_tell("\n");
        }
    } else {
        tell_room(environment(victim), QCTNAME(victim) + 
            " is engulfed in flames from within.\n", victim);
        
        /* Deal fire damage here */
        /* Take into account resistence */
        res = 100 - victim->query_magic_res(MAGIC_I_RES_FIRE);
        dam = ((DAMAGE + random(DAMAGE)) * res) / 100;
        
        /* If intoxicated, deal more damage...more flamable material ;) */
        dam = (dam * (victim->query_intoxicated() + 100)) / 100;
        
        switch(dam * 100 / victim->query_hp())
        {
            case 0:
                victim->catch_tell("The flames do not affect you at all.\n");
            break;
            
            case 1..10:
                victim->catch_tell("You are slightly singed by the enveloping " +
                    "flames.\n");
            break;
            
            case 11..20:
                victim->catch_tell("You are somewhat burned inside and out.\n");
            break;
            
            case 21..40:
                victim->catch_tell("You are severely burned inside and out.\n");
            break;
            
            default:
                victim->catch_tell("You burn to a crisp.\n");
            break;
        }
        
        victim->reduce_hit_point(dam);
        
        if(victim->query_hp() <= 0)
        {
            tell_room(environment(victim), QCTNAME(victim) + " combusts " +
                "into oblivion, leaving only a charred corpse.\n", victim);
            
            /* Fix me: remove corpse */
            victim->catch_tell("You combust into oblivion. You died!\n");
            kill_player();
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
            tell_room(environment(player), "The flames enveloping " +
                QCTNAME(player) + " die a little.\n", player);
            player->catch_tell("The flames enveloping you die a little.\n");
        } else {
            tell_room(environment(player), "The flames enveloping " +
                QCTNAME(player) + " die out.\n", player);
            player->catch_tell("The flames enveloping you die out.\n");
        }
    } else {
        player->catch_tell("The effects are wearing off.\n");
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
    
    // Why?
    return 0;
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
        write("You are still enveloped by flames.\n");
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
        "Time      : " + ftoi(p_time) + "\n" +
        "Time left : " + ftoi(query_time_left()) + "\n" +
        "Interval  : " + ftoi(interval) + "\n" +
        "Gas       : " + gas + "\n" +
        "Combusting: " + is_combusting + "\n";
}

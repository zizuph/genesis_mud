/* emerald_npc.c
 * This is an inheritable, base npc for the Emerald domain.
 * Using this file, npc's can
 *   - easily log deaths and kills
 *   - silently wield/wear equipment
 *   - make use of the "speak" command
 *   - restrict an npc's wandering to specific rooms w/in a directory
 *   - designate a specific path for npcs to walk
 *   - more easily use special attacks
 *
 * Example usage:
 * 
 * inherit "/d/Emerald/std/emerald_monster";
 * 
 * // prototypes for special attack functions 
 * int kick(object enemy);
 * int slap(object enemy);
 *
 * void create_emerald_monster()
 * {
 *   set_name("monster");
 *   set_stats(({ 10, 20, 10, 20, 10, 20 }));
 *   set_random_move(20);
 *   set_monster_home("/d/Emerald/telberin/o1");
 *   
 *   // add weapons and armour.  These will be wielded/worn
 *   // automatically when the npc is created.
 *   add_equipment(({ "/d/Emerald/telberin/arm/w_mithril_plate",
 *                    "/d/Emerald/telberin/wep/laensword" }));
 *   
 *   // log when the npc kills a player 
 *   log_my_kills("/d/Emerald/shiva/npc_kill_log");
 *   
 *   // log when a player kills the npc
 *   log_my_deaths("/d/Emerald/shiva/npc_death_log");
 *
 *   // set my responses to attempts to "speak" with the npc
 *   set_speak(({ "I heard a rumour that rangers really suck.",
 *                "Supposedly, vampires are far cooler." }));
 *
 *   // wander through four rooms
 *   set_restrain_path(({"/d/Emerald/telberin/o1", "/d/Emerald/telberin/o2",
 *                       "/d/Emerald/telberin/o3", "/d/Emerald/telberin/o4"}));
 *
 *   // 10% of my attacks should be special attacks
 *   set_special_attack_percent(10);
 *
 *   // execute the slap special 50% of the time
 *   add_special_attack(slap, 50, "slap");
 *   // execute the kick special 50% of the time
 *   add_special_attack(kick, 50, "kick");
 * }
 *
 * int slap(object enemy)
 * {
 *   ... special attack code ...
 *   return 1;
 * }
 *
 * int kick(object enemy)
 * {
 *   ... special attack code ...
 *   return 1;
 * }
 *
 * Note: Further features are planned
 *
 * Send questions, comments, etc. to Shiva
 */

inherit "/std/monster";
inherit "/d/Emerald/lib/equip";
inherit "/d/Emerald/lib/speak";
inherit "/d/Emerald/lib/special_attack";

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <formulas.h>

#define DEBUG_ON
#undef  DEBUG_ON

#define DEBUG_WHO find_player("shiva")
#include "/d/Emerald/sys/debug.h"

#define MY_NAME          query_name() + " (" + file_name(this_object()) + ")"
#define OTHERS_NAME(who) capitalize(who->query_real_name()) + \
                         " (St Avg " + who->query_average_stat() + ")"
#define LOG(file, msg) catch(write_file(file, sprintf("- %-=70s\n", \
                       msg + " " + ctime(time()))))

static int log_all_kills,
           log_all_deaths,
           next_direction,
           peace_heal_time = time(),
           peace_time = time(),
           last_con,
           last_intox;

static string  kill_file, 
               death_file, 
              *restrain_paths = ({}),
              *walk_rooms = ({});

public void
create_emerald_monster()
{
}

nomask void
create_monster()
{
    create_emerald_monster();
    last_con = query_stat(SS_CON);
    last_intox = query_intoxicated();
}

/* Function name: log_my_kills
 * Description:   designate that you wish to log when the npc kills
 *                a living.
 * Arguments:     string file            - the path to the log file
 *                (optional) int log_all - log all kills, not only
 *                                         players (default 0)
 */
varargs void log_my_kills(string file, int log_all)
{
    kill_file = file;
    log_all_kills = log_all;
}


/* Function name: log_my_deaths
 * Description:   designate that you wish to log when the npc is killed
 * Arguments:     string file            - the path to the log file
 *                (optional) int log_all - log all deaths, not only
 *                                         those caused by players (default 0)
 */
varargs void log_my_deaths(string file, int log_all)
{
    death_file = file;
    log_all_deaths = log_all;
}

/*
 * Function name: log_this_kill
 * Description:   This determines whether a particular kill by this npc
 *                should be logged.  Redefine this if you have turned kill
 *                logging on and you want control over whether individual kills
 *                are logged.
 * Arguments:     1. (object) The (former) living that has been killed.
 * Returns:       1 - log this kill
 *                0 - don't log this kill
 */
public int
log_this_kill(object killed)
{
    return 1;
}

/*
 * Function name: notify_you_killed_me
 * Description:   This is called from the combat system when this monster
 *                kills someone.
 * Arguments:     1. (object) What we killed
 */
public void
notify_you_killed_me(object ob)
{
    // If appropriate, log this kill
    if (strlen(kill_file) && ob && (log_all_kills || !ob->query_npc()) &&
        log_this_kill(ob))
    {
        setuid();
        seteuid(getuid());
    
        LOG(kill_file, MY_NAME + " killed " + OTHERS_NAME(ob));
    }
}

/*
 * Function name: log_this_deat
 * Description:   This determines whether a particular death should be logged.
 *                Redefine this if you have turned death logging on and you
 *                want control over whether individual deaths are logged.
 * Arguments:     1. (object) The object that killed us.
 * Returns:       1 - log this death
 *                0 - don't log this death
 */
public int
log_this_death(object killer)
{
    return 1;
}

/*
 * Function name: second_life
 * Description:   Used to handle any special routines when the npc dies.
 * Arguments:     1. (object) The object that killed us.
 * Returns:       1 - Don't actually remove the dead monster
 *                0 - Remove the dead monster.
 */
public int
second_life(object killer)
{
    // If appropriate, log the death.
    if (strlen(death_file) && (log_all_deaths || !killer->query_npc()) &&
        (killer || (killer = previous_object())) && log_this_death(killer))
    {
        setuid();
        seteuid(getuid());
  
        LOG(death_file, MY_NAME + " killed by " + OTHERS_NAME(killer));
    }

    return 0;
}

/* Function name: set_restrain_path
 * Description:   Restrict an npc's wandering to certain files/directories
 * Arguments:     string *paths - an array of strings which are the pathnames
 *                                of the rooms and directories to which the 
 *                                npc will be restricted.
 */  
public void
set_restrain_path(mixed paths)
{
    if (!pointerp(paths))
    {
        paths = ({ paths });
    }
  
    monster_restrain_path = paths;
}

/*
 * Function name: set_walk_directions
 * Description:   Designate a set of rooms through which this npc will attempt
 *                to walk, in order, back and forth.  This operates on the 
 *                random walk mechanism, so you'll need to enable that with
 *                set_random_move() as well.
 */
public void
set_walk_directions(string *rooms)
{
    walk_rooms = rooms;
}

/*
 * Function name: query_walk_directions
 * Description:   Get the list of rooms through which this npc is to walk, as
 *                indicated by set_walk_directions.
 */
public string *
query_walk_directions()
{
    return walk_rooms + ({});
}

/*
 * Function name: filter_exits
 * Description:   Determine which exits this npc can use when wandering.
 * Arguments:     1. (mixed *) All possible exits
 * Returns:       The exits this npc is allowed to use.
 */
mixed *filter_exits(mixed *exits)
{
    int i, j;
    mixed *possible_exits = ({ });
  
    if (!sizeof(exits))
    {
        return ({ });
    }
  
    // First, check to see if the npc has a specific walk path
    if (sizeof(walk_rooms))
    {
        for (i = 0; i < sizeof(exits); i += 3)
        {
            if (exits[i] == walk_rooms[next_direction])
            {
                return exits[i..(i + 2)];
            }
        }
   
        return ({ });
    }
  
    // Check the restrain path
    if (sizeof(monster_restrain_path))
    {
        for (i = 0; i < sizeof(monster_restrain_path); i++)
        {
            for (j = 0; j < sizeof(exits); j += 3)
            {
                if (exits[j] == monster_restrain_path[i] ||
                    wildmatch(monster_restrain_path[i] + "*", exits[j]))
                {
                    possible_exits += exits[j..(j + 2)];
                }
            }
        }
    
        return possible_exits;
    }

    return ::filter_exits(exits);
}

/*
 * Function name: monster_walk_end
 * Description:   For monsters with a set walk path, this notifies us that
 *                the monster has reached the end of the path.
 */
public void
monster_walk_end()
{
    int i;
    string *reverse_walk_rooms = ({ });
  
    next_direction = 1;

    // Reverse the path and start walking back  
    for (i = sizeof(walk_rooms) - 1; i > -1; i--)
    {
        reverse_walk_rooms += ({ walk_rooms[i] });
    }
  
    if (sizeof(walk_rooms) < 2)
    {
        next_direction = 0;
    }
    else
    {
        next_direction = 1;
    }
  
    walk_rooms = reverse_walk_rooms; 
} 

/*
 * Function name: set_next_walk_room
 * Description:   Indicate which room we should wander into next.
 * Arguments:     1. (object) The room the npc is in now
 */
public varargs void
set_next_walk_room(object current_room = environment())
{
    int index;
  
    if ((index = member_array(file_name(current_room), walk_rooms)) < 0)
    {
        return;
    }
  
    if (index == (sizeof(walk_rooms) - 1))
    {
        monster_walk_end();
        return;
    }
  
    next_direction = index + 1;
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    // Find out which room the npc should walk into next
    set_next_walk_room(env);
}


public void
init_living()
{
    ::init_living();
    init_speak();
}

public string
actor_id()
{
    return OB_NAME(this_player());
}

public string
query_combat_file()
{
    return "/d/Emerald/std/combat_object_monster";
}

public void
combat_heartbeat_started()
{
    query_hp(); // updates hps
    peace_time = 0;
}

public void
combat_heartbeat_stopped()
{
    if (peace_time == 0)
    {
        peace_time = time();
        peace_heal_time = time();
        last_con = query_stat(SS_CON);
        last_intox = query_intoxicated();;
    }
}

public void
calculate_hp()
{
    int n, con, intox;
    int tmpcon, tmpintox;

    ::calculate_hp();

    if (peace_time == 0)
    {
        return;
    }

    n = (time() - peace_heal_time) / F_INTERVAL_BETWEEN_HP_HEALING;
    if (n > 0)
    {
        con = query_stat(SS_CON);
        intox = query_intoxicated();
        tmpcon = (con + last_con) / 2;
        tmpintox = (intox + last_intox) / 2;

        peace_heal_time += n * F_INTERVAL_BETWEEN_HP_HEALING;
        heal_hp(n * F_HEAL_FORMULA(tmpcon, tmpintox) * 3);
        last_con = con;
        last_intox = intox;
    }
}

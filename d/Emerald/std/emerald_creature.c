/* emerald_creature.c
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
 * inherit "/d/Emerald/std/emerald_creature";
 * 
 * // prototypes for special attack functions 
 * int kick(object enemy);
 * int slap(object enemy);
 *
 * void create_emerald_creature()
 * {
 *   set_name("creature");
 *   set_stats(({ 10, 20, 10, 20, 10, 20 }));
 *   set_random_move(20);
 *   set_monster_home("/d/Emerald/telberin/o1");
 *   
 *   // log when the npc kills a player 
 *   log_my_kills("/d/Emerald/shiva/npc_kill_log");
 *   
 *   // log when a player kills the npc
 *   log_my_deaths("/d/Emerald/shiva/npc_death_log");
 *
 *   // set my responses to attempts to "speak" with the npc
 *   set_speak(({ "Awwk!",
 *                "Nevermore." }));
 *
 *   // wander through four rooms
 *   set_restrain_paths(({ "/d/Emerald/telberin/o1", "/d/Emerald/telberin/o2",
 *                         "/d/Emerald/telberin/o3", "/d/Emerald/telberin/o4" }));
 *
 *   // 10% of my attacks should be special attacks
 *   set_special_attack_percent(10);
 *
 *   // execute the slap special 50% of the time
 *   add_special_attack(peck, 50, "peck");
 *   // execute the kick special 50% of the time
 *   add_special_attack(wing_beat, 50, "beat");
 * }
 *
 * int peck(object enemy)
 * {
 *   ... special attack code ...
 *   return 1;
 * }
 *
 * int wing_beat(object enemy)
 * {
 *   ... special attack code ...
 *   return 1;
 * }
 *
 * Note: Further features are planned
 *
 * Send questions, comments, etc. to Shiva
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/d/Emerald/lib/speak";
inherit "/d/Emerald/lib/special_attack";
inherit "/d/Emerald/lib/equip";

#include <ss_types.h>
#include <formulas.h>

#pragma save_binary
#pragma strict_types

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


public void arm_me();

public void
create_emerald_creature() { }

nomask void
create_creature()
{
    create_emerald_creature();
    last_con = query_stat(SS_CON);
    last_intox = query_intoxicated();
}

/* Kept for backwards compatibility */
public void
arm_me()
{
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

// redefine this to return 0 when a kill shouldn't be logged.
int log_this_kill(object killed) { return 1; }

// log when kill someone, if appropriate.
void notify_you_killed_me(object ob)
{
  if (strlen(kill_file) && ob && (log_all_kills || !ob->query_npc()) &&
      log_this_kill(ob))
  {
    setuid();
    seteuid(getuid());
  
    LOG(kill_file, MY_NAME + " killed " + OTHERS_NAME(ob));
  }
}

// redefine this to return 0 when a death shouldn't be logged
int log_this_death(object killer) { return 1; }

// log when we die, if appropriate.
void do_die(object killer)
{
  if (strlen(death_file) && (log_all_deaths || !killer->query_npc()) &&
      (killer || (killer = previous_object())) && log_this_death(killer))
  {
    setuid();
    seteuid(getuid());

    LOG(death_file, MY_NAME + " was killed by " + OTHERS_NAME(killer));
  }

  ::do_die(killer);
}

/* Function name: set_restrain_paths
 * Description:   restrict an npc's wandering to certain files/directories
 * Arguments:     string *paths - an array of strings which are the pathnames
 *                                of the rooms and directories to which the 
*                                 npc will be restricted.
 */  
void set_restrain_path(string *paths)
{
  if (paths)
  {
    restrain_paths = paths;
  }
}

/* Function name: query_restrain_paths
 * Description:   get the rooms to which this npc's wandering is restrained
 * Returns:       an array of strings
 */
string *query_restrain_paths() { return restrain_paths; }

void set_walk_directions(string *rooms)
{
  walk_rooms = rooms;
}

string *query_walk_directions() { return walk_rooms; }

mixed *filter_exits(mixed *exits)
{
  int i, j;
  mixed *possible_exits = ({ });

  if (!sizeof(exits))
  {
    return ({ });
  }

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

  if (sizeof(restrain_paths))
  {
    for (i = 0; i < sizeof(restrain_paths); i++)
    {
      for (j = 0; j < sizeof(exits); j += 3)
      {
        if (exits[j] == restrain_paths[i] ||
            wildmatch(restrain_paths[i] + "*", exits[j]))
        {
          possible_exits += exits[i..(i + 2)];
        }
      }
    }

    return possible_exits;
  }

  return ::filter_exits(exits);
}

void monster_walk_end()
{
  int i;
  string *reverse_walk_rooms = ({ });

  next_direction = 1;

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

void set_next_walk_room(object current_room)
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

void enter_env(object env, object from)
{
  ::enter_env(env, from);

  set_next_walk_room(env);
}

public void
init_living()
{
    ::init_living();
    init_speak();
}

public string
query_combat_file()
{
    return "/d/Emerald/std/combat_object_creature";
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

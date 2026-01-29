/* /d/Earthsea/std/monster.c
 * This is an inheritable, base npc for the Earthsea domain.
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
 * inherit "/d/Earthsea/std/earthsea_monster";
 * 
 * // prototypes for special attack functions 
 * int kick(object enemy);
 * int slap(object enemy);
 *
 * void create_earthsea_monster()
 * {
 *   set_name("monster");
 *   set_stats(({ 10, 20, 10, 20, 10, 20 }));
 *   set_random_move(20);
 *   set_monster_home("/d/Earthsea/telberin/o1");
 *   
 *   // add weapons and armour.  These will be wielded/worn
 *   // automatically when the npc is first moved.
 *   add_equipment(({ "/d/Earthsea/telberin/arm/w_mithril_plate",
 *                    "/d/Earthsea/telberin/wep/laensword" }));
 *   
 *   // log when the npc kills a player 
 *   log_my_kills("/d/Earthsea/shiva/npc_kill_log");
 *   
 *   // log when a player kills the npc
 *   log_my_deaths("/d/Earthsea/shiva/npc_death_log");
 *
 *   // set my responses to attempts to "speak" with the npc
 *   set_speak(({ "I heard a rumour that rangers really suck.",
 *                "Supposedly, vampires are far cooler." }));
 *
 *   // wander through four rooms
 *   set_restrain_path(({"/d/Earthsea/telberin/o1", "/d/Earthsea/telberin/o2",
 *                       "/d/Earthsea/telberin/o3", "/d/Earthsea/telberin/o4"}));
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

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

#define MY_NAME          query_name() + " (" + file_name(this_object()) + ")"
#define OTHERS_NAME(who) capitalize(who->query_real_name()) + \
                         " (St Avg " + who->query_average_stat() + ")"
#define LOG(file, msg) catch(write_file(file, sprintf("- %-=70s\n", \
                       msg + " " + ctime(time()))))

static int equipped_flag,
           log_all_kills,
           log_all_deaths,
           special_attack_pcnt,
           next_direction;

static string *equipment, 
               kill_file, 
               death_file, 
               speak_command = "say",
              *speak_list = ({}),
              *restrain_paths = ({}),
              *walk_rooms = ({});


static mixed *specials = ({ });

static mapping to_whom_ive_spoken = ([]);

void create_earthsea_monster() { }

nomask void create_monster()
{
  create_earthsea_monster();
}

/* Function name: add_equipment
 * Description:   add an item to the npc's inventory.  All armours
 *                and weapons added via add_equipment will be wielded/worn
 *                as soon as the npc is first moved.  Calling this
 *                function after the npc is first moved will have no
 *                effect.
 * Arguments:     mixed eq - the path to the object to be cloned or
 *                           an array of paths.
 */
void add_equipment(mixed eq)
{
  if (!pointerp(eq))
  {
    equipment = ({ eq });
  }
  else
  {
    equipment = eq;
  }
}

/* clone and wield/wear equipment added through add_equipment.
 * This only occurs once.
 */
void arm_me()
{
  if (!equipped_flag)
  {
    setuid();
    seteuid(getuid());

    map(equipment, clone_object)->move(this_object(), 1);

    command("wield all");
    command("wear all");
    command("hold all");

    equipped_flag = 1;
  }
}

/* we redefine move so that it calls arm_me().  This is a pretty
 * tacky way to handle it, imo, but it seems to be the only point
 * that an npc can wield and wear before entering a room.
 */
varargs int move(mixed dest, mixed subloc)
{
    if (!equipped_flag)
    {
        arm_me();
        equipped_flag = 1;
    }

    return ::move(dest, subloc);
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

/* Function name: set_restrain_path
 * Description:   restrict an npc's wandering to certain files/directories
 * Arguments:     string *paths - an array of strings which are the pathnames
 *                                of the rooms and directories to which the 
 *                                npc will be restricted.
 */  
void set_restrain_path(mixed paths)
{
  if (!pointerp(paths))
  {
    paths = ({ paths });
  }

  monster_restrain_path = paths;
}

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

/* Function name: set_speak
 * Description:   designate response(s) to attempts to "speak" to
 *                the npc.
 * Arguments:     mixed speak - a string or an array of strings which
 *                              the npc will "say".  If an array is
 *                              given, each successive attempt to
 *                              "speak" to the npc will cause the npc
 *                              to respond with the next string in the
 *                              array.
 * Returns:       1 - responses added
 *                0 - responses not added
 */
int set_speak(mixed speak)
{
  if (stringp(speak))
  {
    speak = ({ speak });
  }

  if (!pointerp(speak))
  {
    return 0;
  }

  speak_list = speak;
  return 1;
}

/* Function name: query_speak
 * Returns:       An array of strings, which are the npc's responses
 *                the the "speak" command
 */
string *query_speak() { return speak_list; }

// respond to a "speak"
void continue_speak(object who)
{
  int where_to_start;
  string what_to_say;

  if (!present(who, environment()) || !sizeof(speak_list))
  {
    return;
  }

  where_to_start = to_whom_ive_spoken[who];

  if (where_to_start >= sizeof(speak_list))
  {
    where_to_start = 0;
  }

  set_this_player(who);
  what_to_say = check_call(speak_list[where_to_start]);

  command("say " +
/*to " + who->query_real_name() + " " +*/
      what_to_say);

  to_whom_ive_spoken[who] = ++where_to_start;
}

// redefine this to change the message when a conversation is started  
void start_conversation_hook(object who)
{
  say(QCTNAME(who) + " tries to start a conversation with " +
      QTNAME(this_object()) + ".\n");
}

// redefine this to change the message when a conversation is continued
void continue_conversation_hook(object who)
{
  say(QCTNAME(who) + " continues " + who->query_possessive() +
      " conversation with " + QTNAME(this_object()) + ".\n");
}

// start the response sequence
void do_speak(object who)
{
  to_whom_ive_spoken[who] ? continue_conversation_hook(who) :
      start_conversation_hook(who);

  set_alarm(1.0, 0.0, &continue_speak(who));
}

// this is the code for the "speak" command.
int speak(string str)
{
  object *who;

   if(!sizeof(speak_list))
      return 0;

  notify_fail("Speak to whom?\n");
  if (!strlen(str) || !CAN_SEE_IN_ROOM(this_player()))
  {
    return 0;
  }

  if (!parse_command(lower_case(str), all_inventory(environment()),
      "[to] [the] %l", who))
  {
    return 0;
  }

  who = NORMAL_ACCESS(who - ({ this_player() }), 0, 0) - ({ 0 });

  if (!sizeof(who))
  {
    return 0;
  }

  who->do_speak(this_player());
  
  return 1;
}

void init_living()
{
  ::init_living();

  add_action(speak, "speak");
}

/* This is called from the combat object on each combat round to
 * see if this npc will do a special attack this round.  We do
 * some tests to see if we wish to attempt a special this round,
 * and if so, the appropriate function (as given by the first
 * argument to add_special_attack) is called.  That function
 * should return 0 if regular attacks should or 1 if they should
 * not (successful special attack).
 */
int special_attack(object enemy)
{
  int i, j, ran;
  function attack_func;

  if (!sizeof(specials) || random(100) >= special_attack_pcnt)
  {
    return 0;
  }

  // decide which special to use
  ran = random(100);
  for (i = sizeof(specials); i--;)
  {
    if ((j += specials[i][1]) >= ran)
    {
      break;
    }
  }

  // call the appropriate function for the chosen attack
  i = MAX(0, MIN(sizeof(specials), i));
  attack_func = specials[i][0];
  return attack_func(enemy);
}

/* Function name: add_special_attack
 * Description:   add a special attack to those that will be performed by
 *                this npc 
 * Arguments:     function attack_func - the function to be called to execute
 *                                       the special attack.  This function
 *                                       should return 1 if regular attacks
 *                                       should be suspended this round, 0
 *                                       if they should not.
 *                int pcnt - the percentage that this attack should be used.
 *                           The sum of the percent usages of all the special
 *                           attacks should be 0
 *                mixed id - a unique id for this special attack for use
 *                           with remove_special_attack
 */
void add_special_attack(function attack_func, int pcnt, mixed id)
{
  specials += ({ ({ attack_func, pcnt, id }) });
}

/* Function name: remove_special_attack
 * Description:   remove a special attack from those that will be performed
 *                by this npc
 * Arguments:     mixed id - the attack's id.  It would seemingly make more
 *                           sense to use the function as an id, but it seems
 *                           that function-type variables can't be compared
 *                           reliably.
 * Returns:       1 - attack removed; 0 - attack not removed
 */
int remove_special_attack(mixed id)
{
  return (sizeof(specials) != sizeof(specials =
     filter(specials, &operator(!=)(id) @ &operator([])(,2))));
}

/* Function name: remove_all_special_attacks
 * Description:   removes all special attacks performed by this npc
 * Returns:       1
 */
int remove_all_special_attacks() 
{ 
  specials = ({ }); 
  return 1;
}

/* Function name: query_special_attacks
 * Description:   get a listing of special attacks performed by this npc
 * Returns:       an array of three-element arrays, where the first element
 *                is a function corresponding to a special attack, the 
 *                second element is an integer which is that attack's
 *                percent usage, and the third element is the attack's id.
 */
mixed *query_special_attacks() { return specials; }

/* Function name: set_special_attack_percent
 * Description:   set the percent of attack rounds that this npc should
 *                attempt a special attack.
 * Arguments:     int pcnt - the percentage of rounds
 * Returns:       1
 */
int set_special_attack_percent(int pcnt)
{
  special_attack_pcnt = pcnt;
  return 1;
}

/* Function name: query_special_attack_percent
 * Description:   get the percentage of attack rounds that this npc
 *                attempts a special attack.
 * Returns:       the percentage (integer)
 */
int query_special_attack_percent() { return special_attack_pcnt; }

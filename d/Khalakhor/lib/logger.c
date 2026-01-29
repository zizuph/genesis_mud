/*
 * Comprehensive logger support
 * Tapakah, 07/2021
 * Added kill/killed support, based on Kalad's identical code
 *  by Zignur
 * Tapakah, 08/2021
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <time.h>
#include "/d/Khalakhor/lib/logger.h"
#include "/d/Khalakhor/sys/defs.h"

void
rotate_log (string file)
{
  string datestamp = TIME2FORMAT(time(), "yyyymmdd");
  int i = 0;
  string new_file = file + "-" + datestamp;

  while (file_size(new_file) != -1)
    new_file = file + datestamp + "-" + (++i);
  rename(file, new_file);
}

varargs void
log_me (string message, string severity="info", string file=0)
{
  setuid();
  seteuid(getuid());
  if (! file)
    file = MISC_LOG;

  if (! wildmatch("*.log", file))
    file += ".log";

  if (! wildmatch("/*", file))
    file = LOG_DIR + file;

  if (file_size(file) > 25000)
    rotate_log(file);

  string log_string = sprintf("%s [%-7s] %s %s\n",
                              ctime(time()), severity, MASTER, message);
  write_file(file, log_string);
}

void
log_npc_death (object killer)
{
  object *team;
  string message;

  if (!objectp(killer) || !living(killer))
    return;
     
  // Check if other members in the team.        
  team = killer->query_team_others();
  // See if they are in the same room.
  team = filter(killer->query_team_others(),
                &operator(==) (environment(killer)) @ environment);
  message =  killer->query_real_name()+
    " (" + killer->query_average_stat() + ") killed "
    + TO->query_name() +
    // Write down the teammembers also.
    (sizeof(team) ? " assists: " : "");

  foreach (object member: team)
    message += member->query_real_name()+ " ("+
      member->query_average_stat()+ ") ";

  log_me(message, "info", NPC_DEATHS_LOG);
}

void
log_player_death (object player)
{
  string message;

  if (player->query_npc())
    return;
  else {
    seteuid(getuid());
    message = TPQN + " (" 
      + player->query_average_stat() + ") killed by "
      + TO->query_name();
    log_me(message, "info", PLAYER_DEATHS_LOG);
  }
}

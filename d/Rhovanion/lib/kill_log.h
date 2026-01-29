/* A file to include if you want your monster to log when it kills a player. */

#include <macros.h>

void
notify_you_killed_me(object player) 
{
  if (player->query_npc()) return; /*don't log NPC kill */

  seteuid(getuid());

  write_file("/d/Rhovanion/log/KILLS",
    ctime(time())+" "+
    player->query_name()+" ("+player->query_average_stat()+") by "+
    "("+query_average_stat()+") "+MASTER+" in "+
    file_name(environment(player))+"\n");
  return;
}

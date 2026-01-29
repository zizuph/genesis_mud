/* A file to include if you want your monster to log when it kills a player. */
#include "/sys/macros.h"

notify_you_killed_me(object player) {
  if (player->query_npc()) return 1;
  seteuid(getuid(this_object()));
  write_file("/d/Shire/log/evilkill",player->query_name() + 
    " ("+player->query_average_stat()+
    ") was killed by "+this_object()->query_name()+" on " +
    ctime(time())+" ("+file_name(environment(this_object()))+").\n");
  return 1;
}

/* A file to include if you want your monster to log when it kills a player. */
#include <macros.h>

notify_you_killed_me(object player){
    command("get all from corpse");
    if(player->query_npc()) return 1;
    seteuid(getuid(this_object()));
    write_file("/d/Terel/log/terel_kills",player->query_name() +
      " ("+player->query_average_stat()+
      ") by "+this_object()->query_name()+" on " +
      ctime(time())+" ("+file_name(environment(this_object()))+").\n");
    return 1;
}

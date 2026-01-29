#include "../defs.h"

int hex(string who)
{
 object *list,sh;

 NF("Hex yourself? You must be crazy!\n");
 if(!who) return 0;
 
 list=parse_this(who,"[to] %l");
 NF("You don't see that person here.\n");
 if(!sizeof(list)) return 0;

 NF("You can only hex one person at a time");
 if(sizeof(list)>1) return 0;

 NF("You cannot hex someone who is already hexed!\n");
 if(list[0]->query_hexed()) return 0;

 setuid();
 seteuid(getuid());

 actor("You place a hex upon",list,"!");
 all2act(" places a hex upon",list,"!");
 target(" places a hex upon you!",list);

 sh=clone_object(TRICKSTERS+"obj/hex_shadow");
 sh->shadow_me(list[0]);
 sh->start_hex(TP);

 return 1;
}


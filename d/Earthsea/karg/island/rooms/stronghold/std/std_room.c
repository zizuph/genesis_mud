inherit "/std/room";

#include "defs.h"

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n");

void create_stronghold_room()
{
}

void create_room()
{
 create_stronghold_room();
}

int query_stronghold_room() {return 1;}

void enter_inv(object inv, object from)
{
 int i;
 object *subinv;

 subinv=subinventory(0);

 if((SERVER)->is_enemy(inv->query_real_name()))
  {
   for(i=0;i<sizeof(subinv);i++)
     if(subinv[i]->query_name()=="Karg") 
       subinv[i]->notify_enemy_arrival(inv);
  }

 ::enter_inv(inv,from);
}


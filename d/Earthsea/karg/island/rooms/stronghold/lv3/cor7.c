#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(4);
object leader;

#include "../std/block_room.h"

void create_stronghold_room()
{
 blocked_exit="northwest";

 set_short("Circle corridor in the stronghold");
 set_long("@@get_long"); 

 add_exit(STRHOLD_LVL3+"cor6","northeast");
 add_exit(STRHOLD_LVL3+"cor8","southwest");
 add_exit(STRHOLD_LVL3+"cat4","northwest","@@block");

 reset_room();
}

void reset_room()
{
 int i;

 for(i=0;i<sizeof(guards);i++)
  {
   if(!guards[i])
    {
     guards[i]=clone_object(STRHOLD_NPC+"eguard");
     guards[i]->set_help(1);
     guards[i]->set_stil(1);
     guards[i]->set_auto_reteam(1);
     guards[i]->move(TO);
     if(leader) leader->team_join(guards[i]);
     else leader=guards[i];
    }
  }

 (STRHOLD_LVL3+"cat4")->reset_catapult();
}


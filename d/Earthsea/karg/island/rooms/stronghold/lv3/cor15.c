#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(4);
object leader;

#include "../std/block_room.h"

void create_stronghold_room()
{
 blocked_exit="southeast";

 set_short("Circle corridor in the stronghold");
 set_long("@@get_long"); 

 add_exit(STRHOLD_LVL3+"cor14","southwest");
 add_exit(STRHOLD_LVL3+"cor16","northeast");
 add_exit(STRHOLD_LVL3+"cat1","southeast","@@block");

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

 (STRHOLD_LVL3+"cat1")->reset_catapult();
}


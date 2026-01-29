#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(4);
object leader;

void create_stronghold_room()
{
 set_short("Inside of guard lookout tower");
 set_long("This is guards lookout tower. Guards watch the sea through "+
   "large windows and will sound alarm if any ship will be spotted.\n");

 add_item(({"window","windows"}),"You look out of window and see "+
   "the sea , with karg warships patroling around.\n");

 add_exit(STRHOLD_LVL3+"tower1","down");

 reset_room();
}

void reset_room()
{
 int i;
 string to_clone;

 for(i=0;i<sizeof(guards);i++)
  {
   if(!guards[i])
    {
     switch(i)
      {
       case 0: to_clone="eguard"; break;
       case 1: to_clone="guard"; break;
       case 2: to_clone="mercenary"; break;
       case 3: to_clone="mercenary"; break;
      }
     guards[i]=clone_object(STRHOLD_NPC+to_clone);
     guards[i]->set_help(1);
     guards[i]->set_auto_reteam(1);
     guards[i]->move(TO);
     if(leader) leader->team_join(guards[i]);
     else leader=guards[i];
    }
  }
}


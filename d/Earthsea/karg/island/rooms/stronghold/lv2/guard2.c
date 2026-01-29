#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(4);
object leader;

void create_stronghold_room()
{
 set_short("Guard room");
 set_long("This small room is used as guardroom by kargish guards. "+
   "Small windows on eastern wall give quite good view of the see "+
   "downstairs.\n");

 add_item(({"windows","window"}),"Small windows in eastern wall are "+
   "used by guards to survey sea downslairs. In case of naval attack "+
   "guards can easily sound alarm.\n");

 add_exit(STRHOLD_LVL2+"cor24","northeast");

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
       case 1: to_clone="eguard"; break;
       case 2: to_clone="guard"; break;
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


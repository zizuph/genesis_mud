#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(3);
object leader;

void create_stronghold_room()
{
 set_short("Inside of guard lookout tower");
 set_long("This small room is used as guardroom by kargish guards. "+
   "Small windows on southern wall give quite good view of the gates "+
   "and bridge downstairs.\n");

 add_item(({"windows","window"}),"Small windows in southern wall are "+
   "used by guards to survey gate and bridge that leads to stronghold. "+
   "In case of attack they can be easily used by archers to backup "+
   "guards on gates downstairs.\n");

 add_exit(STRHOLD_LVL1+"tower3","down");

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


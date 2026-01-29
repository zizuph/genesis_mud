#include <macros.h>

#include "defs.h"

inherit STD_STRHOLD;

object *guards=allocate(5);
object leader;

void create_stronghold_room()
{
 set_short("Inside of stronghold gates");
 set_long("You are inside of gateroom of the stronghold. Gates are "+
   "heavily guarded by group of guards. North of you dark corridor "+
   "leads into the fortress. You see large wheel on the wall. To "+
   "east and west you see entrance to guards towers.\n");

 add_item(({"arch","gate","gates"}),"Sturdy wooden gates can easily "+
   "block entrance to any unwelcomed creature.\n");

 add_item("wheel","It is used to quickly close and open the gate.\n");

 add_exit(STRHOLD_LVL1+"ent1","south");
 add_exit(STRHOLD_LVL1+"ent3","north","@@block");
 add_exit(STRHOLD_LVL1+"tower3","east");
 add_exit(STRHOLD_LVL1+"tower4","west");

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
       case 0: to_clone="lieutenant"; break;
       case 1: to_clone="eguard"; break;
       case 2: to_clone="guard"; break;
       case 3: to_clone="guard"; break;
       case 4: to_clone="mercenary"; break;
      }
     guards[i]=clone_object(STRHOLD_NPC+to_clone);
     guards[i]->set_help(1);
     guards[i]->set_stil(1);
     guards[i]->set_auto_reteam(1);
     guards[i]->move(TO);
     if(leader) leader->team_join(guards[i]);
     else leader=guards[i];
    }
  }
}

int block()
{
 object grd;
 int i;

 for(i=0;i<sizeof(guards);i++)
   if(guards[i]) {grd=guards[i];break;}

 if(!grd) return 0;

 if((SERVER)->is_enemy(TP->query_real_name()))
  {
   leader->command("say You will never get through , "+
    TP->query_nonmet_name()+"!");
   say(QCTNAME(TP)+" was brutaly stoped by guards.\n");
   return 1;
  }

 grd->command("say You may enter "+TP->query_nonmet_name()+", but "+
   "stay out of troubles!");
 return 0;
}


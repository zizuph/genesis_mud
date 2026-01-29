#include "defs.h"

#define MOVE_TIMEOUT 30.0

inherit STD_STRHOLD;

object *guards=allocate(4);
object leader;
object loc;
int alarm_h=0;

void create_stronghold_room()
{
 set_short("Smaller corridor in the stronghold");
 set_long("You are in the small and dark corridor in the stronghold. "+
   "It is very dusty and narrow. Smaller corridor turns to the "+
   "northeast.\n");

 add_exit(STRHOLD_LVL1+"cor13","north");
 add_exit(STRHOLD_LVL1+"cor15","southeast");
 add_exit(STRHOLD_LVL1+"cor39","northeast");

 reset_room();
}

int all_dead()
{
 int i;

 for(i=0;i<sizeof(guards);i++) if(guards[i]) return 0;

 return 1;
}

object get_leader()
{
 int i;

 for(i=0;i<sizeof(guards);i++)
   if(guards[i]) if(!guards[i]->query_leader()) return guards[i];
}

int is_in_fight()
{
 int i;

 for(i=0;i<sizeof(guards);i++)
   if(guards[i]) 
     if(guards[i]->query_enemy() && 
     ENV(guards[i])==ENV(guards[i]->query_enemy())) return 1;

 return 0;
}

void make_move()
{
 string *dirs;

 if(all_dead()) 
  {
   remove_alarm(alarm_h);
   alarm_h=0;
   return;
  }

 if(is_in_fight()) return;

 dirs=loc->query_exit_cmds();
 dirs-=({"up","down"});
 if(file_name(loc)==STRHOLD_LVL1+"cor1") dirs-=({"south"});
 get_leader()->command(dirs[random(sizeof(dirs))]);
 loc=ENV(get_leader());
}

void reset_room()
{
 int i;
 string to_clone;

 if(all_dead()) loc=TO;

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
      }
     guards[i]=clone_object(STRHOLD_NPC+to_clone);
     guards[i]->set_help(1);
     guards[i]->set_auto_reteam(1);
     guards[i]->move(loc);
     if(leader) leader->team_join(guards[i]);
     else leader=guards[i];
    }
  }

 if(!alarm_h) alarm_h=set_alarm(MOVE_TIMEOUT,MOVE_TIMEOUT,&make_move());
}

object query_loc() {return loc;}


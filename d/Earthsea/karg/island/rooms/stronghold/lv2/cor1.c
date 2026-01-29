#include "defs.h"

inherit STD_STRHOLD;

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")
#define MOVE_TIMEOUT 30.0

object *guards=allocate(5);
object leader;
object loc;
int alarm_h=0;

void create_stronghold_room()
{
 set_short("Broad corridor in the stronghold");
 set_long("You are in the dark and broad corridor on the second level "+
   "of the stronghold. To southwest and southeast you see small round "+
   "rooms, while corridor splits here running towards northwest and "+
   "northeast.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners.\n");
 add_item(({"banner","banners"}),"Banners are of different colours "+
   "and sway slightly in the gusts of wind , freely blowing down "+
   "the corridor.\n");

 add_exit(STRHOLD_LVL2+"down1","southwest");
 add_exit(STRHOLD_LVL2+"down2","southeast");
 add_exit(STRHOLD_LVL2+"cor18","northeast");
 add_exit(STRHOLD_LVL2+"cor2","northwest");

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
       case 2: to_clone="eguard"; break;
       case 3: to_clone="guard"; break;
       case 4: to_clone="mercenary"; break;
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


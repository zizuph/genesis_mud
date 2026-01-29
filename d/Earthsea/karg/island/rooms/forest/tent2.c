/* 12/10/2001 by Ged.
 * Tent with diary for Tricksters entrance quest.
 * guards will leave to partol the forest every REST_TIME
 * seconds after they return from patrol. They will take
 * sizeof(PATROL_DIRS) steps with delay of TIME_BETWEEN_STEPS
 * seconds. So patrol time is sizeof(PATROL_DIRS)*TIME_BETWEEN_STEPS
 * seconds
*/

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include <ss_types.h>

#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

#define TIME_BETWEEN_STEPS 4.5
#define REST_TIME 600.0
#define PATROL_DIRS ({"out","w","w","w","w","nw","n","n","n","nw",\
"ne","n","se","ne","e","w","sw","nw","s","sw","sw","w","w","w","w",\
"e","e","e","e","ne","se","s","s","s","se","e","e","e","e"})

object officer;
object *guard = allocate(4);
object location=TO;
object patrol_leader;
int step=0;
object chest=0;
int key=1;

void start_patrol();
void do_move(string dir);
void end_patrol();
void reteam();
int all_dead();
int guarded();

void create_island_room()
{
 set_short("In the tent");
 set_long("This tent is slightly larger than its twin. "+
   "You can see a couple of bedrolls and blankets "+
   "on the ground near the entrance. Further part "+
   "of the tent is obscured with a big blanket "+
   "hanging across the tent.\n\n");

 add_cmd_item("blanket","peek","@@peek_blanket");

 add_item("blanket","A big blanket made of wool divides the "+
    "tent. You wonder what is hidden behind it. Uhmmmm... wouldn't "+
    "in be unpolite to peek it?\n\n");
 add_item("table","@@exa_table");
 add_item("bed","@@exa_bed");

 add_exit(FROOMS+"/path13","out");

 add_prop(OBJ_S_SEARCH_FUN, "search_func");
 add_prop(OBJ_I_SEARCH_TIME, 5);

 reset_room();
}

void reset_room()
{
 int i,start_over=0;
 object *team;

 if(chest) chest->remove_object();
 chest=0;

 key=1;

 if(all_dead()) start_over=1;

 if(!officer)
  {
   officer=clone_object(ISLAND_LIV+"officer");
   officer->set_help(1);
   officer->set_aggressive(1);
   officer->add_prop(HAS_PATH_HINT,1);
   officer->move(location);
   tell_room(location,QCTNAME(officer)+" runs in.\n");
   if(patrol_leader)
    {
     team=patrol_leader->query_team();
     for(i=0;i<sizeof(team);i++) patrol_leader->team_leave(team[i]);
    }
  }

 for(i=0;i<sizeof(guard);i++)
  {
   if(!guard[i])
    {
     guard[i]=clone_object(ISLAND_LIV+"guard");
     guard[i]->set_help(1);
     guard[i]->set_aggressive(1);
     guard[i]->add_prop(HAS_PATH_HINT,1);
     guard[i]->move(location);
     officer->team_join(guard[i]);
     tell_room(location,QCTNAME(guard[i])+" runs in.\n");
    }
   else officer->team_join(guard[i]);
  }

 patrol_leader=officer;
 if(start_over) set_alarm(REST_TIME,0.0,&start_patrol());
}

string exa_table()
{
 if (TP->query_prop(PLAYER_I_PEEKED_BLANKET))
  {
   if(guarded()) return "Guards won't let you!\n";

   if(chest) return "Small wooden table, some maps thrown upon it.\n";
   chest=clone_object(ISLAND_ITEM+"chest");
   chest->move(TO);
   return "Small wooden table, some maps thrown "+
     "upon it. Below the table you find a chest.\n\n";
  }
 return "Table? Where?? \n\n";
}

string exa_bed()
{
 if (TP->query_prop(PLAYER_I_PEEKED_BLANKET))
  {
   if(guarded()) return "Guards won't let you!\n";

   return "Spartan bed that may quickly be "+
     "disassembled and packed, with a bedroll on it.\n\n";
  }
 return "Bed? Where?? \n\n";
}

string peek_blanket()
{
 int i;

 if(guarded()) return "Guards won't let you!\n";

 TP->add_prop(PLAYER_I_PEEKED_BLANKET,1);
 return  "You peek behind the blanket and see... a bed."+
   " Yes, a bed in a tent, pretty sure some officer "+
   "decided it worth to carry the weight all the way "+
   "here for some comfort. Besides the bed there is a "+
   "small table with a chair by it.\n\n";
}

void start_patrol()
{
 step=0;
 set_alarm(1.0,0.0,&do_move(PATROL_DIRS[0]));
}

void do_move(string dir)
{
 object enemy;

 if(!patrol_leader) reteam();
 if(!patrol_leader)
  {
   location=TO;
   return;
  }

 enemy=patrol_leader->query_enemy();
 if(enemy && ENV(enemy)==ENV(patrol_leader)) 
  {
   set_alarm(TIME_BETWEEN_STEPS,0.0,&do_move(dir));
   return;
  }

 patrol_leader->command(dir);
 location=ENV(patrol_leader);
 step++;
 if(step==sizeof(PATROL_DIRS))
  {
   end_patrol();
   return;
  }
 set_alarm(TIME_BETWEEN_STEPS,0.0,&do_move(PATROL_DIRS[step]));
}

void end_patrol()
{
 int i;

 if(officer) 
  {
   tell_room(ENV(officer),C(officer->short())+" enters the tent.\n");
   officer->move(ISLAND_FOREST+"tent2");
   tell_room(ENV(officer),C(officer->short())+" arrives from outside.\n");
  }
 for(i=0;i<sizeof(guard);i++)
  {
   if(!guard[i]) continue;
   tell_room(ENV(guard[i]),C(guard[i]->short())+" enters the tent.\n");
   guard[i]->move(ISLAND_FOREST+"tent2");
   tell_room(ENV(guard[i]),C(guard[i]->short())+" arrives from "+
     "outside.\n");
  }

 location=TO;
 set_alarm(REST_TIME,0.0,&start_patrol());
}

void reteam()
{
 int i,g_ind;

 if(officer)
  {
   for(i=1;i<sizeof(guard);i++)
     if(guard[i]) officer->team_join(guard[i]);
   patrol_leader=officer;
  }
 else
  {
   g_ind=-1;
   for(i=0;i<sizeof(guard);i++)
     if(guard[i]) {g_ind=i; break;}
   if(g_ind==-1) return;
   for(i=0;i<sizeof(guard);i++)
     if(i!=g_ind && guard[i]) guard[g_ind]->team_join(guard[i]);
   patrol_leader=guard[g_ind];
  }
}

object query_leader() {return patrol_leader;}

int all_dead()
{
 int i;

 if(officer) return 0;

 for(i=0;i<sizeof(guard);i++) if(guard[i]) return 0;

 return 1;
}

int guarded()
{
 int i;

 if(location!=TO) return 0;
 for(i=0;i<sizeof(guard);i++)
   if(guard[i]) return 1;
 if(officer) return 1;
}

string search_func(object pl,string str)
{
 if(str!="bed") return "Your search reveals nothing special.\n";

 if(pl->query_skill(SS_AWARENESS)<30 || !key)
   return "You find nothing , and only make a mess on the bed.\n";

 clone_object(ISLAND_ITEM+"key")->move(pl);
 key=0;
 return "You find a key under the pillow!\n";
}

object query_location() {return location;}

void leave_inv(object ob,object to)
{
 ob->remove_prop(PLAYER_I_PEEKED_BLANKET);
}


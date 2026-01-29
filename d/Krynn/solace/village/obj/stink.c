/* the stinking object from the skunk
* created by Stevenson
*/
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

void
init() 
{
   find_living("stevenson")->catch_msg(TP->query_name()+" just got sprayed!\n");
   set_alarm(0.0,0.0,"leave_team");
   set_alarm(5.0,20.0,"you_stink");
   set_alarm(itof(random(200) + 100),0.0,"remove_me");
   ADD("no_team","join");
   ADD("no_team","invite");
   ::init();
}

void
create_object() 
{
   set_short("stink");
   set_name("spray");
   add_name("stink");
   
   add_prop(OBJ_I_NO_GIVE,1);
   add_prop(OBJ_I_NO_DROP,1);
   add_prop(OBJ_I_INVIS,1);
   add_prop(OBJ_I_HIDE,1);
   add_prop(OBJ_M_NO_SELL,1);
}

void
you_stink() 
{
   tell_room(E(TP),QCTNAME(TP)+" really stinks. You feel repulsed by "
      + TP->query_objective() + ".\n",TP);
   write("You really stink!\n");
}

void
remove_me() 
{
   tell_room(E(TP),QCTNAME(TP)+" doesn't stink anymore.\n",TP);
   write("Your bad smell fades.\n");
   TO->remove_object();
}

void
leave_team() 
{
   object lead = TP->query_leader();
   object * team_arr = TP->query_team();
   int team_num = sizeof(team_arr), i;
   if (team_num) {
      /* you are team leader. make all run away */
      set_this_player(environment());
      for (i=0;i<team_num;i++) {
         write(team_arr[i]->query_name()+" refuses to be "
            + "with someone smelling as bad as you.\n");
	
         team_arr[i]->catch_msg(QCTNAME(TP)+" is suddenly rendered "
+ "incapable of leading you because he stinks so much.\n");
         TP->team_leave(team_arr[i]);
       }
   }
   if (lead)
      {
      write("Because you stink so much, " 
         + TP->query_leader()->query_name()
         + " decides he doesn't want you near "
	 + TP->query_leader()->query_objective() + ".\n");
      lead->catch_msg("You throw " + QTNAME(TP) + " out of the team " +
         "because " + TP->query_pronoun() + " stinks so " +
         "bad.\n");
      tell_room(E(TP),QCTNAME(lead) + " throws " + QTNAME(TP) + " out " +
         "of the team because " + TP->query_pronoun() + " stinks " +
         "so bad.\n", ({ TP, lead }));
      lead->team_leave(TP);
   }
}

int 
no_team(string str) 
{
   write("Nobody would want you because you stink so much!\n");
   return 1;
}



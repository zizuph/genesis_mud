// Saggart Meditation room.
// If an altar with a monstrance with a consecrated shamrock is here,
// the saggart can regain mana by meditating here.
//
// History:
// Date         Coder       Action
// ----------   ----------- ----------------------------------
// 7/20/98      Zima        Created
//
#include "defs.h"
inherit  SR_ROOM+"kneelrm";
#include <macros.h>
#include <stdproperties.h>
#include "meditation.h"
#include <filter_funs.h>
#define  MEDITATING         "_sr_meditating"
 
object altar;
int    in_meditation=0;     // is a do_med scheduled? are we meditating?
 
//
// mon_ok - is a montrance on the altar with the shamrock?
//
object mon_ok()
{
   object mon;
   if (!objectp(altar)) return 0;
   mon = present(SR_MONSTRANCE,altar);
   if (objectp(mon) && (mon->query_shamrock())) return mon;
   return 0;
}
 
//
// meditating
//
object meditating(object tp)
{
   object pobj = present(MED_PARALYSIS_OBJID,tp);
   if (objectp(pobj)) return pobj;
   return 0;
}
int query_in_meditation() { return in_meditation; }
 
//
// do_med - if monstrance OK, add mana to all meditating players allowed
//
void do_med()
{
   object* player;
   object  mon = mon_ok(), pobj;
   int     i, num_meds=0;
 
   // get a list of all players in the room
   player = FILTER_PLAYERS(all_inventory(TO));
 
   // check list of players for those meditating
   for (i=0; i<sizeof(player); i++)
      if (objectp(pobj=meditating(player[i])))
      {
      if (objectp(mon) && (mon->allowed_to_med(player[i])) &&
         (mon->query_shamrock()) &&
         ((player[i])->query_mana() < (player[i])->query_max_mana()))
         {
         player[i]->catch_msg("You feel strength flowing through your "+
                              "meditations.\n");
         player[i]->add_mana(MED_INC_MANA_AMT);
         mon->report_med(player[i],MED_INC_MANA_AMT);
         num_meds++;
         }
      else
         {
         player[i]->catch_msg("You feel your meditations here are "+
                              "complete.\n");
         pobj->remove_object();
         tell_room(TO,QCTNAME(player[i])+" awakens from meditation.\n",
                   player[i]);
         }
      }
 
   // if some are still meditating, schedule next do_med, or stop
   if (num_meds > 0)
      set_alarm(MED_INC_TIME,0.0,&do_med());
   else
      in_meditation = 0;
}
 
//
// srmeditate
//
int srmeditate(string cmd)
{
   object mon=mon_ok(), pobj;
 
   if (!kneeling(TP))
      write("You should kneel first.\n");
   else if (!(TP->is_saggart()))
      write("You meditate momentarily.\n");
   else if (!objectp(mon))
      write("You meditate momentarily but seem unable to concentrate.\n");
   else if (meditating(TP))
      write("You are already deep in meditation.\n");
   else if (!(mon->allowed_to_med(TP)))
      write("Your meditations here are complete.\n");
   else
      {
      seteuid(getuid());
      pobj = clone_object(SR_LIB+"medparalysis");
      pobj->move(TP);
      TP->catch_msg("You begin to meditate and fall into a restful trance.\n");
      tell_room(TO,QCTNAME(TP)+" begins to meditate intently.\n",TP);
      if (!in_meditation)
         {
         in_meditation = 1;
         set_alarm(MED_INC_TIME,0.0,&do_med());
         }
      }
   return 1;
}
 
//
// do_feel - player entering the room feels the presence of the monstrance
//
void do_feel(object tp, object room)
{
   if (!(objectp(mon_ok()) && objectp(tp) && (present(tp,room)))) return;
   set_this_player(tp);
   if (tp->query_alignment()<0)
      write("You feel a belligerent deadly presence in this place.\n");
   else
      write("You feel a peaceful presence in this place.\n");
}
 
//
// enter_inv - let the player feel the presence of the monstrance
//
public void enter_inv(object ob, object from)
{
   if (interactive(ob) && objectp(mon_ok()))
      set_alarm(3.0,0.0,&do_feel(ob,TO));
   ::enter_inv(ob,from);
}
 
//
// exa - show player long desc of montrance if its on the altar
//
int exa(string cmd)
{
   object mon = present(SR_MONSTRANCE,altar);
   if (!parse_command(cmd,all_inventory(TO),"'monstrance'")) return 0;
   if ((!objectp(mon))||(!present(mon,altar))) return 0;
   write(mon->long());
   return 1;
}
 
//
// init - add actions to the room
//
void init()
{
   ::init();
   add_action(&srmeditate(),"meditate");
   add_action(&exa(),       "exa",1); // catch examine/exa
}

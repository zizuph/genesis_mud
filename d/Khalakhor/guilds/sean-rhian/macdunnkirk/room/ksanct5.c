/* Kirk of Port City - Sanctuary - central altar
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
** 6/1/98      Zima        Code for quest added
*/
/* inherits/includes */
#include "defs.h"
inherit ROOM+"ksanct";
#include <macros.h>
#include <stdproperties.h>
#define  NUM_MONKS 2
#define  PROC  "_sr_proc_prop"
#define  PROC1 "i offer these gifts to ardaugh the most high!"
#define  PROC2 "the fruits of the earth and the work of my hands!"
#define  PROC3 "praised be ardaugh forever!"
 
object   altar;
object   *monk=allocate(NUM_MONKS);
int      responding=0;
 
void make_monk(int i) {
   if (monk[i]) return;
   monk[i]=clone_object(SR_NPC+"kmonk");
   monk[i]->equip_me();
   monk[i]->set_wander(ROOM+"ksanct", MASTER_OB(TO), 60);
   monk[i]->move(TO);
   tell_room(TO,QCNAME(monk[i])+" approaches the altar reverently.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM_MONKS; i++) make_monk(i);
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("Sanctuary of the kirk");
   set_long(
      "   You are at the center of the sanctuary of the kirk, standing "+
      "before the high altar, the center of worship for those who gather "+
      "here. Everything in the sanctuary seems to focus at this point; "+
      "the gaze of the figures depicted in the windows, the protective "+
      "stare of the angel in the apse, even the main entrance of the "+
      "sanctuary directly south leads one here. Light from the hundreds "+
      "of candles in the chandeliers add to the solemn atmosphere of "+
      "this place.\n");
 
   setup_ksanct();
 
   add_exit("ksanct8", "north",0);
   add_exit("ksanct2", "south",0);
   add_exit("ksanct6", "east",0);
   add_exit("ksanct4", "west",0);
   add_exit("ksanct7", "northwest",0);
   add_exit("ksanct9", "northeast",0);
   add_exit("ksanct1", "southwest",0);
   add_exit("ksanct3", "southeast",0);
   altar=clone_object(SR_OBJ+"kaltar");
   altar->move(this_object());
   reset_room();
}
 
void do_bow(object ob) {
      ob->command("emote places his hand together prayerfully.");
      ob->command("emote bows deeply toward the high altar.");
}
 
void enter_inv(object ob, object from) {
   if (ob->id(SR_NPC_ID)) set_alarm(3.0,0.0,&do_bow(ob));
   ::enter_inv(ob,from);
}
 
void quick_resp(string m) { tell_room(TO,m+"\n"); }
void resp_proc(object tp, object pendant, int step)
{
   string m;
   if ((!objectp(tp))||(ENV(tp)!=TO)) step=6;
   switch (step)
      {
      case 1: m="A light breeze begins to flow."; break;
      case 2: m="The breeze strengthens into a mighty wind."; break;
      case 3: m="A mighty voice proclaims: Your offering is accepted "+
                "aspirant!";
              break;
      case 4: m="A mighty voice proclaims: Show yourself to the Presbytair!";
              break;
      case 5: m="A mighty voice proclaims: For I have found you worthy "+
                "to be my servant!";
              pendant->set_level(4);
              break;
      case 6: m="The wind dies out and all returns to quiet.";
              responding=0;
              break;
      default:m="There is a rip in the fabric of space.";
      }
   tell_room(TO,m+"\n");
   if (responding)
      set_alarm(7.0,0.0,&resp_proc(tp,pendant,(step+1)));
}
 
int altar_ready()
{
   object platter=present(SR_GPLATTER,altar);
   object chalice=present(SR_CHALICE,altar);
   if (objectp(platter) && objectp(chalice) &&
      ((chalice->query_contents())>=1)      &&
      objectp(present("_bk_honeycomb",platter)))
      return 1;
   return 0;
}
 
int proclaim(string cmd)
{
   int    proc=(TP->query_prop(PROC));
   object pendant=present(SHAM_PENDANT,TP);
   string m="";
 
   if (!objectp(pendant)) return 0;
   notify_fail("Proclaim what?\n");
   if (!stringp(cmd)) return 0;
 
   if (altar_ready()&&(pendant->query_level()==3))
      {
      if ((lower_case(cmd)==PROC1)&&(proc==0))
         {
         TP->add_prop(PROC,1);
         m="The platter and chalice on the altar glow briefly.";
         }
      else if ((lower_case(cmd)==PROC2)&&(proc==1))
         {
         TP->add_prop(PROC,2);
         m="The contents of the vessels on the altar glow briefly.";
         }
      else if ((lower_case(cmd)==PROC3)&&(proc==2))
         {
         responding=1;
         set_alarm(7.0,0.0,&resp_proc(TP,pendant,1));
         TP->remove_prop(PROC);
         }
      }
   write("You proclaim: "+cmd+"\n");
   tell_room(TO,QCTNAME(TP)+" proclaims: "+cmd+"\n",TP);
   if (strlen(m)>3) set_alarm(7.0,0.0,&quick_resp(m));
   return 1;
}
 
void init()
{
   ::init();
   add_action(&proclaim(),"proclaim");
}

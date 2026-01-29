inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
int direct,leave_now;
/* by Antharanos */
void create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("On the carpet");
   set_long("You are on top of the flying carpet, the air seeming to "+
      "whip by you as you skim over clouds and race across the landscape. "+
      "The ground below is but a shifting panorama of colors.\n");
   add_item(({"flying carpet","carpet"}),"Its what you're sitting on, silly.\n");
   add_item(({"clouds","cloud"}),"Faint, wispy clouds that were to "+
      "insignificant to see from the ground, but are quite obvious up here.\n");
   add_item(({"landscape","ground"}),"It lies far below you, and all "+
      "that can be seen is the fleeting images of desert, plains and sea as "+
      "they rush by below you.\n");
   add_exit(CPASS(desert/carpet/carpet_leave),"off","@@outta_here");
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");
   set_alarm(20.0,0.0,"moving_start");
   direct=0;      /* 0 = flying away */
   leave_now=0;  /* 0 = safe to leave, 1 = in midair, stupid */
}
wizinfo()
{
   return
   "It is quite possible that this carpet will get stuck on occasion; for "+
   "example, if another basket appears. However, to rectify the situation, "+
   "simply 'Call here restart' to fix it.\n";
}
moving_start()
{
   if(direct==0){
      tell_room(TO,
         "The flying carpet leaps into the sky, dragging you upwards at a "+
         "frightening pace and bringing you into the lower stratosphere.\n");
      call_other(CPASS(desert/carpet/carpet_leave),"come_and_go",1);
   }
   if(direct==1){
      tell_room(TO,
         "The flying carpet suddenly lurches into the sky, almost causing you "+
         "to lose your grip.\n");
      call_other(CPASS(desert/carpet/carpet_board),"come_and_go",1);
   }
   leave_now=1;
   set_alarm(20.0,0.0,"moving_end");
}
moving_end()
{
   tell_room(TO,
      "The flying carpet suddenly slows and drops altitude and prepares "+
      "for a return trip. Now is the time to exit.\n");
   if(direct==1) {
      direct=0;
      call_other(CPASS(desert/carpet/carpet_leave),"come_and_go",0);
   }
   else          {
      direct=1;
      call_other(CPASS(desert/carpet/carpet_board),"come_and_go",0);
   }
   leave_now=0;
   set_alarm(20.0,0.0,"moving_start");
}
outta_here()
{
   if(leave_now==1){
      tell_object(TP,
         "That would be unwise, as the flying carpet is in midair.\n");
      tell_room(TO,(QCTNAME(TP) + " looks over the edge of the flying carpet and "+
            "wisely decides that it wouldn't be a good idea to leave right now.\n"),TP);
      return 1;
   }
   if(leave_now==0&&direct==1){
      TP->move("/d/Kalad/common/wild/pass/desert/carpet/carpet_board");}
   if(leave_now==0&&direct==0) {
      TP->move(CPASS(desert/carpet/carpet_leave));}
   tell_room(TO,
      (QCTNAME(TP) + " leaps off the flying carpet.\n"));
   tell_room(environment(TP),
      (QCTNAME(TP) + " leaps off of the flying carpet.\n"),TP);
   tell_object(TP,
      "You leap off of the flying carpet.\n");
   TP->command("look");
   return 1;
}
restart()
{
   leave_now=0;
   direct=0;
   call_other(CPASS(desert/carpet/carpet_board),"come_and_go",1);
   call_other(CPASS(desert/carpet/carpet_leave),"come_and_go",0);
   return "Okay - no problems";
}

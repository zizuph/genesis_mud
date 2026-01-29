/* Behind the falls, at the bottom.
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/22/97   Zima          Created 
** 21/8/01   Maniac        fixed climb destup and enter dest 
** 
** Notes:
** Special exits:
**   "climb cliff" - climb up the cliff of the mountains behind the falls
**   "jump waterfall",
**   "enter waterfall" - jump into waterfall, onto the boulders outside
*/
inherit "/std/room";
#include <filter_funs.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include "wfall.h"

/* prototypes */
int do_climb(string Parms);
int do_enter(string Parms);

/* room definition */
void create_room() {
   set_short("Behind a waterfall");
   set_long(
       "You are in a cavern behind a waterfall, the craggy cliff rising "+
       "straight up to the heights at the top of the falls. A magnificent "+
       "rainbow arcs above your head, the sunlight from outside the falls "+
       "penetrating the curtain of water to illuminate the mist. To the "+
       "west, you see the mouth of a cave, while to the east through the "+
       "falls, you see mounds of boulders being pounded by the crush of "+
       "the water.\n");
   add_item(({"waterfall","falls","water"}),
       "The falls come crushing down from the heights of the cliff above, "+
       "a powerful curtain of water which veils this cavern from the "+
       "outside. Through the falls, at the bottom, you see boulders which "+
       "you can climb onto.\n");
   add_item(({"mountain","mountains","cliff"}),
       "The craggy cliff of the mountain rises high above you, veiled but "+
       "relatively untouched by the pounding force of the falls. Sharp "+
       "edges portrude the heights of the cliff, threatening impalement "+
       "to any who would dare scale it and slip.\n");
   add_item(({"rainbow","sunlight","mist"}),
       "Sunlight penetrates the veil of the falls, giving a faint light "+
       "to this cavern. A constant mist from the falls dances in the "+
       "sunlight to form a rainbow, arcing from the base of the falls "+
       "to its top.\n");
   add_item(({"mouth","cave"}),
       "There is a mouth of a cave to the west, a strange and dim glow "+
       "coming from inside.\n");
   add_item(({"mound","mounds","boulder","boulders"}),
       "On the other side of the falls, you see mounds of large boulders, "+
       "constantly pounded and drenched by the curtain of falling water. "+
       "It seems you could jump through the falls onto them if you "+
       "wished.\n");

   add_prop(ROOM_I_INSIDE,1);
   add_exit("wfcave","west",0);
}

/*
** INIT - add commands
*/
void init() {
   ::init();
   add_action(do_climb,"climb");
   add_action(do_enter,"enter");
   add_action(do_enter,"jump");
}

/*
** CLIMB - allows player to "climb up cliff"
*/
int do_climb(string Parms) {
   string *parm;
   object destup=(F2ROOM->get_this_object());

   if (!(Parms)) { write("Climb where?\n"); return 1; }
   parm=explode(Parms," ");


   if ((member_array("cliff",parm)>=0)||(member_array("cliffs",parm)>=0)||
       (member_array("mountain",parm)>=0)||(member_array("up",parm)>=0))
      {
      if (TP->query_skill(SS_CLIMB) < CCLIMB_SKILL)
         write("It is too dangerous for you to climb the craggy cliff.\n");
      else
         {
         write("You climb up the side of the cliff.\n");
         tell_room(TO,QCTNAME(TP)+" climbs up the cliff of the cavern.\n",TP);
         tell_room(destup,QCTNAME(TP)+" climbs up the cliff from below.\n",TP);
         TP->move_living("M", destup);
         }
      return 1;
      }
   write("Climb where?\n");
   return 1;
}

/*
** ENTER - allows player to "enter" or "jump" into waterfall
*/
int do_enter(string Parms) {
   string verb=capitalize(query_verb());
   string *parm;
   object dest=(BROOM->get_this_object());

   if (!(Parms)) { write(verb+" where?\n"); return 1; }
   parm=explode(Parms," ");

   if ((member_array("waterfall",parm)<0)&&(member_array("falls",parm)<0)) {
      write(verb+" where? Into the falls?\n");
      return 1;
   }
   write("You deftly jump into the crushing water of the falls!\n");
   write("You land on the slippery boulders and hang on for your life!\n");
   tell_room(TO,  QCTNAME(TP)+" jumps into the falls and disappears into "+
                  "the water!\n",TP);
   tell_room(dest,QCTNAME(TP)+" comes diving out of the falls and lands "+
                  "on the boulders, clinging for dear life!\n",TP);

   TP->move_living("M", dest);
   return 1;
}

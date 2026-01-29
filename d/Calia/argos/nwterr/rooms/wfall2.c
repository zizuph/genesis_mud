/* Behind the falls, climbing the cliff
**
** History
** Date        Coder       Action
** --------  ------------  ---------------------- 
** 2/22/97   Zima          Created 
** 21/8/01   Maniac        fixed climb destup and destdn 
** 
** Notes:
** Special exits:
**   "climb up/down"
*/
inherit "/std/room";
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "wfall.h"

/* prototypes */
int do_climb(string Parms);

/* room definition */
void create_room() {
   set_short("Clinging to the cliff behind a waterfall");
   set_long(
       "You are clinging to the side of the cliff behind the falls, the "+
       "light mist from the water behind you moistening the rocks making "+
       "them slippery. You catch a glimpse of bright sunlight from above, "+
       "while below is the floor of the cavern behind the base of the "+
       "falls.\n");
   add_item(({"waterfall","falls","water"}),
       "They are behind you and you dare not turn around to look. The roar "+
       "of the water reminds you just how far up you are.\n");
   add_item(({"mountain","mountains","cliff"}),
       "You are climbing the craggy cliff of the mountain, veiled but "+
       "relatively untouched by the pounding force of the falls. Sharp "+
       "edges portrude the heights of the cliff, threatening "+
       "to impale or cut you, but also providing the footing necessary to "+
       "climb up or down.\n");
   add_item(({"light","sunlight","opening"}),
       "Light seems to be coming from an opening further up the cliff. You "+
       "think you can climb up to it.\n");
   add_item(({"cavern","floor"}),
       "It is below you, you can climb down to it.\n");

   add_prop(ROOM_I_INSIDE,1);
}

/*
** INIT - add commands
*/
void init() {
   ::init();
   add_action(do_climb,"climb");
}

/*
** CLIMB - allows player to "climb up" or "down"
*/
int do_climb(string Parms) {
   string *parm;
   object destup=(LROOM->get_this_object());
   object destdn=(F1ROOM->get_this_object());

   if (!(Parms)) { write("Climb where?\n"); return 1; }
   parm=explode(Parms," ");

   if (member_array("up",parm)>=0)
      {
      write("You climb up the side of the cliff and come out from behind "+
            "the falls onto a ledge.\n");
      tell_room(TO,QCTNAME(TP)+" climbs up the cliff into the sunlight.\n",
                                 TP);
      tell_room(destup,QCTNAME(TP)+" climbs up the cliff from behind the "+
                                   "falls onto the ledge.\n",TP);
      TP->move_living("M",destup);
      return 1;
      }
   if (member_array("down",parm)>=0)
      {
      write("You climb down the side of the cliff onto the floor of the "+
            "cavern behind the falls.\n");
      tell_room(TO,QCTNAME(TP)+" climbs down the cliff onto the floor of "+
                               "the cavern.\n",TP);
      tell_room(destdn,QCTNAME(TP)+" climbs down from the cliff above.\n",
                                   TP);
      TP->move_living("M",destdn);
      return 1;
      }

   write("Climb where? up or down?\n");
   return 1;
}

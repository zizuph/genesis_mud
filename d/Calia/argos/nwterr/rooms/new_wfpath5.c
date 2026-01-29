
/* Road to the waterfall
**
** History
** Date        Coder       Action
** ---------------  ----------------------
** 2/22/97   Zima          Created
** 5/25/98   Jaacar  Added Stonewalker Entrance
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include "wfall.h"
#include STONE_HEADER

/* prototypes */
int do_climb(string Parms);

int
is_stone(object player)
{
    return player->query_guild_name_occ() == GUILD_NAME;
}

/* room definition */
void create_room() {
   set_short("At the base of a waterfall");
   set_long(
       "You stand in awe of a magnificent waterfall which crashes out of the "+
       "heights of the mountains to the west. The water cascades over the "+
       "cliffs of the mountains into the rapids of the river which barrel "+
       "south through the foothills. Large boulders are lying along "+
       "the base of the waterfall between the river's edge and the base of "+
       "the crushing cataract. There is a small stone altar here, worn by "+
       "years of rain and wind, it faces the falls. The forest of the "+
       "foothills grows up to the edge of the sheer mountains to the west, "+
       "leaving the only way out along the river's bank to the south.\n");

   add_item(({"waterfall","cataract"}),
       "The waterfall tumbles over the top of the high mountains to the "+
       "west, cascading down the side of the mountains, into a crushing "+
       "vortex at the base, where the force of the water crashes into "+
       "mounds of boulders.\n");
   add_item(({"mountains","cliffs"}),
       "The mountains tower straight up to the west, overshadowing the "+
       "forested foothills all around you. The waterfall tumbles over "+
       "the cliffs at the mountains tops high above.\n");
   add_item(({"river","rapids"}),
       "The river forms here, a vortex of rapids created by the water "+
       "cascading off the mountains, flowing south through the foothills.\n");
   add_item("foothills",
       "They roll along the base of the mountains to the north and east, "+
       "heavily wooded by a thick forest.\n");
   add_item("forest",
       "Composed of towering hardwoods sprinkled with pink and white "+
       "dogwoods, the forest coats the foothills, growing right up to "+
       "the edge of the mountains.\n");
   add_item("altar",
       "It is a simple stone altar with a square top balanced on a "+
       "rough cylinder of stone. It seems to be focused toward "+
       "the falls.\n");
    add_item(({"top","square top"}),"Upon close examination of the "+
        "square top, you notice a small indentation.\n");
   add_item("boulders",
       "They lie in mounds along at the foot of the falls, as if they "+
       "were carried and dropped over the mountains' edge by the "+
       "force of the water. They extend from the edge of the forming "+
       "river up to and under the falls. They look very slippery and "+
       "dangerous.\n");
   add_item("bank",
       "The bank of the river is dotted with boulders and follows "+
       "the rapids of the river on their way south.\n");

   add_exit("wfpath4","south",0);
    clone_object(INDENTATION)->move(TO,1);
}

public void init() {
   ::init();
   add_action(do_climb,"climb");
}

int do_climb(string Parms) {
   string *parm;
   object dest=(BROOM->this_object());

   if (!(Parms)) return 0;

   parm=explode(Parms," ");
   if ((member_array("mountain",parm)>=0)||
       (member_array("mountains",parm)>=0)||
       (member_array("cliff",parm)>=0)||
       (member_array("cliffs",parm)>=0)||
       (member_array("falls",parm)>=0)||
       (member_array("waterfall",parm)>=0))
       {
      write("You are not close enough to climb there.\n");
      return 1;
   }
   if ((member_array("boulder",parm)<0)&&(member_array("boulders",parm)<0)) {
      write("Climb onto what?\n");
      return 1;
   }

   if ((TP->query_skill(SS_CLIMB)) < BCLIMB_SKILL) {
      write("It is too dangerous for you to climb onto the boulders.\n");
      return 1;
   }

   write("You carefully climb out onto the slick boulders nearing the "+
         "falls.\n");
   tell_room(TO,QCTNAME(TP)+" climbs out onto the boulders nearing the "+
                            "falls.\n",TP);
   tell_room(dest,QCTNAME(TP)+" climbs up from the bank onto the boulders "+
                              "with you.\n",TP);
   TP->move_living("M",BROOM);
   return 1;
}


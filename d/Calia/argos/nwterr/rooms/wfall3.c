/* At the top of the falls
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/22/97   Zima          Created
** 21/8/01   Maniac        Fixed climb dest 
** 8/10/03   Jaacar        Added Flesh Golems
** 
** Notes:
** Special exits:
**   "climb up/down"
*/
inherit "/std/room";
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "wfall.h"

#define NUM 2
#define THIS this_object()

/* prototypes */
int do_climb(string Parms);

object this, *golem = allocate(NUM);

void
make_monster(int i)
{
    golem[i] = clone_object("/d/Calia/argos/nwterr/monsters/flesh_golem");
    golem[i]->move(this);
    tell_room(this, QCTNAME(golem[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!golem[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

/* room definition */
void create_room() {
   set_short("On a ledge at the top of the falls");
   set_long(
       "You are on a ledge at the top of the falls of a large river, the "+
       "water cascading over the cliff's edge crashing into the valley "+
       "below. You have a breathtaking view of the foothills and valley to "+
       "the east, while a dense forest of evergreens grows all around the "+
       "ledge and the mountaintops in the other directions. A small path "+
       "leads through the forest to the north.\n");
   add_item("ledge",
       "It sticks out from the edge of the cliff, so close to the falls "+
       "that you are getting wet standing here. The ledge curves down "+
       "to the sides of the cliff behind the falls, and you might be "+
       "able to climb down them.\n");
   add_item(({"cliff","cliffs"}),
       "The cliff drops straight down the side of the mountain to the "+
       "foothills below, the river rushing over the edge forming the "+
       "magnificent falls which capture your attention. It seems you "+
       "could climb down the cliff behind the falls.\n");
   add_item("river",
       "It a river here at the top of the mountains, flowing from "+
       "somewhere to the north, cascading over the edge of the cliff "+
       "into the foothills below.\n");
   add_item(({"waterfall","falls"}),
       "The waterfall rushes over the edge of the cliff and down the "+
       "straight side of the mountain, pounding the foothills below.\n");
   add_item(({"view","foothills","valley"}),
       "As you look out to the east over the edge of the cliff, you see "+
       "the foothills which roll along the eastern edge of this north/"+
       "south mountain chain. Further beyond to the east is a verdant "+
       "valley, the river which forms from the falls running southeastward "+
       "into it. In the center of the valley you see the buildings of a "+
       "large city.\n");
   add_item(({"mountain","mountains","mountaintops","chain"}),
       "You are at near the summit of one of the mountains which form "+
       "a long chain running north and south. The mountains here are "+
       "heavily forested with evergreen trees.\n");
   add_item(({"forest","trees","evergreens"}),
       "A thick forest of evergreens grows all around, blanketing the "+
       "mountaintops with a dark green coat.\n");
   add_exit("wfpath6","north",0);
   this = THIS;
   set_alarm(1.0, 0.0, reset_room);

}

/*
** INIT - add commands
*/
void init() {
   ::init();
   add_action(do_climb,"climb");
}

/*
** CLIMB - allows player to "climb down"
*/
int do_climb(string Parms) {
   string *parm;
   object dest=(F2ROOM->get_this_object());

   if (!(Parms)) { write("Climb where?\n"); return 1; }
   parm=explode(Parms," ");

   if (member_array("down",parm) >= 0) {
      if (TP->query_skill(SS_CLIMB) < CCLIMB_SKILL)
         write("It is too dangerous for you to climb down.\n");
      else {
         write("You climb off the ledge onto the side of the cliff "+
               "behind the waterfall.\n");
         tell_room(TO,QCTNAME(TP)+" climbs down off the ledge onto the "+
                      "side of the cliff and disappears behind the "+
                      "waterfall.\n",TP);
         tell_room(dest,QCTNAME(TP)+" climbs down from the cliff above.\n",
                       TP);
         TP->move_living("M", dest);
      }
      return 1;
   }

   write("Climb where? down?\n");
   return 1;
}

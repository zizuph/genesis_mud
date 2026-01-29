/* Northern Path through dark forest around Kretan Camp
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 12/2/95     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include "reduce.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define KRETAN_LIST ({"sentry/sentry3","sentry/sentry3"})
#define  ORIGIN_MSG   " steps out from the woods"
#include "sentry.h"
#include "kr_reset.h"

/* room definition */
void create_room() {
   set_short("A path through a dark forest");
   set_long(
      "You are at the end of a newly made path through a dark forest. "+
      "Towering black pines populate the woods, their long needles look "+
      "sharp enough to draw blood. The branches of the pines grow so "+
      "thickly all around that the only way out seems to be along the path "+
      "to the southwest.\n");
 
    add_item(({"forest","trees","woods"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
    add_item("branches",
        "They grow thickly from the crowded trees, their spiny needles "+
        "warning of any contact. Some branches seem to have been broken "+
        "through to the southeast, as if some creatures have crawled through "+
        "them several times.\n");
 
    add_item("sounds",
       "You don't see anything moving...you wonder what is making them.\n");
    add_item("sun",
       "You can't see it, though you can tell it is daytime.\n");
    add_item(({"cones","pine cones"}),
       "You see some hanging high from the branches of the black pines.\n");
    add_item("path",
       "It looks rather new, and leads to the southwest.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"npath5","southwest",0);
    reset_room();
}
 
int do_crawl(string parms) {
   string *parm;
   object Tp=this_player();
 
   if (!parms) { write("Crawl where?\n"); return 1; }
   parm=explode(parms," ");
   if (member("branches",parm)==-1) { write("Crawl where?\n"); return 1; }
 
   write("You crawl through the branches, sharp needles scratching your "+
         "hands and face painfully.\n");
   environment(Tp)->set_dircmd(parms);
   Tp->move_living("into the branches",SWTERR_DIR+"rooms/r29");
   return 1;
}
 
void init() {
   ::init();
   add_action("do_crawl","crawl");
}

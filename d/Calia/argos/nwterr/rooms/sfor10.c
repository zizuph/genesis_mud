/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NumSatyrs 3
#include "sfornpcs.h"
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "You tromp through the deep underbrush into one of the darker "+
       "parts of the forest, the trees growing very close to each other "+
       "here allowing very little sunlight to fall to the forest floor. "+
       "To the southeast you see the ruins of some small, long-forgotten "+
       "shrine setting in the midst of the woods.\n");
 
#include "sfordesc.ext"
   add_item(({"shrine","ruins"}),
            "It seems to be just a group of crumbling marble pillars set "+
            "in a circle, choked by green vines of the forest. Perhaps "+
            "you should get a closer look.\n");
   add_item("vines","They curl around the pillars of the shrine.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"sfor11",  "west",0);
   add_exit(ROOM_DIR+"sfor14",  "east",0);
   add_exit(ROOM_DIR+"sfor9",   "northwest",0);
   add_exit(ROOM_DIR+"sforruin","southeast",0);
   set_alarm(5.0,0.0,"reset_room");
}

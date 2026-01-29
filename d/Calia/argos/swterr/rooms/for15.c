/*
** Evil forest in Southwestern Territory of Argos
**
** Special: entrance/exit to this room from outside world is by
**          special command "crawl through branches"
**
** History:
** Date         Coder       Action
** 12/14/94     Zima        Created
** 8/15/96      Zima        added exit to kretan camp
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A dark forest");
   set_long(
      "You are standing in a mysteriously evil part of the dark forest.  " +
      "Towering pine trees with rough black bark and branches, covered "  +
      "in strangley black needles, which look sharp enough to pierce " +
      "armour, surround you on all sides.  You feel like you are " +
      "being watched.  A small path leads west and southeast through the " +
      "dark trees.\n");
 
    add_item(({"forest","trees"}),
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n");
 
    add_item("branches",
        "Black as the night, the branches of the pine trees are covered " +
        "in black needles, which look sharp enough to pierce armour.\n");
    add_item("path",
        "It is a very narrow path through the thick forest, leading "+
        "west and southeast.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"for14","west",0);
    add_exit(KRCAMP_DIR+"rooms/npath1","southeast",0);
}

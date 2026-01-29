/*
** Evil forest in Southwestern Territory of Argos
**
** Special: entrance/exit to this room from outside world is by
**          special command "crawl through branches"
**
** History:
** Date         Coder       Action
** 12/14/94     Zima        Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A dark forest");
   set_long(break_string(
      "You are standing in a mysteriously evil part of the dark forest.  " +
      "Towering pine trees with rough black bark and branches, covered "  +
      "in strangely black needles, which look sharp enough to pierce " +
      "armour, surround you on all sides.  There is a small path " +
      "which leads southwest through the dark trees, while you see an " +
      "opening in the branches to the north which seems to have " +
      "been made by some creature.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "black needles sharp enough to cut.\n",70));
 
    add_item(({"opening","pine branches","branches"}), break_string(
       "There is a small hole which has been made by some creature through " +
       "the branches of the dark pines.  You think you might be able " +
       "to crawl through them, if you don't mind getting stuck by " +
       "the deadly needles.\n",70));
 
    add_item("through branches", break_string(
       "There is a small hole which has been made by some creature through " +
       "the branches of the dark pines.  You think you might be able " +
       "to crawl through them, if you don't mind getting stuck by " +
       "the deadly needles.\n",70));
 
    add_cmd_item("through branches","crawl","@@enter");
 
    /* exits */
    add_exit(ROOM_DIR+"for15","east",0);
    add_exit(DEPHTEMP_DIR+"rooms/tdpath1","southwest",0);
}
int blocked() {
   write("That path has been temporarily blocked.\n");
   return 1;
}
 
enter()
{
    write(break_string(
          "You crawl through the branches, sharp needles scratching " +
          "your hands and face painfully.\n",70));
    environment(this_player())->set_dircmd("through branches");
   this_player()->move_living("into the sharp branches",
                              ROOM_DIR+"for9");
   return 1;
}

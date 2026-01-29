/* ARGOS - SWTERR - Dirt road along south bank of river
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 11/10/95  Zima       Created
** 02/08/03  Jaacar       Added exit to Spirit Circle Temple
**                        through the branches.
**
*/
/* inherits/includes */
inherit  "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A dirt road along a river");
   set_long(
      "You are at the end of a dirt road which leads onto a bridge over "+
      "the river to the east, and continues north along the river's western "+
      "bank. A forest of dark pine trees grows thickly all around, "+
      "their long black needles dancing in the breeze like small "+
      "daggers.\n");
 
   add_item("bridge",
      "It is a study oak bridge, slightly arched in the middle, which "+
      "spans the width of the river. You can walk onto it to the "+
      "east.\n");
   add_item(({"forest","pines","trees"}),
      "A dark forest of towering pines grows thickly to the west, the long "+
      "needles of the trees looking sharp enough to draw blood.\n");
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows a river along its western bank.\n");
   add_item(({"city","Argos","argos"}),
      "The city lies on the eastern side of the river, across the bridge.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "It provides a great amount of protection for the city of Argos "+
      "which is built on its eastern side.\n");
    add_item(({"needles","branches"}),"The branches of the trees are covered "+
        "with sharp needles, sure to prick the bare skin of any creatures "+
        "that might try to crawl through them.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"r32","north",0);
   add_exit(ROOM_DIR+"sbridge","east",0);
}

int
do_crawl(string str)
{
    if (!str)
        return 0;

    if (!parse_command(str, ({}), "[through] [the] 'branches'")) 
    {
        notify_fail("Crawl where? Through the branches? <crawl through "+
            "branches>\n");
        return 0;
    }

    write("You crawl through the branches, sharp needles scratching "+
        "your hands and face painfully.\n");
    set_dircmd("through branches");
    TP->move_living("into the branches","/d/Calia/guilds/scop/temple/entry_path1");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_crawl,"crawl");
}

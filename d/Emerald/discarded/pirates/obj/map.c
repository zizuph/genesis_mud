/* This obj is cloned by /d/Emerald/pirates/npc/pirate3
*/

inherit "/std/object.c";

#include <stdproperties.h>
#include </sys/macros.h>
#include "defs.h"


void
create_object()
{
   set_name("map");
   set_pname("maps");
   set_adj("old");
   set_adj("very");
   set_long("You think you see words on this map but it is "+
      "so old and faded you are not sure.\n");
}

void
init()
{
   ::init();
   add_action("do_read","read");
}

int
do_read(string arg)
{
   notify_fail("Read what?\n");
   if(!arg || arg != "map")
      return 0;
   else
      {
      write("This is a strange map. All it says is... \n");
      write("Crawl\n");
      write("Crawl\n");
      write("Stagger\n");
      write("Stagger\n");
      return 1;
   }
}

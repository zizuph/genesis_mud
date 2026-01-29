inherit "/std/object.c";

#include <stdproperties.h>
#include </sys/macros.h>
#include "defs.h"


void
create_object()
{
   set_name("tool");
   set_adj("Charon's");
   set_short("Charon's tool");
   set_long("This is Charon's Pirate tool.\n");
}

void
init()
{
   ::init();
   add_action("change_file","chfile");
}


void
change_file()
{
   string line, *line2, name;
   int i;
   for (i = 1; i < 172; i++)
   {
      line = read_file("/d/Emerald/open/pirate_quest.old",i,1);
      line2 = explode(line," ");
      name = line2[0];
      log_file("bits_need_fixing",name+"\n");
      write("Yes");
   }
   write("\n");
   return;
}

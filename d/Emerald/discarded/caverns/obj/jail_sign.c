inherit "/std/object";

#include "defs.h"

void
create_object()
{
   set_short("sign above the east exit");
   set_name("sign");
   add_name("sign above the east exit");
   set_long("It has writing on it.\n");
   
   add_prop(OBJ_M_NO_GET,1);
   
   
   seteuid(getuid());
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
   if(arg != "sign")
      return 0;
   write("The sign says...\n\nPrison for the enemies and "+
      "traitors of the most gratious\n"+
      "Piratas del Diablo\n\n");
   return 1;
}

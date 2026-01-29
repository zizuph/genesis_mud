inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
   set_short("The Charms 'n Trinkets shop");
   set_long(BSN("This quaint little shop looks as if it has fallen "+
      "into disrepair.  Many odd and dusty objects line the old"+
      " wooden shelves, most of which look very silly and useless."+
      "  Sitting on the counter is a small sign.\n"));
   add_exit("/d/Gondor/pelargir/docks/dokst3","east",0);
   add_item(({"odd objects","dusty objects"}),"Though some "+
       "of them are interesting you don't think they hold any actual "+
      "value.  They'd probably break if you touched them.\n");
   add_item("sign","The sign says 'closed for repairs "+
       "DO NOT TOUCH!'\n");
}

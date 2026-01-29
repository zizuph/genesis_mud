
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
create_room()
{
  set_short("Deep within the mining tunnels");
  set_long("You stand deep within one of the many mining tunnels "+
     "that run through the western portion of Khazad-dum. Rough walls "+
     "show signs of mining activity. Loose chunks of rock litter the "+
     "uneven ground. An overturned cart lies off to the side "+
     "of the passage. The tunnel runs off to the southwest and "+
     "east.\n");
 
 
  add_item("cart",
     "Used for moving rock out of the mining tunnels.\n");
 
  add_exit("/d/Shire/khazad/west/random_tunnel","east",0,1);
  add_exit("/d/Shire/khazad/west/tunnel1d","southwest",0,1);
}

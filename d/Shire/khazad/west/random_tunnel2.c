
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
     "uneven ground. A large boulder sits near the southern wall. "+
     "The straight tunnel runs off to the east and west.\n");
 
  add_prop("boulder",
     "Halfway to the ceiling in height this large boulder "+
     "partially obstructs your passage to the west.\n");
 
  add_exit("/d/Shire/khazad/west/tunnel3b","east",0,1);
  add_exit("/d/Shire/khazad/west/random_tunnel","west",0,1);
}

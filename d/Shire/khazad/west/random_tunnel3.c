
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
     "uneven ground. The tunnel heads eastwards and to the "+
     "south around a bend.\n");
 
  add_exit("/d/Shire/khazad/west/tunnel2d","east",0,1);
  add_exit("/d/Shire/khazad/west/random_tunnel","south",0,1);
}

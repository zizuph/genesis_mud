inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>
create_room()
{
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);
   set_short("This is Ibun's home.\n");
   set_long("This is the home of Ibun. It seems to be " +
          "a room inside a mountain, but somehow you feel transported " +
          "to another time. On the wall you can see a huge painting, " +
          "but there are no signs of furniture to be seen.\n");
 
   add_item("painting","You can see three dwarves on this painting. " +
          "One seems to be older and is surrounded by two younger " +
          "ones that apparently are his two sons. They are posing in " +
          "front of a rocky and bare from vegetation hill, in " +
          "what seems to be West Beleriand.\n");
   add_exit("/d/Rhovanion/ibun/workroom","work");
}

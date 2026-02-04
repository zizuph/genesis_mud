
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/dark/"

create_room(){
   
   set_short("Tunnel");
   set_long("This tunnels is carved from deep black rock, veined\n"
      +"with lines of red carnelian and sardonyx. It seems as though\n"
      +"it is of better work than the most of the area.\n"
      +"A set of stairs leads down deeper into the earth. The tunnels\n"
      +"lead northeast-southwest.\n"
   );
   
   add_item("sardonyx", "A stone of multi-colors, it is semi-precious.\n");
   add_item("carnelian", "A red semi-precious stone. It occurs in veins\n"
      +"in this tunnel area.\n");
   
   add_exit(PATH + "stair1", "down", 0);
   add_exit(PATH + "ne2", "northeast", 0);
   add_exit(PATH + "n1", "southwest", 0);
   
   
}

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/dark/"

#define FOREMAN "/d/Avenir/common/dark/mon/foreman"
#define WORKER "/d/Avenir/common/dark/mon/troll_w"

reset_room()
{
    int workers;
    
    if (!present("foreman")) {
        clone_object(FOREMAN)->move_living("arrives", this_object());
        if (!present("troll")) {
            workers = 2 + random(3);
            while (workers--) 
                clone_object(WORKER)->move_living("arrives", this_object());
        }
    }
}

create_room(){
   
   set_short("Tunnel");
   set_long("This tunnels is carved from deep black rock, veined\n"
      +"with lines of red carnelian and sardonyx. It seems as though\n"
      +"it is of better work than the most of the area.\n"
      +"The tunnels lead northeast-southwest.\n"
   );
   
   add_item("sardonyx", "A stone of multi-colors, it is semi-precious.\n");
   add_item("carnelian", "A red semi-precious stone. It occurs in veins\n"
      +"in this tunnel area.\n");
   
   add_exit("/d/Avenir/common/dark/l1/stair3", "northeast", 0);
   add_exit(PATH + "ne1", "southwest", 0);
   reset_room();
}

ward(){
  write("A magic ward blocks the tunnel.\n");
  return 1;
   
}


inherit "std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"


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
   set_long("A darkened tunnel, its walls covered with fungi, the\n" +
      "the ground slick with fetid water and moss.\n" +
      "The tunnel leads east and a haunting looking cave is to\n" +
      "the southwest.\n");
   
   add_item("walls", "Worn smooth, but not natural tunnels.\n");
   add_item("fungi", "Foul smelling fungus that decays all matter.\n");
   add_item("moss", "Its is a foul blackish green moss.\n");
   add_item("water", "Fetid and contaminated with dirt and minerals.\n");
   
   add_exit(PATH + "w3", "east", 0);
   add_exit("/d/Avenir/common/dark/l1/stair2", "southwest", 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   reset_room();
   
}

ward(){

write("A magic ward prevents you from entering the cavern.\n");
return 1;
}



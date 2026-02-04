#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

public string*
query_moving_object_list()
{
    return ({PATH + "mon/dark_elf", 
            PATH + "mon/dark_elf",
            PATH + "mon/dark_elf",
            PATH + "mon/dark_elf",
            PATH + "mon/dark_elf",
            PATH + "mon/dark_elf",
            });
}
create_room(){
   
   set_short("Tunnel");
   set_long("A darkened tunnel, its walls covered with fungi, the\n" +
      "the ground slick with fetid water and moss.\n" +
   "The tunnels lead east-west.\n"
      
   );
   add_item("walls", "Worn smooth, but not natural tunnels.\n");
   add_item("fungi", "Foul smelling fungus that decays all matter.\n");
   add_item("moss", "Its is a foul blackish green moss.\n");
   add_item("water", "Fetid and contaminated with dirt and minerals.\n");
   
   add_exit(PATH + "e4", "east", 0);
   add_exit(PATH + "e2", "west", 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
    reset_room();
   
}


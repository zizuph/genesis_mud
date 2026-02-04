inherit "std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/dark/"

reset_room(arg){
   object drake;
   if (present("drake")) return;
   drake=clone_object(PATH + "mon/drake");
   drake->move(this_object());
}

create_room(){
   
   set_short("Cavern");
   set_long("Although this area is much the same as the rest,\n"
      + "being ridden with slime and fungi, it also has not been\n"
      + "been worked. It is a cavernous hall of nature, full of\n"
      + "fetid waters and putrid things.\n"
   );
   add_item("fungi", "Foul smelling fungus that decays all matter.\n");
   add_item("moss", "Its is a foul blackish green moss.\n");
   add_item("water", "Fetid and contaminated with dirt and minerals.\n");
   
   add_exit(PATH + "se4", "north", 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   
   reset_room();
}


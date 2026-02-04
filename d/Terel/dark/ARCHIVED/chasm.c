
inherit "std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

init(){
add_action("jump", "jump");
::init();
}

jump(){
  write("A suicide attempt at best.\n");
  return 1;
}

create_room(){
   
   set_short("Chasm");
   set_long("An abyssmal chasm reaches out across the cavern, like\n"
      +"the mouth of some great demon. A wind rises up from its depths,\n"
      +"upon which rides the smell of death. On the north side of the\n"
      +"chasm is a tall towered fort, from which rays of light flicker\n"
      +"deep into the chasm.\n"
   );
   
   add_item("walls", "Worn smooth, but not natural tunnels.\n");
   add_item("fungi", "Foul smelling fungus that decays all matter.\n");
   add_item("moss", "Its is a foul blackish green moss.\n");
   add_item("water", "Fetid and contaminated with dirt and minerals.\n");
   add_item(({ "fort", "outpost", "keep" }), 
      "It is a small fortress made of deep black stone. It looks to\n"
   +"be heavily guarded. Lights from within it shine out across the\n"
   +"chasm.\n");
   add_item(({"chasm", "pit"}),
    "This abyssmal chasm must be bottomless or else is the entry\n"
   +"to the netherworld. Shadows seems to dance within it.\n");
   
   add_exit(PATH + "n5", "south", 0);
    add_exit("/d/Avenir/common/outpost/chasm_south", "east", 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 1);
   
}


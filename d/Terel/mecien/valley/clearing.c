inherit "std/room";
#include "defs.h";

create_room(){
   
   set_short("Clearing");
   set_long("The forest is thin here, clear open to the\n" +
      "sky. The open area is carpeted with a layer of flowers\n" +
      "and shrubs. The beautiful forest grows thick to the south\n" +
      "and there is a path north of here.\n");
   
   add_item("flowers", "They grow in a thick carpet, living and vibrant\n"
  + "in their many colors.\n");
  add_cmd_item("flower", "pick", "For some reason you decide not to.\n");
   add_exit("/d/Terel/mecien/valley/path4", "north", 0);
   add_exit(PATH + "forest4", "south", 0);
   
}


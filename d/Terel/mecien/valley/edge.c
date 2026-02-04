inherit "std/room";
#include "defs.h";

create_room(){
   
   set_short("Forest Edge");
   set_long("This is the edge of a large forest of beautiful\n" +
      "maples, elms, oaks and many other trees. To the south\n" +
      "is the forest, there is a path north of here. A large\n" +
      "grey stone has been set into the earth here.\n");
   
   add_item(({"grey stone", "stone"}),
         "It is an ancient stone that has been carved with writing\n"
      +"and polished.\n");
  add_cmd_item(({"stone", "writing"}), "read",
    " If we listen, if we hear,\n"
   +" all shall know the time is near.\n"
   +" As our people stand and sing,\n"
   +" we dance about our faerie ring.\n"
);
   add_exit("/d/Terel/mecien/valley/path3", "northeast", 0);
   add_exit(PATH + "forest3", "south", 0);
   add_exit(MAZE, "southwest", 0);
   
}


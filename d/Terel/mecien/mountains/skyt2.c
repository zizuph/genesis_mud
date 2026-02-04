inherit "/std/room";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

int mon;

reset_room(arg){

if(!mon){
mon=clone_object("/d/Terel/mecien/valley/guild/at");
mon->move(this_object());
}
}


create_room(){
   
   set_short("Tower of the Sky");
   set_long(
 "This solemn hall, draped in white silk and golden velvet\n"
+"tapestries, is centered about a large ebony table. Set in the\n"
+"midst of the table is a large blue stone, cracked and opaque.\n"
+"A silver door leads out of the tower.\n"
   );
   

  add_item(({"stone", "blue stone", "sky stone"}),
   "It is a strange azure colour, opaque. It is cracked.\n");
   add_item("tapestries", "They are made of golden velvet, very " +
    "rich and colourful.\n");
  add_cmd_item("stone", "touch", "@@leave");
  add_cmd_item("stone", "polish", "@@leave");
   add_item(({"white silk", "silk"}), 
     "It hangs from the walls and ceiling, like haunting apparitions.\n");
   add_item("door", "It is made of silver and is very ornate.\n");
  add_item("table", "Made of ebony, it looks very strange as if it was "
  + "built\njust to hold something in its center.\n");
   add_cmd_item("door", "open", "It will not open.\n");
   
reset_room();
}

leave(){
write("You touch the blue stone.\n");
write("You are gripped by some strange power!\n");
this_player()->move_living("is taken away by a mysterious cloud",
  "/d/Terel/mecien/mountains/skyt1");
return 1;
}


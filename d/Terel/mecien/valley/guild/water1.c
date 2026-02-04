/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define PATH  "/d/Terel/mecien/valley/guild/"
#define TP  this_player()

init(){
   add_action("swim", "swim");
   add_action("dive", "dive");
   ::init();
}

dive(){
   write("You dive into the waters.\n");
   write("It is too deep and cold here, so you return to the surface.\n");
   TP->add_fatigue(-10);
   say(QCTNAME(TP) + " dives underwater, but returns quickly.\n");
   return 1;
}

swim(string str){
   if(!str){
      write("You swim about the frigid waters.\n");
      TP->add_fatigue(-5);
      say(QCTNAME(TP) + " swims about the frigid waters.\n");
      return 1;
   }
   if(str == "south"){
      if(TP->query_skill(SS_SWIM)< 5){
         write("Your inability in swimming keeps you from going too far.\n");
         return 1;
      }
      write("You swim off to the south.\n");
      say(QCTNAME(TP) + " swims off to the south.\n");
      TP->move(PATH + "water3");
      return 1;
   }
   write("Swim where?\n");
   return 1;
   
}
create_room(){
   set_short("Pool");
   set_long("This frigid water, is fresh and clean. The mists clear\n" +
      "up here, allowing for some light. The pool seems large\n" +
      "and deep. The mountain cliffs form a concave.\n");
   add_item("water", "It is pure and sparkling clean.\n");
   add_item("mist", "Scattered bits of mist over the waters.\n");
   add_item("concave", "The mountain cliffs form a concave in which this\n"
      + "pool naturally rests, like a shell. The concave wall is to\n"
      + "the south.\n");
   add_exit("/d/Terel/mecien/valley/guild/pool", "out", 0);
}

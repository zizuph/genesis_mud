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

dive(string str){
   if(str == "deep"){
      write("You dive down to the depths.\n");
      write("You find a small grotto and enter it.\n");
      say(QCTNAME(TP) + " dives underwater.\n");
      TP->move(PATH + "uwg");
      return 1;
   }
   write("You dive into the waters.\n");
   write("The water is cold, but not too deep here. You see a small\n"
      + "grotto under the water, but you would need to dive deep.\n");
   write("You return to the surface.\n");
   say(QCTNAME(TP) + " dives underwater, but returns quickly.\n");
   TP->add_fatigue(-10);
   return 1;
}

swim(string str){
   if(!str){
      write("You swim about the frigid waters.\n");
      TP->add_fatigue(-5);
      say(QCTNAME(TP) + " swims about the frigid waters.\n");
      return 1;
   }
   if(str == "north"){
      if(TP->query_skill(SS_SWIM)< 5){
         write("Your inability in swimming keeps you from going too far.\n");
         return 1;
      }
      write("You swim off to the north.\n");
      say(QCTNAME(TP) + " swims off to the north.\n");
      TP->move(PATH + "water1");
      return 1;
   }
   write("Swim where?\n");
   return 1;
   
}
create_room(){
   set_short("Pool");
   set_long(
   "This is the southern edge of the majestic concave pool, set\n"
  +"like some divine bath into the side of the mountains. The tall\n"
  +"white cliffs rise high into the misty sky. The water is warmer\n"
  +"here and seems to sparkle off the cliffs.\n"
);
add_item(({"cliff", "cliffs"}), "They are sheer and wet, making it\n"
   + "impossible to climb. The cliff are white, formed of some\n"
  + "soft stone.\n");
add_item("mist", "It descends from the mountains, like spirits from\n"
  + "the heavens come to bring tidings.\n");
   add_item("water", "It is pure and sparkling clean.\n");
   add_item("mist", "Scattered bits of mist over the waters.\n");
}

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

init(){
   add_action("enter", "enter");
   ::init();
}

enter(string str){
   if (str!="water" && str!="pool") return 0;
   if (this_player()->query_skill(SS_SWIM) < 1)
      {
      write("You do not know how to swim.\n");
      say(QCTNAME(this_player()) + " goes near the water, but steps back.\n");
      return 1;
   }
   write("You wade out into the fetid pool.\n");
   write("The water is foul and filled with slime.\n");
   say(QCTNAME(this_player()) + " steps out into the fetid water.\n");
   write("You find the pool rather small and cross to the other side.\n");
   tell_room("/d/Terel/mecien/dark/waters",
     QCTNAME(this_player()) + " steps out of the dark pool.\n");
   this_player()->move_living("M", "/d/Terel/mecien/dark/waters");
   return 1;
}

create_room(){
   set_short("Pool");
   set_long("A pool of fetid and murky water spreads out into\n"
      +"the darkness. The cavern is coated with a sheet of slime\n"
      +"and moss, causing it to be quite slick. Stalagmites and\n"
      +"stalactites fill the cavern like ancient pillars of some\n"
      +"forgotten royal hall.\n");
   add_exit("/d/Terel/mecien/mountains/dcave", "up", 0);
   add_item(({"pool", "water"}),
      "It is putrid and filled with slime.\n");
}


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
   write("You cross the pool to the other side.\n");
   say(QCTNAME(this_player()) + " steps out into the fetid water.\n");
   tell_room("/d/Terel/dark/pool",
     QCTNAME(this_player()) + " steps out from the fetid water.\n");
   this_player()->move_living("M", "/d/Terel/dark/pool");
   return 1;
}

create_room(){
   set_short("Pool");
  set_long("Sounds echo throughout the caverns and collect\n" +
   "in this large grotto-cavern. A fetid pool of water reaches\n" +
    "out along the edges of the cavern. Slime and fungus grows\n" +
    "in great abundance and variety here.\n"
  );
   add_exit("/d/Terel/dark/s1", "north", 0);
   add_item(({"pool", "water"}),
      "It is putrid and filled with slime.\n");
    add_prop(ROOM_I_LIGHT,-1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_ALLOW_STEED, 1);
}

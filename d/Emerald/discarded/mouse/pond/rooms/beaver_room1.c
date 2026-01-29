/* room coded by Elizabeth Cook/Mouse, September 1996 */
inherit "std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "../../mouse.h"

   void create_room() {
     add_prop(ROOM_I_LIGHT,1);
     add_prop(ROOM_I_INSIDE, 1);
     set_short("In the pond");
     set_long("   The water is a bit cooler and deeper than you expected! "+
          "You are surrounded by the many branches the beavers have "+
          "stored under the water to sustain themselves during the long "+
          "winter when the pond freezes over. The fish seem to navigate "+
          "easily through the branches, however, you will find this a "+
          "more daunting task. To the north, beyond the web of "+
          "branches, you see a dark mass rising from the bottom of "+
          "the pond. The silty floor is lushly covered with grasslike "+
          "water plants.\n");
     add_item("branches","Branches from various types of trees, mostly "+
          "weeping willow, suspended in the water.\n");
     add_item("fish", "Smaller, more colorful sunfish and larger, dull "+
          "green bass with slackened jaws darting between the submerged "+
          "branches.\n");
     add_item("mass", "You are not close enough to make out many "+
          "details, you might want to swim north to inspect it more "+
          "thoroughly.\n");
     add_item("plants", "Thin stemmed plants with spiky leaf-like "+
          "protrusions. The plants sway with the movement of the "+
          "water.\n");
     add_exit(ROOT+"pond/rooms/pond_room7","out");
     add_exit(ROOT+"pond/rooms/beaver_room2","swim","@@swim_func",5,1);  
}

int swim_func() {
   object player;
   int skill;
   player= this_player();
   skill= player->query_skill(SS_SWIM);
   if(query_dircmd()!="north")
   {
     write("You would most surely become entangled in the branches and "+
           "drown if you try to swim that direction.\n");
     return 1;
   }
   if(skill<20) {
     write("You don't have enough confidence in your ability to "+
           "swim through the branches.\n");
     return 1;
   }
   return 0;
}

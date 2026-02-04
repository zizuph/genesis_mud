/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define PATH "/d/Terel/mecien/valley/guild/crypt/"

init(){
add_action("pray", "pray");
::init();
}

pray(str){
if(!str){
  write("You pray here for a time.\n");
  write("The dead feel close at hand.\n");
  say(QCTNAME(this_player()) + " prays silently.\n");
  return 1;
}
if(str == "to the dead"){
write("You kneel down and pray before the tombs of the dead.\n");
say(QCTNAME(this_player()) + " kneels down and prays silently.\n");
say("The chamber feels stirred, as if a breeze passed through.\n");
return 1;
}

 write("A feeling of death is near.\n");
 say(QCTNAME(this_player()) + " prays silently.\n");
 return 1;

}

create_room(){
   
   set_short("Crypt");
   set_long(
   "Like the ancient days rising to life, the dead seem free here, their\n"
   +"presence felt within the stone. This vaulted hall, aged stone that has\n"
   +"only begun to crumble, stands silent in a sheet of dust. In the center\n"
   +"of the hall are four stone tombs.\n"
   );
   add_item("tombs", "They are carved stone blocks that house the remains of\n"
     + "the dead. A strange feeling emanates from them, a sanctity not to be\n"
     + "disturbed.\n");
   add_item(({"first tomb", "tomb 1"}),
    "This large stone block is carved with the image of an aged man, he looks\n"
    + "wise and noble, though stern and merciless.\n");
   add_item(({"second tomb", "tomb 2"}),
    "This large stone block is carved with the image of a young man, he wears\n"
    + "a mitre and hold a sceptre. His face is kind and gentle.\n");
   add_item(({"third tomb", "tomb 3"}),
    "This large stone block is carved with the image of a young man, he looks\n"
    + "as though he were asleep. He wears a coronet of leaves.\n");
   add_item(({"fourth tomb", "tomb 4"}),
    "This large stone block is carved with the image of a venerable man, like\n"
    + "a divine being the image seems to radiate holiness.\n");


   add_item("walls", "Smooth gray and white stone.\n");
   add_item("floor", "The floor is a smooth gray stone, set with a pattern\n"
            +"of black swirling karmic designs.\n");
   add_item("dust", "From all the ages this dust has collected.\n");
   add_item(({"designs","karmic designs","patterns"}),
           "They look arcane, but seem to serve no purpose.\n");
   
   add_cmd_item(({"tomb", "first tomb", "tomb 1", "second tomb", "tomb 2",
      "third tomb", "tomb 3", "fourth tomb", "tomb4"}), "open", "@@open_tomb");

   add_exit(PATH + "c2", "north", 0);
   add_exit(MAZE, "west", 0);
   add_exit(MAZE, "south", 0);
   add_exit(PATH + "c1", "east", 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   
}

open_tomb(){
write("Impossible, the tombs have been sealed until the age to come.\n");
write("A feeling of dread permeates your entire being!\n");
this_player()->add_fatigue(-5);
say(QCTNAME(this_player()) + " tries to open a tomb!\n");
return 1;
}



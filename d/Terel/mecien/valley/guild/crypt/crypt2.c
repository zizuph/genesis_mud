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
  write("The dead spirit feels very close at hand.\n");
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
    "This large stone block is carved with the image of a middle-aged man, he\n"
    + "bears a star upon his forehead and is wrapped in a mantle.\n");
   add_item(({"second tomb", "tomb 2"}),
    "This large stone block is carved with the image of a dark aged man. He is\n"
    + "strange looking, perhaps from some foreign land. He wears a tabard with\n"
    + "the image of a tree.\n");
   add_item(({"third tomb", "tomb 3"}),
    "This large stone block is carved with the image of a very old man, he looks\n"
    + "almost like a skelton. He wears a necklace of astrological symbols.\n");
   add_item(({"fourth tomb", "tomb 4"}),
    "This large stone block is carved with the image of old man, he has a long\n"
    + "beard that is braided. In his hands are arcane rods.\n");


   add_item("walls", "Smooth gray and white stone.\n");
   add_item("floor", "The floor is a smooth gray stone, set with a pattern\n"
            +"of black swirling karmic designs.\n");
   add_item("dust", "From all the ages this dust has collected.\n");
   add_item(({"designs","karmic designs","patterns"}),
           "They look arcane, but seem to serve no purpose.\n");
   
   add_cmd_item(({"tomb", "first tomb", "tomb 1", "second tomb", "tomb 2",
      "third tomb", "tomb 3", "fourth tomb", "tomb4"}), "open", "@@open_tomb");

   add_exit(PATH + "c2", "east", 0);
   add_exit(PATH + "c3", "west", 0);
   add_exit(MAZE, "south", 0);
   add_exit(MAZE, "north", 0);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_prop("_can_summon_the_dead", 1);
   
}

open_tomb(){
write("Impossible, the tombs have been sealed until the age to come.\n");
write("A feeling of dread permeates your entire being!\n");
this_player()->add_fatigue(-5);
say(QCTNAME(this_player()) + " tries to open a tomb!\n");
return 1;
}



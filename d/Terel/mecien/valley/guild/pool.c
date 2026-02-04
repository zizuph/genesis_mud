/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
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
 write("You wade out into the pool.\n");
 write("It is very cold.\n");
  say(QCTNAME(this_player()) + " wades out into the misty pool.\n");
 this_player()->move("/d/Terel/mecien/valley/guild/water1");
 return 1;
 }

create_room(){
  set_short("Pool");
  set_long("An ancient pool. It rests quietly against the edge\n" +
           "of the stone of the courtyard. Tall pillars stand at\n" +
           "its border, carved spirals of marble. Mists creep out\n" +
          "across the pool, like spirits of the dead haunting the\n" +
          "edges of the world.\n");
  add_item("pool", "It is a stone resevoir that rests calmly in the mountains.\n");
   add_item("pillars", "They are marble and ring the courtyard.\n");
   add_item("water", "It is crystal clear.\n");
   add_cmd_item("water", "drink", "It is pure and refreshing.\n");
   add_item("mist", "A fine sheet of mist haning over the waters,\n" +
  "it descends from the mountains.\n");
  add_exit("/d/Terel/mecien/valley/guild/entry", "north", 0);
}

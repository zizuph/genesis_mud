/* room coded by Elizabeth Cook/Mouse, October 1996 */

inherit "std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "../../mouse.h"

   void create_room()  {
     set_short("The pond");
     set_long("   You have reached the grassy bank of the pond where "+
          "it opens at the mouth of the stream. Ducks dart into the "+
          "water when you approach, eager to place themselves safely "+
          "at a distance. The trees that flank the pond are well "+
          "interspersed with jagged stumps. A few bare, dead tree "+
          "trunks stand along the edge, drowned by the advancing water "+
          "years before when the pond was formed. A mound of tree "+
          "limbs, branches, and other debris rises like an island in "+
          "the center of the pond. The opposite bank beckons to you "+
          "from across the mouth of the stream. Perhaps you can reach it "+
          "if you walk around the pond.\n");
     add_item("bank","The bank stands about a meter above water level. "+
          "It is covered with lush green grass. Water-smoothened rocks "+
          "line the bank at the water line, laying either just inside the "+
          "edge of water, or on the muddy verge of the bank.\n");
     add_item("pond","This is a large pond, surrounded by trees and "+
          "brimming with animal and plant life. It is vital to the lives "+
          "of many creatures in the surrounding area, who rely on it as "+
          "a source of water and food. It is fed by a stream flowing in "+
          "from the northwest.\n");
     add_item("ducks","A muddy colored female duck with ten fuzzy brown "+
          "brown ducklings swim away from you, parallel to the bank, "+
          "while several sleek, green-headed male and dull "+
          "brown female mallards swim gracefully toward the mound of "+
          "branches and debris in the center of the pond.\n");
     add_item("trees","Many varieties of trees surround the pond, "+
          "mainly birches and willows closest to the pond and maples "+
          "becoming more prevalent further into the woods. Some trees "+
          "appear to have branches and bark stripped from them. There "+
          "are stumps standing between the trees.\n");
     add_item("stumps","These trees were obviously not felled by an axe. "+
          "Rather than a flat, clean surface where the cut was made, "+
          "These stumps are jagged and pointed at the top, as if the "+
          "trees had been whittled away.\n");
     add_item("trunks","They have been stripped of bark and most of their "+
          "branches. The trunks are dead and half-rotted. There are large "+
          "holes in some of the trunks, a few meters above the surface of "+
          "the pond.\n");
     add_item("mound","A tangled pile of limbs and branches. You can "+
          "see some pieces of man-made articles, such as milled boards and "+
          "intricately turned legs of tables and chairs jumbled into the "+
          "chaotic heap.\n");
     add_item("stream","It seems a little daunting, but you might be able "+
          "to swim over to the opposite bank if you don't mind getting "+
          "wet.\n"); 
     add_exit(ROOT+"pond/rooms/pond_room1","north");
     add_exit(ROOT+"pond/rooms/pond_room14","northeast");
     add_exit(ROOT+"pond/rooms/pond_room3","swim","@@swim_func",5,1);
}

int swim_func()  {
   object player;
   int skill;
   player= this_player();
   skill= player->query_skill(SS_SWIM);
   if(query_dircmd()!="south")
 {
     write("What ?\n");
     return 1;
   }
   if(skill<5) {
     write("You are too frightened of the water.\n");
     return 1;
   }
   return 0;
}

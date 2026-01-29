// file name: shore.c
// creator(s): Ilyian, April 1995
// last update: 
// purpose: Entrance to bridge between park and bazaar islands.
// note: 
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

create_room()
{
set_short("Northern shore");
set_long("You stand upon the northern shore of an island that seems "
       +"to be covered in fierce vegetation. Canopies of trees enclose "
       +"a stone path that leads south into what seems to be a clearing, "
       +"and to the north begins a bridge of blackened grey stone. The "
       +"dark waters of the sea swirl around the edge of the shore. You "
       +"are stopped from following the shore to the east and west due "
       +"to powerful hedges that have grown up.\n");

AE(PK+"latch","south",0);
AE(BAZAAR+"green/s_bridge","north",0);

   add_prop(ROOM_I_TYPE, ROOM_BEACH);
add_prop(OBJ_I_CONTAIN_WATER);     //water is available here
add_prop(ROOM_I_LIGHT,1);
IN

AI(({"bridge","stone"}), "The bridge to the north is made from a rough "
   +"grey stone that has blackened to a sooty colour over the years. It "
   +"arches high over the sea, and ends at an island you can see to the "
   +"distand north. In the middle of the bridge, you can make out two "
   +"large statues on either side.\n");
AI(({"water","sea","ocean"}),"The water of surrounding the island is "
   +"completely lightless, so you have no indication of either how "
   +"deep it is, or what hides beneath the surface. It gives you an "
   +"uncomfortable feel, and strange eddies swirl in eerie patterns.\n");
AI(({"vegetation","trees","plants","canopy","tree","trees"}),"This "
   +"entire island seems to contain a myriad of life, so thick "
   +"that it prevents any possibility of movement except along "
   +"the paths that are bordered by hedges or walls. How anything can "
   +"grow under the pale watery light of the Source is beyond you.\n");
AI(("path"),"The path is paved with intricate cobblestones and leads "
   +"south into what seems to be a large clearing.\n");
AI(("shore"),"The shore goes around the island, but you cannot follow along "
   +"it because your way is blocked by hedges on either side.\n");
AI(({"hedge","hedges"}),"Massive hedges have grown up on either side "
   +"of this path, both preventing you from going along the shore and "
   +"stopping you from seeing over them. They are thick with thorns.\n");

  set_searched(0);
  set_search_places(({"shore","edge","water","beach"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(HERB+"nethra");

}
 
reset_room()
{
  set_searched(0);
}

inherit "/std/room";

#include "defs.h"
#include "/d/Shire/lib/herbsearch.c"
#include "/sys/stdproperties.h"

create_room() {
   set_short("grassy field");
   set_long(break_string(
      "You are on a grassy field, standing between the green "
    + "patches of tall grass. The grassy field is being forced aside "
    + "by dense bushes. To the south there is more grass, whereas to the "
    + "north more bushes seem to grow.\n",70));

   add_item(({"bush","dense bush"}), break_string(
      "The dense bushes block the view of whatever is behind them. They "
    + "look like the bushes that commonly grow in the Shire.\n",70));

   add_item(({"ground","grass","tall grass"}), break_string(
      "The grass is tall and green, a pleasure for the eye. There is "
    + "not too much grass growing here.\n",70));

   add_prop(ROOM_I_INSIDE,0);

   add_exit(STAND_DIR + "field1","south",0,1);
   add_exit(STAND_DIR + "field3","north",0,1);

   add_prop(OBJ_I_SEARCH_TIME, 4);
   add_prop(OBJ_S_SEARCH_FUN, "herb_search");
   set_search_places(({"ground","grass","tall grass"}));
   add_herb_file("/d/Gondor/common/herbs/redweed");
   add_herb_file(STAND_HERB + "grass");
}

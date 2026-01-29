inherit "/std/room";

#include "defs.h"
#include "/d/Shire/lib/herbsearch.c"
#include "/sys/stdproperties.h"

create_room() {
   set_short("grassy field");
   set_long(break_string(
      "You are on a grassy field, standing between large green "
    + "patches of tall grass. Every now and then the grassy field is "
    + "interrupted by a dense bush. Far away south you see a glimpse "
    + "of an east-west road.\n",70));

   add_item(({"bush","dense bush"}), break_string(
      "The dense bushes block the view of whatever is behind them. They "
    + "look like the bushes that commonly grow in the Shire.\n",70));

   add_item(({"grass","tall grass"}), break_string(
      "The grass is tall and green, a pleasure for the eye.\n",70));

   /* Enable the searching for grass */
   add_prop(OBJ_I_SEARCH_TIME, 1);
   add_prop(OBJ_S_SEARCH_FUN, "herb_search");
   add_herb_file(STAND_HERB + "grass");

   add_prop(ROOM_I_INSIDE,0);

   add_exit(STAND_DIR + "er8","south", 0);
   add_exit(STAND_DIR + "field2","north", 0);
}

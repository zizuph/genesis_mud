inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
inherit "/d/Gondor/common/lib/herbsearch.c";

create_room() {

  set_short("Offroad");
  set_long("The mist is very dark here. Rubble is strewn everywhere.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the ground. It obscures your vision "
                   +"just enough so you can't make out details in "
                   +"the distance.\n");
  add_exit(ANNUM_DIR + "am2c4", "north", 0, 1, 1);

  add_herb_file(SHIRE_HERB_DIR + "glimmer");
  add_herb_file(SHIRE_HERB_DIR + "glimmer");
  add_herb_file(SHIRE_HERB_DIR + "glimmer");
  add_herb_file(SHIRE_HERB_DIR + "glimmer");
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_prop(OBJ_I_SEARCH_TIME,8);
  
  set_search_places(({"rubble","rocks"}));
  reset_shire_room();
  
}


reset_shire_room()
{
 set_searched(0);
}

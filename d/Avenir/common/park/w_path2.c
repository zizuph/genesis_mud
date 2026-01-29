// file name: w_path2.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:


inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

create_room()
{
set_short("Western path");
set_long("You are standing on a dirt path leading"
        +" from north to southeast. The path widens a bit here,"
        +" though it is still lined with heavy, uncut foliage"
        +". Thick vines hang down from the trees above you,"
        +" and smaller plants still grow across the pathway,"
        +" hindering your progress. Broken branches and trampled"
        +" turf indicate a freshly-made track leading deeper into"
        +" the underbrush immediately southwest.\n");

AE(PK+"w_path1","southeast",0);
AE(PK+"w_path3","north",0);
AE(PK_JUNG + "lf5", "southwest", 0);

add_item(({"turf", "branches", "broken branches", "track" }),
      "There is evidence of recent passage into the under"
      +"brush southwest of you. Branches have been broken"
      +" as though they had snagged upon armour, and the"
      +" turf bears damage consistent with heavy boots.\n");

add_prop(ROOM_I_LIGHT,1);

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"blueberry");
  add_herb_file(GONDOR+"garlic");
}

reset_room()
{
  set_searched(0);
}

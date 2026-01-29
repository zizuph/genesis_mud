// file name: s_path1.c
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

/* Room 9 */

create_room()
{
set_short("Narrow path");
set_long("This is a narrow dirt path leading"
        +" from north to south. Along the path are crumbling stone walls,"
        +" well-worn by the passage of time. Innumerable small plants"
        +" grow here, impeding your progress by their constant"
        +" presence underfoot. The light is dim due to the heavy overhead"
        +" canopy of trees and other life, and the calls of birds and"
        +" humming of insects hang in the air.\n");

AE(PK+"slope","north",0);
AE(PK+"s_path2","south",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"dill");
  add_herb_file(GONDOR+"holly");
  add_herb_file(SHIRE+"pawnrose");
}

reset_room()
{
  set_searched(0);
}


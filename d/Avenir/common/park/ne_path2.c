// file name: ne_path2.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 4 */

create_room()
{
set_short("Northeast path");
set_long("This is a small section of a narrow dirt path that"
        +" leads from northeast to southwest. It is lined with low,"
        +" crumbling stone walls which have been heavily eroded by time and"
        +" weather. Innumerable roots and plants lay along the"
        +" path, tripping you up at every step. Overhead, you can see only"
        +" the thick canopy of trees and high bushes all around. The sounds"
        +" of wildlife of various sorts fill your ears, not all of it"
        +" pleasant.\n");

AE(PK+"ne_end","northeast",0);
AE(PK+"ne_path1","southwest",0);

add_prop(ROOM_I_LIGHT,1); IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"lianor_berry");
  add_herb_file(GONDOR+"ungolestel");
  add_herb_file(GONDOR+"blueberry");
}

reset_room()
{
  set_searched(0);
}

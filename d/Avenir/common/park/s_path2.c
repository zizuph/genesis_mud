// file name: s_path2.c
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

/* Room 10 */

create_room()
{
set_short("Fork in the path");
set_long("The path forks here, with branches"
        +" heading off to the north, south and west. Low, crumbling"
        +" stone walls lie along its edges, and plants and weeds"
        +" choke the path. The light here is dim due to the thick"
        +" canopy of trees overhead, and the sounds of wildlife reach"
        +" your ears through the still air.\n");

AE(PK+"s_path1","north",0);
AE(PK+"s_path3","south",0);
AE(PK+"w_path1","west",0);

add_prop(ROOM_I_LIGHT,1); IN IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"caraway");
  add_herb_file(GONDOR+"chervil");
  add_herb_file(SHIRE+"pawnrose");
}

reset_room()
{
  set_searched(0);
}


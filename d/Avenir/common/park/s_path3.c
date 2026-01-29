// file name: s_path3.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicorna
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

static object bicorna;

create_room()
{
set_short("Narrow path");
set_long("You stand on a narrow dirt path which"
        +" leads away"
        +" to the north and south. Low stone walls, now"
        +" heavily eroded by many years of time and nature's"
        +" efforts, line the way. Many indigenous plants"
        +" grow here, snagging at your every step, almost"
        +" as if possessing a will of their own. You can"
        +" hear the cries of the creatures of this island"
        +" through the still air.\n");

AE(PK+"s_path2","north",0);
AE(PK+"s_path4","south",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"redweed");
  add_herb_file(GONDOR+"lothore");
  add_herb_file(SHIRE+"parsley");
}

reset_room()
{
  set_searched(0);

  if (!bicorna)
   {
      bicorna = clone_object(PK+"mon/bicorna");
      bicorna->move_living("M", this_object());
    }
}

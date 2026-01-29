// file name: e_path2.c
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

/* Room 40 */

static object bicornbrn;
static object bicorna;

create_room()
{
set_short("Narrow dirt path");
set_long("You stand on a very narrow section of a"
        +" dirt path. A low, crumbling stone"
        +" wall stands nearby, heavily eroded by time's"
        +" influence. Along the path's edges, heavy underbrush"
        +" grows, while weeds snag at your heels and impede your"
        +" progress. You may follow the path to the northeast"
        +" or to the south.\n");

AE(PK+"e_path4","northeast",0);
AE(PK+"e_path1","south",0);

add_prop(ROOM_I_LIGHT,1);IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"foxglove");
  add_herb_file(GONDOR+"hemlock");

reset_room();
}

reset_room()
{
  set_searched(0);

  if (!bicorna)
   {
      bicorna = clone_object(PK+"mon/bicorna");
      bicorna->move_living("M", this_object());
    }
  if (!bicornbrn)
   {
      bicornbrn = clone_object(PK+"mon/bicornbrn");
      bicornbrn->move_living("M", this_object());
    }
}

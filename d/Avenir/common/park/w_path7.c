
// file name: w_path7.c
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

static object bicornv;

create_room()
{
set_short("Stone path");
set_long("You are standing on a stone-paved path"
        +" leading from east to southwest. The calls of birds and"
        +" other wildlife fill the air. A heavy canopy of trees and vines"
        +" obscures the light, and dense foliage grows all around the path."
        +"\n");

AE(PK+"w_path8","east",0);
AE(PK+"w_path6","southwest",0);

add_prop(ROOM_I_LIGHT,1); IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"dill");
  add_herb_file(GONDOR+"curugwath");

reset_room();
}

reset_room()
{
  set_searched(0);
  if (!bicornv)
   {
      bicornv = clone_object(PK+"mon/bicornv");
      bicornv->move_living("M", this_object());
    }
}

// file name: e_path1.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicornv
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 41 */

static object bicornv;

create_room()
{
set_short("Narrow dirt path");
set_long("This section of the narrow dirt path turns"
        +" rather sharply, heading away to the north and west."
        +" The vines hang down across the path, while low,"
        +" crumbling stone walls line your way. In the distance,"
        +" you can hear some unnamed beast calling out.\n");

AE(PK+"e_path2","north",0);
AE(PK+"s_path4","west",0);

add_prop(ROOM_I_LIGHT,1);IN

STDEPATH


  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"angurth");
  add_herb_file(GONDOR+"garlic");
  add_herb_file(GONDOR+"dill");
  add_herb_file(GONDOR+"holly");

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


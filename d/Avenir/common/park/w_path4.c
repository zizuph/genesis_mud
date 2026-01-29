// file name: w_path4.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicornblk
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

static object bicornblk;

create_room()
{
set_short("Western path");
set_long("The path here is overgrown with a variety of"
        +" plant life. Heavy vines hang everywhere, and you"
        +" are constantly tripped up by snagging weeds. You could"
        +" probably hack your way through to the west, though it is"
        +" apparent that someone or something meant to keep"
        +" intruders out of that area. You can also easily follow the"
        +" path back to the southeast.\n");

AE(PK+"w_path5","west",0);
AE(PK+"w_path3","southeast",0);

add_prop(ROOM_I_LIGHT,1); IN
STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"redweed");
  add_herb_file(GONDOR+"myrtle");

reset_room();
}

reset_room()
{
  set_searched(0);
  if (!bicornblk)
   {
      bicornblk = clone_object(PK+"mon/bicornblk");
      bicornblk->move_living("M", this_object());
    }
}

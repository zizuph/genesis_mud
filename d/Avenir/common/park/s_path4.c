// file name: s_path4.c
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

static object bicornb;
static object bicornv;

create_room()
{
set_short("Fork in the path");
set_long("The path splits here, allowing you to head"
        +" to the north, south and east."
        +"  Numerous plants and underbrush bar the way, constantly"
        +" impeding your progress. The light here is dim due to the"
        +" density of the life all around you. You"
        +" can hear the calls of the birds and beasts of the island,"
        +" and the hum of insects.\n");

AE(PK+"s_path3","north",0);
AE(PK+"s_path5","south",0);
AE(PK+"e_path1","east",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"garlic");
  add_herb_file(GONDOR+"ginger");
  add_herb_file(SHIRE+"parsley");
}

reset_room()
{
  set_searched(0);

  if (!bicornb)
   {
      bicornb = clone_object(PK+"mon/bicornb");
      bicornb->move_living("M", this_object());
    }
  if (!bicornv)
   {
      bicornv = clone_object(PK+"mon/bicornv");
      bicornv->move_living("M", this_object());
    }
}

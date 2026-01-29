// file name: w_path1.c
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

static object bicornblk;
static object bicornbrn;
static object bicorna;
static object bicornb;
static object bicornv;

create_room()
{
set_short("Turn in the path");
set_long("This western branch of the narrow dirt path"
        +" turns here to head from east to northwest. Heavy underbrush"
        +" grows along the sides of the path, and persistent weeds and"
        +" other small plants continue to snag your feet with every step."
        +" You can see a small enclosed area to the north.\n");

AE(PK+"s_path2","east",0);
AE(PK+"w_path2","northwest",0);
AE(PK+"cell3","north",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"catnip");
  add_herb_file(GONDOR+"holly");

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
  if (!bicornbrn)
   {
      bicornbrn = clone_object(PK+"mon/bicornbrn");
      bicornbrn->move_living("M", this_object());
    }
  if (!bicorna)
   {
      bicorna = clone_object(PK+"mon/bicorna");
      bicorna->move_living("M", this_object());
    }
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

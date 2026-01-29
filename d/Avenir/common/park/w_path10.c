// file name: w_path10.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicornb
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
set_short("Stone path");
set_long("The well-paved stone path"
        +" turns sharply here. It continues back to the southwest,"
        +" lined by dense brush and foliage. To the southeast,"
        +" it enters a large, cobblestone-paved courtyard."
        +" The trees rustle slightly overhead. With no wind down"
        +" here, you can only assume that some creature must be"
        +" close by.\n");

AE(PK+"court_w","southeast",0);
AE(PK+"w_path9","southwest",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"parsley");

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

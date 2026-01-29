// file name: e_path9.c
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

/* Room 31 */

static object bicorna;
static object bicornb;
static object bicornc;

create_room()
{
set_short("Stone path");
set_long("You stand at the northern end of"
        +" a long, well-built stone path. The way is paved with"
        +" concise square-cut blocks of stone. The pathway"
        +" is bordered by dense foliage, which is somehow"
        +" held back from"
        +" the path. Overhead, a heavy"
        +" canopy of life obscures the light.  The path turns here"
        +" to head both west and south.\n");

AE(PK+"court_e","west",0);
AE(PK+"e_path8","south",0);

add_prop(ROOM_I_LIGHT,1);IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"parsley");
  add_herb_file(GONDOR+"caraway");
  add_herb_file(GONDOR+"morgurth");

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
  if (!bicornb)
   {
      bicornb = clone_object(PK+"mon/bicornb");
      bicornb->move_living("M", this_object());
    }
  if (!bicornc)
   {
      bicornc = clone_object(PK+"mon/bicorna");
      bicornc->move_living("M", this_object());
    }
}

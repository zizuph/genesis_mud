// file name: e_path6.c
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

/* Room 35 */

static object bicornb;
static object bicornblk;
static object bicornv;

create_room()
{
set_short("North-south path");
set_long("The path continues on its way here, leading from"
        +" north to south. The stones begin to be"
        +" interspersed here, with dirt and small plants in between."
        +"  The foliage and growth around the path's edges encroach"
        +" slightly, hindering your passage with their twisted limbs"
        +" and dangling vines. You may follow the path, or enter"
        +" a small walled-off area to the southwest.\n");

AE(PK+"e_path7","north",0);
AE(PK+"e_path5","south",0);
AE(PK+"cell6","southwest",0);

add_prop(ROOM_I_LIGHT,1);IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"parsley");
  add_herb_file(GONDOR+"coccinea");
  add_herb_file(GONDOR+"chervil");

reset_room();
}

reset_room()
{
  set_searched(0);


  if (!bicornb)
   {
      bicornb = clone_object(PK+"mon/bicornb");
      bicornb->move_living("M", this_object());
    }
  if (!bicornblk)
   {
      bicornblk = clone_object(PK+"mon/bicornblk");
      bicornblk->move_living("M", this_object());
    }
  if (!bicornv)
   {
      bicornv = clone_object(PK+"mon/bicornv");
      bicornv->move_living("M", this_object());
    }
}

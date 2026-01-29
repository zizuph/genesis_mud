// file name: e_path7.c
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

/* Room 33 */

static object bicornbrn;
static object bicornblk;

create_room()
{
set_short("Stone path");
set_long("You are standing on a finely-paved stone"
        +" path. All about you hang heavy plants and vines,"
        +" and a few smaller weeds grow among the stones here,"
        +" snagging at your heels as you pass. The path continues"
        +" on to the northwest and south, while a small enclosed"
        +" area lies to the southeast.\n");

AE(PK+"e_path8","northwest",0);
AE(PK+"e_path6","south",0);
AE(PK+"cell5","southeast",0);

add_prop(ROOM_I_LIGHT,1);IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"lianor_berry");
  add_herb_file(GONDOR+"curugwath");
  add_herb_file(GONDOR+"ginger");

reset_room();
}

reset_room()
{
  set_searched(0);

  if (!bicornbrn)
   {
      bicornbrn = clone_object(PK+"mon/bicornbrn");
      bicornbrn->move_living("M", this_object());
    }
  if (!bicornblk)
   {
      bicornblk = clone_object(PK+"mon/bicornblk");
      bicornblk->move_living("M", this_object());
    }
}

// file name: e_path8.c
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

/* Room 32 */

create_room()
{
set_short("Stone path");
set_long("The stone-paved path curves here,"
        +" heading off to the north and southeast. The vines and underbrush"
        +" seem a little more free here, and a few are strewn across"
        +" your path. Through the still air comes the call of"
        +" a wild birds.\n");

AE(PK+"e_path9","north",0);
AE(PK+"e_path7","southeast",0);

add_prop(ROOM_I_LIGHT,1);IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"pawnrose");
  add_herb_file(GONDOR+"attanar");
  add_herb_file(GONDOR+"catnip");
}

reset_room()
{
  set_searched(0);
}

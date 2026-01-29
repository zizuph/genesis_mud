// file name: e_path4.c
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

/* Room 38 */

create_room()
{
set_short("Dirt path");
set_long("The dirt path continues here, widening to"
        +" the northeast and narrowing down to the southwest. Underbrush"
        +" and snagging vines cover the path, hindering your"
        +" progress. Small weeds snag at your feet, slowing you"
        +" further down.\n");

AE(PK+"e_path5","northeast",0);
AE(PK+"e_path2","southwest",0);

add_prop(ROOM_I_LIGHT,1);IN

GEPATH
  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"redweed");
  add_herb_file(GONDOR+"sumac");
  add_herb_file(GONDOR+"redweed");
}

reset_room()
{
  set_searched(0);
}


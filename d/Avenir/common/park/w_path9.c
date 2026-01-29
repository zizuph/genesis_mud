// file name: w_path9.c
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

create_room()
{
set_short("Stone path");
set_long("You are standing on a stone-paved path."
        +" It is lined by dense foliage and hanging vines."
        +" The path curves here from south to northeast,"
        +" and a small clearing lies to the north. In the still air,"
        +" you can hear the cries of the island's indigenous"
        +" wildlife.\n");

AE(PK+"w_path10","northeast",0);
AE(PK+"w_path8","south",0);
AE(PK+"latch","north",0);

add_prop(ROOM_I_LIGHT,1); IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"coccinea");
  add_herb_file(SHIRE+"parsley");
}

reset_room()
{
  set_searched(0);
}

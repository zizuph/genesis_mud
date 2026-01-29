
// file name: w_path3.c
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
set_short("Western path");
set_long("The western path widens further here."
        +"  Plants and weeds still choke the way, but the"
        +" underbrush has been cut back, apparently fairly recently."
        +" The path takes a slight bend, leading off to the south"
        +" and northwest. In the distance you can hear the call of"
        +" some unidentifiable wild creature.\n");

AE(PK+"w_path2","south",0);
AE(PK+"w_path4","northwest",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"lianor_berry");
}

reset_room()
{
  set_searched(0);
}

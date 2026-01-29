// file name: ne_path1.c
// creator(s): Ilyian (from the files by Farlong)
// last update: 
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "park.h"


create_room()
{
set_short("Northeast path");
set_long("The narrow dirt path heads off here to the"
        +" northeast and southwest. Low stone walls stand nearby, and the"
        +" air is filled with the buzzing of insects, the chirping"
        +" of birds, and the calls of other creatures, some unnamed."
        +" Vines and other plants are all around, seeming to close in on you"
        +" in menacing fashion. What little light there is here is heavily"
        +" filtered"
        +" by the trees and other overhead cover.\n");

AE(PK+"ne_path2","northeast",0);
AE(PK+"slope","southwest",0);

add_prop(ROOM_I_LIGHT,1); IN

GEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(SHIRE+"huckleberry");
  add_herb_file(GONDOR+"suranie");
  add_herb_file(GONDOR+"blueberry");
}

reset_room()
{
  set_searched(0);
}

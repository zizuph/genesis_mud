// file name: w_path6.c
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
set_long("The widened path is now paved with heavy, square"
        +" stones. They are arrayed in perfect perpendicularity, and lead"
        +" onward to the northeast. Heavy vines and foliage still hang around"
        +" you, lining the path, but it is clear here of the nagging"
        +" plants that grow across the path and make progress difficult."
        +" There is also a large, stone-walled room lying to the south."
        +"\n");

AE(PK+"w_path7","northeast",0);
AE(PK+"w_path5","south",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(HERB+"carlith");
  add_herb_file(SHIRE+"pawnrose");
}

reset_room()
{
  set_searched(0);
}

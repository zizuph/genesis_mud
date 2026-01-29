// file name: w_path5.c
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
set_short("Walled room");
set_long("You have entered a walled-off room."
        +" This area is clear of vines and encroaching plants. It"
        +" looks like someone has been here recently, and you"
        +" can see the remnants of strangely-shaped footprints"
        +" in the dirt. There is a heavy wall of vegetation to"
        +" the east which you might push your way through, and"
        +" clear exits to the north and northeast.\n");

AE(PK+"w_path4","east",0);
AE(PK+"w_path6","north",0);
AE(PK+"cell4","northeast",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

add_item(({"dirt","footprints"}), "The footprints left"
        +" in the dirt are of a kind you do not recognize."
        +" They seem to have been left by some large animal.\n");
add_item(({"vegetation","plants","wall","east"}),"You"
        +" can probably push your way through this wall"
        +" of vegetation by heading east.\n");

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"suranie");
  add_herb_file(HERB+"carlith");
}

reset_room()
{
  set_searched(0);
}

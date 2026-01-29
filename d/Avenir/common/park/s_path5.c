// file name: s_path5.c
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

/* Room 44 */

create_room()
{
set_short("Turn in the path");
set_long("The dirt path turns here,"
        +" leading away to the north and southwest. Looking"
        +" around, you also spot an opening in the dense"
        +" foliage which leads to the east. The sound"
        +" of calling birds fills your ears, and many"
        +" annoying but harmless insects hover nearby.\n");

AE(PK+"s_path4","north",0);
AE(PK+"s_path6","southwest",0);
AE(PK+"enterlab","east",0);

add_prop(ROOM_I_LIGHT,1); IN

STDEPATH

  set_search_places(({"vine","vines","underbrush","weeds","weed"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(GONDOR+"sumac");
  add_herb_file(SHIRE+"lianor_berry");
}

reset_room()
{
  set_searched(0);
}


inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/lake/"

create_room(){

set_short("Lake");
set_long(
"Clear as crystal, this deep mountain lake reaches out across\n"
+"the valley, forming its center. A strong breeze gusts over the\n"
+"water, warm and full of life.\n"
);

add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}


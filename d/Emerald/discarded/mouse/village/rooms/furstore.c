/* storeroom for fur trader, coded by Elizabeth Cook/Mouse, November 1996 */

inherit "std/room";
#include <stdproperties.h>
#include"../../mouse.h"

void create_room()  {
     add_prop(ROOM_I_INSIDE,1);
     set_short("Fur trader's storeroom");
     set_long("   This is the storeroom for the fur trading post.\n");
     clone_object(ROOT+"village/items/buckskin.c")->move(TO);
     clone_object(ROOT+"village/items/rockyfur.c")->move(TO);
     clone_object(ROOT+"village/items/doeskin.c")->move(TO);
     clone_object(ROOT+"village/items/wolfskin.c")->move(TO);
     clone_object(ROOT+"village/items/gryfoxfur.c")->move(TO);
}


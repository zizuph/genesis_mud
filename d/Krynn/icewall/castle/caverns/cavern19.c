/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
set_short("Overlooking Lake");
set_long(
	"You stand on dry land overlooking the underground lake of "
+ "Icewall. Just to the south is what looks like a large patch of "
+ "spikes sticking out of the floor and ceiling. "
+"\n");

add_item("spikes","Well, they look like spikes.\n");
add_item("land","The land is more frozen than dry.\n");
add_item("lake","The lake stretches out to the west of you forming "
+ "a large subterranean passage.\n");

add_exit(CAVE+"cavern5.c","northwest");
add_exit(CAVERNS+"cavern20.c","southeast");
add_exit(CAVE+"cavern18.c","south");
}









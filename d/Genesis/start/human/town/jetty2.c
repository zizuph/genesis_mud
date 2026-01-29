#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{ 
    set_short("The far point of the jetty");
/*    set_long("\n"+
        "The end of the jetty.\n"+
        "The waves break violently at the large stones. It is quite windy.\n"+
        "A large statue of a strong sailor stands here looking out towards\n"+
        "the horizon of Pensea.\n"+
        "");*/

    set_long("The end of the jetty.\n"+
        "The waves break violently at the large stones. It is quite windy. " +
        "A large statue of a strong sailor stands here looking out towards " +
        "the horizon of Pensea.\n");


    add_item(({"waves" }),
		"The waves are wild and maybe just a bit too rough to swim " +
		"around in. You would be crushed on the stones if you tried to " +
		"enter the water here.\n");
    add_item(({"stones" }),
		"The waves have polished the rock to a smooth and even surface. " +
		"These stones must have been put here a long time ago.\n");
    add_item(({"statue" }),
		"He's tall and muscular with a weatherbeaten look to his face. " +
		"Clad in a striped shirt, breaches and a sailor's vest, he stands " +
		"here looking out over the sea with a faraway look in his eyes. " +
		"There is a small metal plate at the bottom of the statue.\n");
    add_item(({"plate" }),
		"It is a small bronze plate with an inscription. It says:\n\n" +
		"   Born at sea, born to sail, born to travel far.\n" +
		" Gone with thee, the one I love, lost to me thou are.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(TOWN_DIR + "jetty1", "north");
}

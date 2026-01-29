#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("The far point of the jetty");
    set_long("\n"+
             "The end of the jetty.\n"+
             "The waves break violently at the large stones. It is quite windy.\n"+
             "A large statue of a strong sailor stands here looking out towards\n"+
             "the horizon of Pensea.\n"+
             "");

    add_item(({"waves" }),"The waves are wild and maybe just a bit to rough to swim\n"+
    "around in. You would be crushed on the stones if you try to enter "+
    "the water here.\n"+
    "");
    add_item(({"stones" }),"The waves have polished the rock to a smooth and even surface.\n"+
    "These stones must have been put here a long time ago.\n"+
    "");
    add_item(({"statue" }),"He's tall and muscular with a weather-beaten look to his face.\n"+
    "Clad in a striped shirt, breaches and a sailors vest, he stands\n"+
    "here looking out over the sea with a far away look in his eyes.\n"+
    "There is a small metal plate at the bottom of the statue.\n"+
    "");
    add_item(({"plate" }),"It is a small bronze plate with an inscription. It says,\n"+
    "\n"+
    "   Born at sea, born to sail, born to travel far.\n"+
    " Gone with thee, the one I love, lost to me thou are.\n"+
    "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit("jetty1","north");
}


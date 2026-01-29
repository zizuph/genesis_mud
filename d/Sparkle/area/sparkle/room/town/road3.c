/* Aug 30 2001 Stern : Added west exit for events museum */



#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

void
create_room()
{
    set_short("Sparkle Road");
    set_long("\n"+
             "You're walking down the road. To your south is the "+
             "adventurers guild. A place well worth a visit. "+
             "To the west you see a towering building.\n");

    add_item(({"guild","road" }),"");

    add_exit("road2","north");
    add_exit("adv_guild","south");
    add_exit("road4","east");
    add_exit(S_LINK_MVSEVM_ENTRY, "west");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}


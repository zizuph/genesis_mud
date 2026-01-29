#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

public void    rats(int nr);
public void    mice(int nr);

public void
create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    set_short("Berth 3 - Grey Havens");
    set_long(
      "You are at the west pier outside a warehouse." +
      " The harbour is due east, so you better not walk too close" +
      " to the edge. Ships and galleys are known to land here.\n" +
      "There is a sign here that reads: Berth 3 - Grey Havens.\n");

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/pelargir","north");
    add_exit(S_LOCAL_ROOM_DIR + "ware3","west");
    add_exit(S_LOCAL_ROOM_DIR + "circle","south");

    add_item(({"warehouse" }),"");
    add_item(({"pier" }),"");
    add_item(({"sign" }),"");

    set_alarm(1.0, 0.0, &rats(random(4)));
    set_alarm(1.0, 0.0, &mice(4 + random(6)));
}

public void
rats(int nr)
{
    object ob;

    clone_object(S_COMMON_NPC_DIR + "rat_tiny")->move(TO);

    if (nr > 1)
        set_alarm(30.0 + 60.0 * rnd(), 0.0, &rats(nr - 1));
}

public void
mice(int nr)
{
    clone_object(S_COMMON_NPC_DIR + "mouse")->move(TO);

    if (nr > 1)
        set_alarm(30.0 + 60.0 * rnd(), 0.0, &mice(nr - 1));
}

public void
reset_room()
{
    if (!random(3))
        set_alarm(1.0, 0.0, &rats(random(4)));
    if (!random(8))
        set_alarm(1.0, 0.0, &mice(4 + random(6)));
}


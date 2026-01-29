#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

#include "../defs.h"

inherit "/std/room";

void
create_room()
{
    set_short("The inlet");
    set_long("\n"+
             "You are in the inlet to the harbour.\n"+
             "To swim further east would be pure folly since the waves\n"+
             "are getting pretty big out there. It might even be lethal.\n"+
             "However, a small ladder can be seen leading up to the south pier.\n"+
             "");

    add_item(({"harbour" }),"It's the harbour of Sparkle and it's wet!\n"+
    "");
    add_item(({"waves" }),"Those big waves! They make you feel rather small.\n"+
    "");
    add_item(({"ladder" }),"A sturdy wooden ladder.\n"+
    "");
    add_item(({"pier" }),"It's to far for you to reach up there.\n"+
    "");
    add_item(({"water" }),"It's rather filthy.\n"+
    "");

    add_exit(TOWN_DIR + "sea1","west");
    add_exit(TOWN_DIR + "sea3","east");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

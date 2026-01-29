#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#define PATH "/d/Terel/mountains/"

public void
create_room()
{
    set_short("Cliff");
    set_long(
        "Here along the ledge of the mountains forms an icy cliff, there\n"+
        "are many large icicles that hang down almost to form a shelter.\n"+
        "Bits of bone and scraps of fur are here.\n");
    add_item("cliff", "It is icy and sheer, but it might be possible to " +
       "climb.\n");
    add_cmd_item("cliff", "climb", "@@climb");
    add_exit("/d/Terel/mountains/ice6","west", 0);
    reset_room();
}

int
climb(){
    if((TP->query_skill(SS_CLIMB) + TP->query_stat(SS_DEX) +
         random(100) > 100))
        {
            TP->move_living("by climbing up the cliff", PATH + "clifftop");

            return 1;
        }
    write("You try to climb the cliff, but fall down.\n");
    TP->add_fatigue(-15);
    say(QCTNAME(this_player()) + " tries to climb the cliff, but fails.\n");
    return 1;
}

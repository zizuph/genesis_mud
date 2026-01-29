/* Loaded by valley1_1.c */

inherit "/d/Emerald/std/clone_handler";

#define VALLEY1_DIR "/d/Emerald/blackwall/valley1/"
#include "/d/Emerald/sys/paths.h"

void
create_clone_handler()
{
    set_default_area(VALLEY1_DIR);

    /* A few random NPCs to make life in the valley more interesting */

    add_clone(BLACKWALL_DIR + "npc/bear", 1, random(3));
    add_clone(BLACKWALL_DIR + "npc/troll1", 2, random(4));
}

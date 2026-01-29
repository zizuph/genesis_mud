/*
 *  /d/Gondor/guilds/rangers/ithilien/passage6.c
 *
 * Modification log:
 * 20-Jul-2001,Alto: more tidy up, change inheritance for new
 *                   rangers.
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"

inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "exit.c"

public void
create_gondor()
{
    set_short("a hidden set of stairs");
    set_long("A set of stone steps lead up from here towards the roof "
        + "of green leaves above. The hidden passage continues west between "
        + "narrow stone walls. You hear the sound of rushing water from the "
        + "north.\n");
    add_item(({"roof", "leaves"}), "A roof of green leaves can be seen "
        + "above. You guess it is the bushes covering the entrance to this "
        + "hidden path.\n");
    add_item("passage", "The hidden passage runs under a cover of leaves.\n");
    add_item("steps", "The path runs up a set of stone steps cut into the "
        + "rock.\n");
    add_prop(ROOM_M_NO_SCRY, 1);
    add_exit(RANGERS_ITH_DIR + "passage5", "west", &check_ranger());
    add_exit(RANGERS_ITH_DIR + "entrance", "up", &check_ranger());
}

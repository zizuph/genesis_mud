/*
 * Longbottom
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

inherit "/d/Shire/std/room";
inherit "/d/Gondor/common/lib/time.c";
inherit LB_BASE_ROAD;

void

create_room()

{
    set_short("The village of Longbottom");
    set_long("You are walking along a street in the middle of Longbottom, " +
        "a village set in a deep valley of the South Farthing in the Shire. " +
        "On the southwest side of the road, various circular doors and " +
        "windows reveal the smials set into the steep ravine wall that " +
        "rises high above you. To the northeast, you can see a stout, " +
        "square building which appears to have a more or less constant " +
        "flow of hobbits going in and out. Beyond the stream, " +
        "you can see endless fields growing the famous longbottom leaf. " +
        "This road continues further into town to the northwest and out " +
        "of the valley to the southeast.\n");
    add_item(({"building", "square building", "post office", "post"}),
        "This appears to be the local post office! It seems to be " +
        "very busy, despite the small size and remote nature of the " +
        "village of Longbottom.\n");

    lb_road();

// This sets up the drink function and lists where players can drink from
    set_drink_from(({"brook", "stream", "small brook"}));

    add_exit(LB_RM_DIR + "post.c", "northeast");
    add_exit(LB_RM_DIR + "lb03.c", "southeast");
    add_exit(LB_RM_DIR + "lb05.c", "northwest");
}

public void
init()
{
    ::init();
// This initializes the drink function.
    init_drink();
}

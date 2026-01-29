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
        "rises high above you. To the northeast, you see a brightly painted " +
        "building, between a small stream and the dirt road you " +
        "are currently walking on. Beyond the stream, you can see endless " +
        "fields growing the famous longbottom leaf. This road continues " +
        "further into town to the northwest and out of the valley to the " +
        "southeast.\n");

    add_item(({"building", "painted building", "brightly painted building", 
            "store", "general store"}),
        "This brightly painted building appears to be the general store " +
        "that serves the village of Longbottom. It is sitting on the " +
        "northeast side of the road, just before a small stream.\n");

    lb_road();

// This sets up the drink function and lists where players can drink from
    set_drink_from(({"brook", "stream", "small brook"}));

   add_exit(LB_RM_DIR + "shop.c", "northeast");
    add_exit(LB_RM_DIR + "lb01.c", "southeast");
    add_exit(LB_RM_DIR + "lb03.c", "northwest");
}

public void
init()
{
    ::init();
// This initializes the drink function.
    init_drink();
}
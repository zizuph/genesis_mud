/*
 * Base file for Longbottom
 * Finwe, December 2019
 * Area originally coded by Varian, February 2015
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Shire/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";

void
init()
{
    ::init();
    init_drink();
}

void lb_road()
{
    add_item(({"track", "road", "path", "dirt", "street"}),
        "This is just a hard-packed, dirt road running through the small " +
        "hobbit village of Longbottom.\n");
    add_item(({"longbottom", "village"}),
        "You are currently within the village of Longbottom, a hobbit " +
        "settlement which is famous for the 'Longbottom Leaf', the " +
        "highly prized pipeweed which is in demand world-wide.\n");
    add_item(({"valley", "ravine"}),
        "The village of Longbottom has been settled in a deep, long " +
        "ravine running northwest to southeast. The steep walls of " +
        "the ravine to the southwest have apparently been excavated " +
        "to accomodate several smials.\n");
    add_item(({"smial", "smials", "hobbit holes"}),
        "There are many Hobbit holes, or smials as they are known " +
        "amongst the Hobbitfolk themselves, cut deep into the ravine " +
        "wall to the southwest. Smials are quite comfortable and tidy " +
        "dwellings, the favoured residence of most Hobbits.\n");
    add_item(({"window", "windows", "door", "doors"}),
        "There are many circular doors and windows, signs of several smials, " +
        "peeking out all along the ravine wall southwest of the road.\n");
    add_item(({"stream", "small stream", "water"}),
        "This is just a quiet little stream that runs through the " +
        "village of Longbottom. It happily gurgles its way south " +
        "towards the sea.\n");
    add_item(({"field", "fields", "longbottom leaf"}),
        "You can see endless fields where the local hobbits grow " +
        "the famous 'Longbottom Leaf' pipeweed on the far side " +
        "of the stream. The village here is quite prosperous " +
        "as a result.\n");
}
/*
 * Base Room Example
 * -- Finwe, June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "stables.h"
#include <stdproperties.h>
#include <terrain.h>

// this is a base file for outdoor rooms in Faerun
inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Gondor/common/lib/drink_water.c";

#define ROOM_DIR "/d/Faerun/examples/base_file/rooms/"
// this defines the routine to create the room

void
create_faerun_room()
{
    setuid();
    seteuid(getuid());

    set_short("A clean stable");
    set_long("The stable is large and houses many fine steeds. One end of " +
        "the building is full of stalls. Some have horses in them and " +
        "others are empty. Straw covers the floor. Bales of hay are " +
        "stacked up against one wall, and long troughs full of fresh water " +
        "are set near the entrance.\n");

    set_drink_from(({"trough", "long trough", "loung troughs", "troughs"}));

    add_item(({"door", "corral door"}),
        "It is locked securely.\n");

    add_item(({"hay", "bales of hay", "alfalfa"}),
        "It is freshly cut and stacked up against the walls. " +
        "It is excellent food for the horses.\n");
    add_item(({"horses", "steeds"}),
        "The horses in the stalls are tall magnificent " +
        "creatures, They are muscular and well groomed. " +
        "The steeds are different colors, with " +
        "brown being the common color.\n");
    add_item("ceiling",
        "Large carved beams hold up the roof high above you.\n");
    add_item(({"down", "straw", "floor", "ground"}),
        "Fresh straw cover the ground. It is golden colored " +
        "and smells clean like it was freshly cut.\n");
    add_item(({"stalls", "stall"}),
        "The stalls are a good size, sturdy and made of solid " +
        "wood, and able to house a large " +
        "horse comfortably. Within each stall you see troughs " +
        "for food and water. Some stalls are empty " +
        "while others are occupied.\n");
    add_item(({"troughs", "trough"}),
        "you see troughs in the stalls for food.\n");
    add_item(({"food trough", "food troughs", "wooden food troughs",
            "wooden food trough"}),
        "The food troughs are made of wood and have some hay, alfalfa" +
        "and grain in them for the hungry horses.\n");
    add_item(({"grain", "oats", "sweet molasses", "molasses",
            "corn", "feed"}),
        "You see a mixture of oats, corn, sweet molasses, and " +
        "other good foods in the food troughs.\n");
    add_item(({"walls", "wall"}),
        "The walls are strong and durable, made of planed wood. " +
        "Some shelves and racks are on the walls.\n");
    add_item("racks",
        "The racks stretch across a long wall. On them, are " +
        "various saddles, bridles, halters, and other implements " +
        "of horsmanship.\n");
    add_item("shelves",
        "You see some combs, brushes, bells, blankets, and " +
        "other items stacked on the shelves.\n");
    add_item(({"comb", "combs"}),
        "The combs are made of metal and have teeth to remove " +
        "tangles and debris from the animal's hair.\n");
    add_item(({"brushes", "brush"}),
        "The brush is made of soft, smooth bristles of pure dark " +
        "horsehair blend and is the best finishing brush you've seen. " +
        "The brushes are small and fit in your hand comfortably.\n");
    add_item(({"blankets", "horses blankets"}),
        "The blankets are wool and in many bright colors. They " +
        "are used to cover the horses and for riding.\n");
    add_item(({"saddles", "saddle"}),
        "The saddles are strongly built to withstand and " +
        "protect the rider from extended travel. The saddles " +
        "have a flatter seat allowing greater freedom while " +
        "riding.\n");
    add_item(({"bridle", "bridles"}),
        "These harnesses fit over the horses head and are used " +
        "to guide or restrain the animal. They consist of a " +
        "'U'-shaped metal piece which fits in the mouth and " +
        "leather straps to secure it to the horse.\n");
    add_item(({"halters", "halter"}),
        "These devices are made of leather straps and fit over " +
        "the horses head and neck.\n");

    add_exit(STABLES_DIR + "east_yard", "east");
    add_exit(ROOM_DIR + "meadow01", "south");

// This turns on room tells
    set_room_tell_time(60);

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


public void
init()
{
    ::init();
    init_drink();
}

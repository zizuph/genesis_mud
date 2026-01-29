#include "defs.h"

inherit GROTTOBASE;

public void reset_room();

public void
create_room()
{
    set_short("a dark grotto");
    set_long("You've entered a dark cave or grotto of some " +
        "sort, deep beneath the surface. It's quite " +
        "large, big enough that you have difficulty spotting " +
        "the exact locations of the walls and ceiling in the " +
        "shadow-filled darkness.  The floor has been worn " +
        "smooth, however. It remains quite uneven and filled " +
        "with depressions of varying sizes, but there are no " +
        "sharp or sudden edges. All the surfaces are bare, grey " +
        "stone, and appear to have been eroded out from the " +
        "stone naturally. Many of the depressions on the " +
        "ground have collected pools of water that drips down " +
        "from high stalactites on the ceiling, or trickles " +
        "into the room through cracks from the underground " +
        "lake to the south.\n\n");

    INSIDE;
    DARK;
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    enable_reset(100);
    reset_room();

    add_item(({"walls", "wall"}),
        "You can only see small sections of the walls in this " +
        "dim lighting, however they appear to be quite typical " +
        "for cave walls, most probably water-smoothed " +
        "stone.\n");
    add_item(({"ceiling", "roof"}),
        "The roof of the ceiling hangs low, but is cloaked in " +
        "numerous shadows cast about the room. From what little " +
        "you can see if it, however, it appears quite normal. " +
        "Just a roof made of eroded stone.\n");
    add_item(({"floor", "ground"}),
        "Like the walls and ceiling, the floor appears to be " +
        "just eroded stone. Unlike the walls and ceiling, however,  " +
        "the floor isn't just smooth, but more or less level. " +
        "The only things that mar it's surface are a large number " +
        "of depressions in the stone that have filled with " +
        "water, forming a series of small pools.\n");
    add_item(({"depressions", "depression", "pool", "pools"}),
        "Scattered across the floor of the grotto, several " +
        "depressions of various sizes have formed pools of water " +
        "of varying depth.\n");
    add_item(({"stone", "grey stone"}),
        "It looks to be a fairly common variety of granite, and " +
        "the island seems to be almost completely composed of it, " +
        "along with the castle.\n");
    add_item(({"water"}),
        "There's a substantial amount of water down here, " +
        "a large amount of which is dripping down into the pools " +
        "of water from the stalactites above.\n");
    add_item(({"stalactite"}),
        "Several stalactites hang low from the ceiling above " +
        "you. An almost steady stream of water drips down them " +
        "and into the pools of water that have formed in the " +
        "depressions on the floor.\n");

    add_exit(GROTTO + "s_grotto", "south");
}

public void
reset_room()
{
    if (!find_living("firestorm"))
    clone_object(NPC + "firestorm")->move(TO);
}

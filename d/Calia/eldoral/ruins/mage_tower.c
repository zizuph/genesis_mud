#pragma strict_types

#include "../defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("in the top of a tower in " + CASTLE_NAME);
    set_long("Strangely enough, you find yourself in a warm, well-lit " +
        "circular room, apparently someone's study. A large fireplace " +
        "in the north wall contains a roaring fire, snapping and cracking " +
        "as the flames feed upon the poorly seasoned wood. Against the " +
        "west wall, a cluttered oak desk stands before a leather-backed " +
        "chair. The south wall is entirely consumed by endless shelves, " +
        "filled with books, scrolls, and objects of various shapes and " +
        "sizes. Soft, clean rugs cover the stone floor, it looks as if " +
        "it was just barely built. Even the ceiling isn't spared from " +
        "the clutter, you see a variety of spheres, curves and disks " +
        "hanging from it in strange patterns, some of which are even " +
        "mounted on tracks of some sort, so they seem to rotate about " +
        "one another in complicated circuits. As if all of this weren't " +
        "confusing enough, you realize that you can hear the sounds of " +
        "birds singing, and dozens of voices laughing and carrying on " +
        "coming from somewhere outside.\n\n");

    INSIDE;

    add_exit(RUIN + "walk_3", "east");
}

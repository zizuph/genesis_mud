/* Hut1: This could be a quest sight (exterminate the bugs). */

inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


void
reset_room()
{
    bring_room_mob("citizen", TYR_NPC+"poor_hmn", 1, 1);
}

void create_room()
{
    ::create_room();
    set_short("shoddy house");
    set_long ("The crumbling clay patching the holes in the wall and the "+
              "free roaming insects do not speak highly of the owner's "+
              "cleanliness or wealth. Of course, that is to be expected "+
              "in this section of Tyr.\n");

    add_item(({"clay", "holes", "hole", "patch", "walls", "wall"}),
             ("The holes are most likely made by the insects, and patched "+
              "over by the owner as soon as they appear. Unfortunately, the "+
              "bugs have a significant numerical advantage.\n"));

    add_item(({"insects", "insect", "bug", "bugs"}),
             ("They are about the size of a man's thumb, with large "+
              "mandibles, but don't seem very hostile. The problem is "+
              "simply their raw numbers.\n"));

    INSIDE

    add_exit(TYR_WARREN+"rd_mr_04.c", "north", 0, 1);

    reset_room();
}

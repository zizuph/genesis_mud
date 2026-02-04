/*
 * cave04.c
 *
 * A cave room near the entrance.
 *
 * Lucius - Jan 2021
 *   Cleaned up and modernized.
 */
#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "goblincave/cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    ::create_terel_room();
    set_long(query_long() +
        "The tunnel ends here. This room looks to be " +
        "inhabited. Several furs lay on the ground. A makeshift table and " +
        "stools are against one of the cave walls.\n");

    add_item(("furs"),"Furs of various woodland creatures used for warmth.\n");
    add_item(("ground"),"The rocky ground is littered with bones of various " +
       "sizes.\n");
    add_item(("bones"),"The bones are hard to distinguish, some however could " +
       "be large enough to be humanoid in origin.\n");
    add_item(({"table","stool","stools"}),"The table and stools are crudely built " +
       "from twigs and vines.\n");

    DARK;

    add_exit(MOUNTAIN_DIR + "goblincave/cave02",   "southeast");

    add_npc(MOUNTAIN_DIR + "goblincave/npc/std_goblin_grd", 2);
}

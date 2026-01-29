/*
 * The excercise yard off of the stables in Imladris
 * By Finwe, January 1998
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
    set_extraline("The yard is large enough for many horses " +
        "to practice different skills. A dirt track runs around " +
        "the perimeter of the grassy yard with obstacles for " +
        "horses to jump over. A fence encircles the yard.");
 
    add_item(({"field", "yard", "grassy yard"}),
        "The yard is covered with short clipped grass. It is " +
        "clean and free of debris. \n");
    add_item(({"obstacles"}),
        "Across the track, you see some rails for horses to " +
        "practice jumping over.\n");
    add_item(({"rails", "practice rails"}),
        "The rails are fences stretched across the track at " +
        "various heights. Horses jump over them in their " +
        "training excercises.\n");
    add_item(({"dirt track", "track"}),
        "the track is made of packed earth. It is wide and " +
        "designed for horses to practice running on. It is free " +
        "of rocks, large stones, and other debris.\n");
    add_item(({"debris", "rocks", "stones", "large stones"}),
        "You don't see any here.\n");
    add_item("stable",
        "The stable is a large building to your east. The " +
        "horses live in it.\n");
    add_item(({"fence", "wooden fence", "split-rail fence"}),
        "The fence is constructed of timbers that have been " +
        "split in two. They are secured to posts that have been " +
        "sunk into the ground.\n");
 
     
    add_exit(VALLEY_DIR + "stable", "east");
 
}
 
 
string short_desc()
{
    return ("Excercise yard of the stables");
}


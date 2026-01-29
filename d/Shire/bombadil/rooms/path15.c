/*
 * Path in Tom Bombadill's Clearing
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"

inherit CLEAR_BASE;
 
void
create_path_room()
{
    set_areadesc("dark");
    set_area("path in");
    set_areaname("the Old Forest");
    set_land("Eriador");
    set_areatype(0);

    set_extraline("The path runs between large trees in the old " +
        "forest. Long tree branches stretch out, blocking your " +
        "view of anything nearby. The path disappears into the " +
        "trees to the west.");

    set_no_exit_msg(({"southwest","south","northwest","southeast","north",
            "northeast"}),
        "The trees are too thick to move any further in this direction!\n");
    set_no_exit_msg(({"west"}),
        "You try to follow the path west, but the trees seem to gather " +
        "in front of you, making further passage impossible.\n");

// items not neaded as player isn't in clearing anymore/yet
    remove_item("clearing"); 
    remove_item(({"downs", "barrow downs"}));
    remove_item(({"green hills", "hills"}));
    remove_item(({"fogs", "fog", "mists", "mist", "swirling fog", 
            "swirling fogs", "swirling mists", "swirling mist"}));

// modified from base file
    add_item(({"forest", "old forest"}),
        "The forest is dark and forboding. Tall trees block most " +
        "of the @@light_type@@ light, leaving an almost stifling " +
        "feeling. Some say the forest is haunted and that it " +
        "moves about on its own, though this is speculation and " +
        "no one knows for sure.\n");
    add_item(({"ground", "path", "trail"}),
        "The ground is unusually smooth and covered with short, clipped " +
        "grass, as if it was mowed. It ends rather abruptly to the west, " +
        "and leads away east from here.\n");
    add_item(({"branch", "branches", "leaf", "leaves", "long branches",
            "long branch", "leafy branch", "leafy branches"}),
        "Long leafy branches stretch out, surrounding the path here and " +
        "blocking your sight in every direction. Every time you move " +
        "a branch, another seems to spring into view, preventing you " +
        "from seeing anything aside from a face full of leaves or going " +
        "anywhere except east along the path.\n");
    add_item(({"trees", "tree"}),
        "The trees are tall and dark looking. Many are ancient " +
        "looking. Their tall branches shade reach to the sky, " +
        "blocking most of the @@light_type@@ light. The branches " +
        "move about, almost on their own.\n");

// remove this when exit west is added.
    add_item(({"west"}),
        "The trees are thicker, blocking your passage beyond " +
        "here. The path winds around some trees and then appears to " +
        "be suddenly swallowed by the trees.\n");
    add_exit(ROOMS_DIR + "path09", "east");

}


/*
 * cemetary_base.c
 *
 * This is the baseroom for the cemetary outside of the
 * black tower.
 *
 * Khail - July 7/97
 */
#pragma strict_types

#include "cemetary.h"

inherit "/d/Khalakhor/std/room";

public void
create_add_items()
{
    add_item(({"tower","ruins","rubble"}),
        "The tower is a curious shape, as if constructed " +
        "from three separate towers, then stacked side " +
        "by side, resulting in a triangular-shaped " +
        "tower. The lower levels appear to be intact, " +
        "but the jagged stones jutting out of the top " +
        "of the tower suggest that it was much higher " +
        "at one point, but has since collapsed in upon " +
        "itself.\n");
    add_item(({"ground","floor"}),
        "The ground here is mainly short brown grass, " +
        "as if it dies shortly after sprouting.\n");
    add_item(({"grass"}),
        "The grass is quite dead, and makes a loud " +
        "rustling noise as you pass across it.\n");
    add_item(({"sky", "clouds"}),
        "High above your head, a few dark clouds drift " +
        "through an otherwise blue sky.\n");
    add_item(({"grounds","clearing"}),
        "The tower grounds might once have been an " +
        "orchard of oak trees, but now it's covered " +
        "in dead grass and skeletal oak trees, beneath " +
        "which sprawls a mat of rotting leaves.\n");
    add_item(({"trees", "oaks", "oak trees"}),
        "There's little left to recognize these trees " +
        "as oaks, aside from their size. Leaves once " +
        "must have covered these blackened branches, " +
        "but they now lie rotting around the bases " +
        "of the trunks. The are particularly dense " +
        "here in the cemetary, and particularly deformed, " +
        "as well.\n");
    add_item(({"leaves"}),
        "Strewn about the bases of the oak trees, " +
        "thin beds of rotting leaves give off a rather " +
        "unpleasant smell of decay.\n");
    add_item(({"embankments"}),
        "The tower grounds are surrounded on all visible " +
        "sides by embankments of stony earth, which are " +
        "covered with a thick tangle of brambles and " +
        "thistles.\n");
    add_item(({"brambles"}),
        "The brambles cover the embankments, large, " +
        "tangled brush filled with thorns as long as " +
        "your thumb.\n");
    add_item(({"thistles"}),
        "Intermingled with the brambles, bushes of " +
        "thistles fill up the few gaps that the brambles " +
        "are unable to.\n");
    add_item(({"graves"}),
        "If not for a few tombstones sticking out of the " +
        "ground, you'd never even know there were people " +
        "buried here.\n");
    add_item(({"tombstones"}),
        "Heavy tombstones lie strewn about the cemetary, " +
        "some still upright, some having toppled over " +
        "long ago. Most are fairly simple slabs of stone, " +
        "others are more intricately carved, portraying " +
        "various figures and symbols.\n");
    add_item(({"figures"}),
        "Most of the figures, though badly worn, appear " +
        "to have once been of humans, possibly those " +
        "buried beneath them. A few though, could not " +
        "possibly have been human shapes, and are " +
        "unlikely to be naturally occuring creatures " +
        "at all.\n");
    add_item(({"symbols"}),
        "There are a number of symbols carved into tombstones, " +
        "most geometric shapes such as circles and triangles. " +
        "You notice one in particular seems to only exist " +
        "on the larger tombstones. It consists of a large " +
        "cross, with a circle centered on the intersection " +
        "of the arms with the stem. Within the circle are " +
        "three vanes which spiral outwards from the center, " +
        "forming three identical tear-drop shapes.\n");
}

public void
create_cemetary()
{
    set_short("in an overgrown cemetary");
    set_long("You are in an obviously old cemetary, " +
        "overgrown so heavily that the only way to " +
        "tell it's a cemetary are a few tombstones " +
        "sticking up out of the ground. The dead " +
        "oak trees which dominate the grounds of the " +
        "old tower are particularly dense here, this " +
        "must once have been a beautiful graveyard. " +
        "Now, however, the dead are blanketed not in " +
        "soft grass dappled with sunlight as it filters " +
        "through the leaves of the oaks, but a carpet " +
        "of dead vegetation and tendril-like shadows " +
        "as the sun passes through the skeletal remains "+
        "of the oaks.\n");

    create_add_items();
}
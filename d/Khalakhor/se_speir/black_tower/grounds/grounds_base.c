/*
 * grounds_base.c
 *
 * This is the baseroom for the grounds outside of the
 * black tower.
 *
 * Khail - July 7/97
 */
#pragma strict_types

#include "grounds.h"

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
        "of the trunks.\n");
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
}

public void
create_grounds()
{
    set_short("beside the ruins of a tower");
    set_long("You are on a path leading around " +
        "the ruins of an ancient tower, across " +
        "the grounds which surround it. The grounds " +
        "are bounded by stony emankments covered in " +
        "brambles and thistles, and are populated " +
        "only by the skeletal remains of a few dead " +
        "oak trees. Occasionally you hear the " +
        "croaking of a raven, and something unseen " +
        "scuttling across the bed of rotting leaves " +
        "beneath the dead trees, but other than that, " +
        "it's as if the wind itself dares not " +
        "whisper here.\n");
    create_add_items();
}
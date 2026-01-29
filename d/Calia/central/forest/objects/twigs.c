// OBJECT:  twigs.c

    /*  Calia Domain

    HISTORY

    [98-04-10] created by Uhclem from
    [C:\CALIA\CENTRAL\FOREST\OBJECTS\TWIGS.DOC].

    PURPOSE

    This heap object is a bunch of twigs broken from a tree in the Great
    Central Forest. The twigs appear when a large branch is broken from the
    tree, mostly to hint that the smaller twigs were broken off the branch as
    it fell, leaving it smooth enough to be easily wielded as a weapon. They
    also serve as a marker to indicate which trees have been climbed. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/heap";

#include <stdproperties.h>

// FUNCTIONS

// Function: create_twig(tree)

/*

Purpose: add description appropriate to the tree variety.

Arguments: string, tree type.

Returns: nothing.

*/

void
create_twig(string tree)

    {

    set_name("twig");
    set_short(tree + " twig");

    set_long("These twigs are bits and pieces of " + tree + " trees" +
        " that break off occasionally due to the effects of wind" +
        " and other forces. You see nothing unusual about them.\n");

    }

// HEAP DEFINITION

void
create_heap()

    {

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_I_VALUE, 0);
    set_heap_size(3 + random(3));

    }

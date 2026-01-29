// WEAPON:  stick.c

    /*  Calia Domain

    HISTORY

    [98-04-10] created by Uhclem from
    [C:\CALIA\CENTRAL\FOREST\OBJECTS\STICK.DOC].

    PURPOSE

    This is a stick broken from a tree in the Great Central Forest. It is a
    good size and shape for making into a wand, but it has no magic power of
    its own. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <language.h>
#include <stdproperties.h>

// FUNCTIONS

// Function: create_stick(tree)

/*

Purpose: add description appropriate to the tree variety.

Arguments: string, tree type.

Returns: nothing.

*/

void
create_stick(string tree)  /* string has two words; i.e., "oak tree" */

    {

    set_name("stick");
    set_short("long straight stick");

    set_long("This stick is a smooth, straight branch from " +
        LANG_ADDART(tree) + ", a little more than a half meter long" +
        " and free from any knots or other blemishes.\n");

    }

// OBJECT DEFINITION

void
create_object()

    {

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 0);

    }

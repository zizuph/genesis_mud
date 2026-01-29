// WEAPON:  branch.c

    /*  Calia Domain

    HISTORY

    [98-11-11] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\OBJECTS\BRANCH.DOC].

    PURPOSE

    This is a branch broken from a tree in the Great Central Forest. It
    randomly serves either as a club or a polearm, but not particularly well.
    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/weapon";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

// FUNCTIONS

// Function: query_recover()

/*

Purpose: prevent recovery of this object.

Arguments: none.

Returns: 0.

*/

int
query_recover()

    {

    return 0;

    }

// Function: create_branch(tree)

/*

Purpose: add description appropriate to the tree variety.

Arguments: string, tree type.

Returns: nothing.

*/

void
create_branch(string tree)

    {

    set_name("branch");

    if (query_wt() == W_CLUB)

        {

        set_short("stout " + tree + " branch");
        add_adj("stout");

        }

    else

        {

        set_short("long " + tree + " branch");
        add_adj("long");

        }

    set_long("This branch looks like it was just recently broken off" +
        " a large " + tree + " tree.  Its scent tells you that it's" +
        " far too green to be used as firewood, but it's sturdy enough" +
        " that you might be able to use it as a weapon.\n");

    }

// WEAPON DEFINITION

void
create_weapon()

    {

    set_default_weapon(
        5 + random(6),                      /* hit */
        5 + random(6),                      /* penetration */
        ({W_CLUB, W_POLEARM})[random(2)],   /* type */
        W_BLUDGEON,                         /* damage type */
        W_BOTH,                             /* wield in both hands */
        0);                                 /* no special wield function */

    add_prop(OBJ_I_WEIGHT, 3000 + random(3000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) * 2 / 3);
    add_prop(OBJ_I_VALUE, 0);

    }

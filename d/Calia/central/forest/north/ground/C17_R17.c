//Room type $

inherit "/d/Calia/central/forest/baserooms/base_interior";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

/*  Function: climb_tree(tree)  */

/*
Purpose:  allow easy climbing of the baobab tree by overriding the standard
central forest climb function.

Arguments:  string containing the tree to be climbed.

Returns:  0/1, value will be called from standard function if the tree being
climbed is not a baobab.
*/

int
climb_tree(string tree)

{

    object tp = this_player();
    string destination;
    int fatigue = 5;

    if (tree == "tree"
        || tree == "baobab"
        || tree == "baobab tree")

    {

        /*
         *  Anybody can climb a baobab tree if he's not too tired.    
         */

        destination = LOW + query_prop(FOREST_LOCATION);

        if (tp->query_fatigue() < fatigue)

        {

            write("You are too tired to climb the baobab tree.\n");

            say(QCTNAME(tp) + " tries to climb the baobab tree" +
                " but fails.\n");

            return 1;

        }

        else

        {

            tp->move_living("M", destination, 1);
            tp->add_fatigue(-fatigue);
            say(QCNAME(tp) + " climbs up from ground level.\n");

            tell_room(this_object(),
                QCTNAME(tp) + " leaves climbing the baobab tree.\n");

        }

        return 1;

    }

    else return ::climb_tree(tree);

}

void
create_room()

{

    string *special_long;

    create_forest_interior("C17_R17", ({"C17_R16", "C18_R16",
        "C18_R17", "C18_R18", "C17_R18", "C16_R18", "C16_R17", "C16_R16"}),
        ({"baobab", "cedar"}), 0, "hill");

    special_long = explode(query_long(), ".");

    special_long[1] = " A tremendous baobab tree, a tumult" +
        " of trunks and branches reaching for the" +
        " sky, dominates the landscape here, spreading as high" +
        " and wide as ten of the massive cedars";

    set_long(implode(special_long, "."));

    add_item(({"tree", "baobab", "baobab tree", "baobabs", "baobab trees"}),
        "A giant among giants, the baobab tree's girth is" +
        " as astounding as its height. Composed of" +
        " many trunks and branches, it spreads across the ground" +
        " as if to intimidate even the mighty cedars that" +
        " grow in its shade.\n");

    add_item(({"trees"}),
        "Here cedars grow in the shade of a tremendous" +
        " baobab tree whose many trunks and branches burst" +
        " forth from the ground and attain heights" +
        " far beyond your view.\n");

    add_item(({"trunks", "branches", "many trunks",
        "many branches", "limbs", "tumult"}),
        "The profusion of limbs suggests that anyone who wants to" +
        " try for the top will find plenty of support" +
        " as he climbs.\n");

}


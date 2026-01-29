// ROOM:  base_scaffold.c

    /*  Calia Domain

    HISTORY

    [99-06-09] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\UPPER\BASE_SCA.DOC].

    PURPOSE

    This is the base for interior rooms at the top of the wall of the
    Sanctimonian fortress.  The fortress is octagonal; there are scaffolds at
    the sides and stairs at the corners at this level.

    SPECIAL NOTE:  This room has only one exit which is defined inside the
    create_scaffold function.  Do not add other exits in individual rooms when
    using this baseroom.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// GLOBAL VARIABLES

string This_Location;
int Max_Weight = random(5000000) + 5000000;
int Total_Weight;

// FUNCTIONS

// Function:  check_room_weight()

/*

Purpose:  check the current weight on the scaffold against the maximum weight,
then break the scaffold and send the room's contents to the room below when the
threshold is exceeded.

Arguments:  none.

Returns:  nothing.

*/

void
check_room_weight()

{

    object *room_contents;
    object adjacent_room;
    object lower_room;
    int m;
    int n;

    if (Total_Weight < Max_Weight) return;

    /*
     *  If Max_Weight is exceeded, the sagging process begins.  This process 
     *  applies additional strain to the scaffold in the form of an
     *  ever-increasing weight value; breakage occurs at 10000000.  The only
     *  way to stop/reverse the sagging is to reduce the current weight to less
     *  than the Max_Weight value.  As with a real floor, a heavy weight can
     *  quickly send it past the point of no return, so that even removing all
     *  or most of the weight won't prevent its destruction.    
     */

    Total_Weight += (Total_Weight / 4);

    switch (Total_Weight)
    {

        case 0..5000000:

        break;

        case 5000001..6000000:

        tell_room(this_object(), "The scaffold yields" +
            " under your weight, bouncing slightly with" +
            " your every motion.\n");

        break;

        case 6000001..7000000:

        tell_room(this_object(), "The scaffold sways and" +
            " sags under your weight.\n");

        break;

        case 7000001..8000000:

        tell_room(this_object(), "The scaffold flexes under" +
            " your weight, its vertical motion making" +
            " you somewhat uneasy.\n");

        break;

        case 8000001..9000000:

        tell_room(this_object(), "The scaffold groans and" +
            " creaks under your weight, and it begins to show" +
            " signs of cracking.\n");

        break;

        case 9000001..10000000:

        tell_room(this_object(), "The scaffold begins to" +
            " fold under your weight, pulling free" +
            " from the supporting framework amid the loud cracks" +
            " and snaps of breaking planks.\n");

        break;

        default:

        adjacent_room = find_object(BOG_OUTER_UPPER + This_location);
        lower_room = find_object(BOG_INNER_MIDDLE + This_location);
        if (adjacent_room) adjacent_room->destroy_scaffold();

        if (lower_room) tell_room(lower_room,
            "The scaffold above you suddenly breaks!" +
            " Broken planks and splinters rain down on you.\n");

        room_contents = all_inventory(this_object());
        m = sizeof(room_contents);

        /*
         *  Tell the room below about falling objects. Non-living is shown only 
         *  if it is the first thing to fall.   
         */

        for (n=0; n<m; n+=1)

        {

            if (objectp(tree_contents[n]))

            {

                if (living(tree_contents[n]))

                {

                    tree_contents[n]->move_living("M",
                        BOG_INNER_MIDDLE + This_location, 1);

                    tell_room(environment(room_contents[n]),
                        QCTNAME(room_contents[n]) + " falls from above.\n",
                        ({room_contents[n]}));

                }

                else

                {

                    tree_contents[n]->move(BOG_INNER_MIDDLE + This_location);

                    if (!n)
                        tell_room(environment(room_contents[n]),
                        capitalize(LANG_ADDART(tree_contents[n])) +
                        " falls from above.\n");

                }

            }

        }

        /*
         *  ADD A FUNCTION TO CAUSE AN IMMEDIATE FALL FOR ANYONE WHO ENTERS THE 
         *  ROOM ONCE THE SCAFFOLD IS DESTROYED.  THIS SHOULD ONLY AFFECT MAGES
         *  WHO TELEPORT HERE.
         *  remove_object();

    }

}

// Function:  enter_inv(object, from_object)

/*

Purpose: update the weight of all objects on the scaffold, which will break if
it is overloaded, and register a player (or foreign npc) with the Sanctimonian
control room..

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    ::enter_inv(ob, from);
    Total_Weight += ob->query_prop(OBJECT_I_WEIGHT);
    check_room_weight();

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

}

// Function:  leave_inv(object, to_object)

/*

Purpose: update the weight of all objects on the scaffold, which will break if
it is overloaded.

Arguments:  object entering the room, object where it is going.

Returns:  nothing.

*/

void
leave_inv(object ob, object to)

{

    ::leave_inv(ob, to);
    Total_Weight -= ob->query_prop(OBJECT_I_WEIGHT);
    check_room_weight();

}

// Function:  create_scaffold(location)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room, string indicating
which compass direction this side of the wall faces.

Returns:  nothing.

*/

void
create_scaffold(string location, string side)

{

    This_Location = location;
    Total_Weight = 0;

    set_short("On a scaffold high on the " + side + " side of a fortress");

    set_long("This scaffold is a floor of broad wooden" +
        " planks laid across a framework of timbers. It is just" +
        " inside the top of the " + side + " wall" +
        " of a massive log fortress.\n");

    add_item(({"timbers", "timber", "sturdy timbers", "sturdy timber",
        "framework", "solid framework"}),
        "Some timbers stand upright, and others are parallel" +
        " to the ground. They're cut so that they interlock and" +
        " form a solid framework for the planks that form the" +
        " floor at this level.\n");

    add_item(({"planks", "plank", "broad planks", "broad plank", "floor"}),
        "The planks are laid on the framework of timbers to" +
        " form a spacious floor. Although they are broad and" +
        " fitted together to eliminate any gaps, they also look a" +
        " bit thin, perhaps not intended to hold great weight.\n");

    add_item(({"log fortress", "fortress", "fortress interior", "inside"}),
        "The wall encloses an interior that has scaffolds" +
        " encircling an open center. The scaffolds block most of" +
        " your view of the activity in the center, but you can make" +
        " out a few small structures.\n");

    /*
     *  EXITS    
     */

    add_exit(BOG_OUTER_UPPER + This_location, "wall");

    /*
     *  PROPERTIES   
     */

    add_prop(ROOM_I_HIDE, -1);  /*  Impossible to hide. */
    add_prop(ROOM_I_LIGHT, 3);  /*  Plenty of sunlight. */

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}

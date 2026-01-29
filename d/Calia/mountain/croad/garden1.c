// ROOM:  palace garden 1

    /* Calia Domain

    HISTORY

    [96-02-23] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN1.DOC].

    PURPOSE

    This room is one of 14 garden rooms surrounding Calia palace.  The gardens
    are mostly for decoration, but there is one quest.  See garden_quest
    document for details.  "cant_plant.c" is part of this quest; it prevents
    players from planting seeds in rooms other than the one required by the
    quest.

    Garden room layout (X is the intersection with the road leading to the
    palace at croad27):
                               5---6---7---8---9
                              /                 \
                             4                   10
                             |       palace       |
                             3         |         11
                              \        |        /
                                2      |      12
                                  \    |     /
                                    1--X--13
                                       |   |
                                       |  14
                                       |                                */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <macros.h>
#include "crdefs.h"
#include "cant_plant.c"

// FUNCTIONS

// Function:  init

/*

Purpose:  define commands available in this location (called by system when
room is entered)

Arguments:  none

Returns:  nothing

*/

void
init()

    {

    ::init();
    add_action(plant_seed, "plant");    /* function in "cant_plant.c" */

    }

// ROOM DEFINITION

void
create_room()

    {

    /*  DESCRIPTION  */

    set_short("Calia Palace Gardens, south side");

    set_long("You stand on a path that leads through the palace " +
        "gardens.  On either side of you are tall, graceful " +
        "willows that provide shade and seclusion for anyone who might " +
        "wish to spend a few moments here in quiet reflection.  The " +
        "trees are planted so close together that you can't see " +
        "anything beyond them except the " +
        "sparkling palace towering high overhead.\n");

    /*  EXITS  */

    add_exit(CROAD + "croad27", "east", 0);
    add_exit(CROAD + "garden2", "northwest", 0);

    /*  ITEMS  */

    add_item(({"garden","gardens"}),
        "This section of the garden is planted with stately rows " +
        "of trees that shade the path surrounding the palace.\n");

    add_item(({"path","stones"}),
        "The stones are freshly hewn and show no signs of wear.  " +
        "They lead further into the willows to the northwest, " +
        "and back toward the front of the palace to the east.\n");

    add_item(({"willow","willows","trees","tree"}),
        "These are weeping willows, planted in memory of the many " +
        "warriors who gave their lives on the mountainside.  " +
        "An occasional breeze prompts them to sway serenely, " +
        "making a soothing, rustling sound.\n");

    add_item(("palace"),
        "The walls of the palace are made of sparkling crystal, " +
        "and you can see no trace of nails, mortar, or any other " +
        "kind of fastening.  You get the impression that the palace " +
        "was carved from one immense, flawless gemstone.\n");

    }

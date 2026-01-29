// ROOM:  palace garden 13

    /* Calia Domain

    HISTORY

    [96-02-23] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN13.DOC].

    PURPOSE

    This is one of 14 garden rooms surrounding Calia palace.  See comments in
    Room 1 for layout details.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <macros.h>
#include "crdefs.h"
#include "cant_plant.c"

// FUNCTIONS

// Function:  follow_path

/*

Purpose:  Lets a player follow the path to garden14, moving in a direction
where there is no obvious exit.

Arguments:  none

Returns:0/1

*/

int
follow_path()

    {

    write("You follow the small path between the shrubberies.  " +
        "As you enter this shady spot, you hear a faint 'ni' " +
        "echoing somewhere among the trees.\n");

    this_player()->move_living("following a small path",
        CROAD + "garden14");

    return 1;

    }

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
    add_action(follow_path, "follow");

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
        "wish to spend a few moments here in quiet reflection.  You can " +
        "see the crystal palace towering high overhead, and next to " +
        "the path you notice a newly-planted shrubbery.\n");

    /*  EXITS  */

    add_exit(CROAD + "croad27", "west", 0);
    add_exit(CROAD + "garden12", "northeast", 0);

    /*  ITEMS  */

    add_item(({"garden","gardens"}),
        "This section of the garden is planted with stately rows " +
        "of trees that shade the path surrounding the palace.\n");

    add_item(({"path","stones"}),
        "The stones are freshly hewn and show no signs of wear.  " +
        "They lead further into the willows to the northeast, " +
        "and back toward the front of the palace to the west.\n");

    add_item(({"willow","willows","trees"}),
        "These are weeping willows, planted in memory of the many " +
        "warriors who gave their lives on the mountainside.  " +
        "An occasional breeze prompts them to sway serenely, " +
        "making a soothing, rustling sound.\n");

    add_item(("palace"),
        "The walls of the palace are made of sparkling crystal, " +
        "and you can see no trace of nails, mortar, or any other " +
        "kind of fastening.  You get the impression that the palace " +
        "was carved from one immense, flawless gemstone.\n");

    add_item(("shrubbery"),
        "You take a good look at the shrubbery.\n" +
        "It's a nice one.  You see another smaller one next to it, " +
        "and there's a little path between them leading away from " +
        "the palace.  " +
        "You could follow this path if you wanted to see " +
        "what was behind the trees.\n");

    add_item(({"second shrubbery","smaller shrubbery"}),
        "It's as nice as the first one.  " +
        "You get the feeling that nothing interesting is going to " +
        "happen as long as you keep standing here just looking at these " +
        "shrubberies.\n");

    }

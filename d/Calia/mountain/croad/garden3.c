// ROOM:  palace garden 3

    /* Calia Domain

    HISTORY

    [96-02-24] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN3.DOC].

    PURPOSE

    This room is one of 14 garden rooms surrounding Calia palace.  See comments
    in Room 1 for area details.  */

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

    /*  VARIABLES  */

    string *darks = ({"indigo","vermilion","violet","crimson","azure"});
    string *brights = ({"ivory","pale yellow","snow-white","pink","gold"});
    string *flowers = ({"moonblooms","fairy-slippers","orchids","roses"});
    string *bunches = ({"bunches","rows","displays","clusters"});
    string *adjects = ({"vivid","brilliant","dazzling","spectacular"});

    string dark = darks[(random(sizeof(darks)))];
    string bright = brights[(random(sizeof(brights)))];
    string flower = flowers[(random(sizeof(flowers)))];
    string bunch = bunches[(random(sizeof(bunches)))];
    string adject = adjects[(random(sizeof(adjects)))];

    /*  DESCRIPTION  */

    set_short("Calia Palace Gardens, west side");

    set_long("This part of the garden is filled with flowering shrubs, " +
        "and your attention is immediately drawn to the vivid " +
        "contrast of bright flowers against dense green foliage.  " +
        "The shrubs are lower than the nearby willows and vines, " +
        "and over them you can get a good view of both the mist " +
        "that perpetually rings Mt. Kyrus and of the towering " +
        "crystal palace.\n");

    /*  EXITS  */

    add_exit(CROAD + "garden2", "southeast", 0);
    add_exit(CROAD + "garden4", "north", 0);

    /*  ITEMS  */

    add_item(({"garden","gardens"}),
        "This part of the garden is planted with low flowering " +
        "shrubs that border both sides of the stone path.  It's a " +
        "bit brighter than the somber rows of willows, and you " +
        "find yourself tempted to linger here to enjoy the " +
        "delicate fragrance of the flowers.\n");

    add_item(({"flowers","shrubs","flower","shrub","foliage"}),
        "There is a variety of flowering shrubs here, selected so that " +
        "at least one kind is always in bloom.  " +
        "Today there are " + adject + " " + bunch + " of " + dark +
        " and " + bright + " " + flower + " among the lush green foliage.\n");

    add_item(({bunch,flower}),
        "The " + bunch + " of " + flower + " are so colorful and " +
        "fragrant, you begin to suspect that they opened up just " +
        "as you entered the garden, and you wonder if they'll close " +
        "up again when you leave to preserve their freshness for " +
        "the next visitor.\n");

    add_item(({"willow","willows","path"}),
        "The path leads southeast through the willows back to the " +
        "palace entrance and north deeper into the garden.\n");

    add_item(({"vine","vines"}),
        "The vines grow on a high wall at the rear of the palace.\n");

    add_item(("mist"),
        "Waves and currents undulate through the mist, " +
        "and the stark contrast and rhythm of the dancing " +
        "light and shadow produces a somewhat hypnotic effect.\n");

    add_item(({"palace","colors"}),
        "The faceted sides of the palace reflect the green, " +
        dark + ", and " + bright + " of the flowering shrubs.  " +
        "As you move, the colors rotate and shift in fascinating " +
        "kaleidoscopic symmetry.\n");

    }

// ROOM:  palace garden 4

    /* Calia Domain

    HISTORY

    [96-02-26] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN4.DOC].

    PURPOSE

    This is one of 14 garden rooms surrounding Calia palace.  See comments in
    Room 1 for layout details.  */

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

    set_short("Calia Palace Gardens, west side");

    set_long("Here a decorative wall has been built " +
        "which has been completely covered with vines.  " +
        "This is a rather narrow space you're walking in now, " +
        "between the wall to your west and the palace to your east, " +
        "but it's cheerful and well-lit because of all the light " +
        "reflected by the crystalline sides of the palace.  The path " +
        "is paved with stones to the south and with gravel " +
        "to the northeast where it leads through a rose trellis.\n");

    /*  EXITS  */

    add_exit(CROAD + "garden3", "south", 0);
    add_exit(CROAD + "garden5", "northeast", 0);

    /*  ITEMS  */

    add_item(({"garden", "gardens"}),
        "The sides of the palace confine your view to this small " +
        "area beside the vine-covered wall, but an occasional " +
        "breeze wafts tantalizing aromas your way, luring you to " +
        "explore what lies beyond the rose trellis.\n");

    add_item(({"trellis", "rose trellis"}),
        "The trellis is constructed in the form of an arch and " +
        "is completely covered with roses.  They form a floral " +
        "tunnel that leads into another part of the garden, but " +
        "the passage curves so that you can't see what lies on " +
        "the other side.\n");

    add_item(({"rose", "roses", "arch", "passage", "tunnel", "floral tunnel",
        "rose tunnel"}),
        "The passage is built from an arch-shaped trellis completely " +
        "covered with roses.  A seductive perfume wafts from " +
        "within.  You can distinguish the fragrance of the roses, but " +
        "there are definitely other scents mixed with it.\n");

    add_item(({"wall","decorative wall"}),
        "The wall serves to protect the garden from the winds " +
        "that sometimes howl across the summit.\n");

    add_item(({"vine", "vines"}),
        "The vines grow vigorously, " +
        "almost completely obscuring the wall with a coat of deep green.\n");

    add_item(({"path", "gravel", "stones"}),
        "The broad flat stones lead toward an area shaded by " +
        "willow trees.  Along the gravel path the site is more open " +
        "and exposed to full sunlight.\n");

    add_item(({"palace", "light", "sides", "side"}),
        "The many-faceted sides of the palace are kept meticulously clean " +
        "and polished.  They rise at curious angles high above your " +
        "head and bounce unexpected splashes of light throughout " +
        "the garden.\n");

    }

/*
 *  /d/Gondor/rohan/isengard/tunnel5.c
 *
 *  Opus, April 1997
 *
 *  Copyright   1997 by Robert Miller
 *
 *  Modification log:
 */

#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>

// Prototypes
int message();

public void
create_isengard()
{
    set_short("inside the ringwall just inside the inner gate");
    set_long(BSN(
        "This tunnel leads through the volcanic ring encircling the "+
        "fortress of Isengard. A torch hangs on the wall which provides "+
        "light for this area of the tunnel. The inner gates are just "+
        "north of here and southward the tunnel continues toward the "+
        "outer gates."));

    add_item( ({"inner gate", "inner gates"}), BSN(
        "The inner gates of the fortress of Isengard are made from "+
        "solid, black iron. Twenty feet tall, and equally wide, the "+
        "gates lead into the central plain of Isengard."));
    add_item( ({"outer gate", "outer gates"}), BSN(
        "Traveling southward in this tunnel will lead to the outer "+
        "gates and ultimatly into the wilderness outside.")); 
    add_item( ({"gate", "gates"}), BSN(
        "Immeditately to the north stands the inner gates, and in the "+
        "distance, to the south, are the outer gates."));
    add_item("torch", BSN(
        "Thick, tar-dripped branches have been placed into holders along "+
        "the walls here. They burn brightly, but the dark smudge of smoke "+
        "that rises from each deadens the light somewhat."));
    add_cmd_item("torch", ({"get", "take"}), BSN(
        "Some type of magical force prevents you from removing the "+
        "torch from its holder."));
    add_cmd_item("torch", ({"extinguish", "put out"}), BSN(
        "Some type of magical force prevents you from manipulating the "+
        "torch in that way."));
    add_item( ({"wall", "walls"}), BSN(
        "A testament to the power of ancient man, the walls have been "+
        "smoothly carved from the strong, black rock that composes this "+
        "entire area."));
    add_item( ({"floor", "ground"}), BSN(
        "From taking a closer look at the strong, black rock that makes up "+
        "this entire area, it is hard to imagine how the floor could have "+
        "been so smoothly carved."));
    add_item( ({"holder", "holders"}), BSN( 
        "These black, metal holders have been attached to the wall "+
        "along the tunnel so that torches can light a person's way."));
    add_item( ({"fortress", "isengard"}), BSN(
        "It is impossible to see Isengard from inside this tunnel."));
    add_item( ({"rock", "black rock", "smooth rock", 
        "smooth black rock"}), BSN(
            "This strange black rock, which makes up the entire area, "+
            "has been carved and shaped to form a passageway through "+
            "the ringwall."));
    add_item( "tunnel", BSN(
        "Carved through the strange black rock making up the ringwall, "+
        "this passage remains the only known way in and out of Isengard."));
    add_item( ({"ring", "ring wall", "volcanic ring", "ringwall",
        "volcanic ring wall", "volcanic ringwall"}), BSN(
            "Only the black rock, through which this tunnel has been "+
            "constructed, is visable from here."));
    add_item( "ceiling", BSN(
        "High above, the ceiling of the tunnel is perfectly "+
        "rounded making it difficult to tell where the ceiling ends and "+
        "the wall begins."));

    add_exit(ISEN_DIR + "ringrd1",  "north", message);
    add_exit(ISEN_DIR + "tunnel4",  "south", 0);  
    add_prop(ROOM_I_INSIDE, 1);
}

/*
 *  Function:    message
 *  Description: prevents mortal from passing until rooms beyond finished
 *  Returns:     1/0
 */

public int
message()
{
    if (TP->query_wiz_level())
    {
        write("This exit is still closed to mortals, wizard.\n");
        return 0;
    }
    else
    {
        write("The gates are closed and are not able to be passed yet.\n");
        return 1;
    }
}

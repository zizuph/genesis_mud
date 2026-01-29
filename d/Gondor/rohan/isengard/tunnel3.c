/*
 *     /d/Gondor/opus/rohan/isengard/tunnel3.c
 *
 *     Opus, April 1997
 *
 *     Copyright   1997 by Robert Miller
 *
 *     Modification log:
 */
#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>

/*
 * Prototypes:
 */
public void    reset_room();

/* 
 * Global variables:
 */
static object  Guard;
   //guard found in the tunnel room.

public void
create_isengard()
{
    set_short("halfway through the ring-wall tunnel");
    set_long(BSN(
	"This is about halfway through the volcanic ring tunnel. "+
	"A torch hangs on the wall which provides light for this area of "+
	"the tunnel. To the west a small set of stairs leads "+
	"up to a wooden door with two windows beside it. Traveling to the "+
	"north will lead to the inner gates, while to the south "+
	"the outer gates can be reached."));

    add_item("stairs", BSN(
	"A small set of stairs leads from the floor up to a wooden door "+
	"to the west. They are made from the same black rock that makes up "+
	"this entire area."));
    add_item( ({"window", "windows"}), BSN(
	"A small window has been cut out of the wall on each side of a "+
	"wooden door at the top of a small set of stairs. The windows "+
	"are too high for anyone to look through from this side."));
    add_item("torch", BSN(
	"Thick, tar dropped branches have been placed into holders along "+
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
    add_item( ({"ground", "floor"}), BSN(
	"From taking a closer look at the strong, black rock that makes up "+
	"this entire area, it is hard to imagine how the floor could have "+
	"been carved so smoothly."));
    add_item( ({"holder", "holders"}), BSN(
	"These black, metal holders have been attached to the wall along "+
	"the tunnel so that torches can light a person's way."));
    add_item( ({"gate", "gates"}), BSN(
	"A set of inner gates lies to the north, while the outer gates are "+
	"south of here."));
    add_item( ({"outer gate", "outer gates"}), BSN(
	"Visible to the south, the outer gates lead into the wilderness "+
	"outside."));
    add_item( ({"inner gate", "inner gates"}), BSN(
	"Visible to the north, the inner gates lead into a grassy plain "+
	"protected on all sides by the ring wall."));
    add_item( ({"rock", "black rock", "smooth rock", 
	"smooth black rock"}), BSN(
	    "This strange black rock, which makes up the entire area, "+
	    "has been carved and shaped to form a passageway through "+
	    "the ringwall."));
    add_item( ({"fortress", "isengard"}), BSN(
	"The fortress of Isengard is not visable from inside this tunnel."));
    add_item( ({"tunnel", "passage", "passageway"}), BSN(
	"Carved through the strange, black rock making up the ringwall, "+
	"this passage remains the only known way in and out of Isengard."));
    add_item( ({"ring", "ring wall", "volcanic ring", "ringwall", 
      "volcanic ring wall", "volcanic ringwall"}), BSN(
	    "Only the black rock, through which this tunnel has been  "+
          "constructed, is visable from here."));
    add_item( ({"plain", "grassy plain"}), BSN(
	"The grassy plains cannot be seen from here since they lie beyond "+
	"the solid inner gates."));
    add_item ( ({"hinges", "hinge"}), BSN(
	"Three large, solid black hinges hold the door securly onto the "+
	"wall."));
    add_item( "ceiling", BSN(
	"High above, the ceiling of the tunnel is perfectly "+
	"rounded making it difficult to tell where the ceiling ends and "+
	"the wall begins."));
    add_item( "this", BSN(
	"As opposed to that."));
    
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ISEN_DIR + "tunnel4", "north", 0);
    add_exit(ISEN_DIR + "tunnel2", "south", 0);
    clone_object(ISEN_DIR + "obj/guardrm1.c")->move(TO);

    reset_room();
}

public void
reset_room()
{
    Guard = clone_npc(Guard, ISEN_DIR + "npc/isen_captain");
}

/*
 * COAST8.c
 * Coastal Road leading into the ruins of Kamesh.
 * Inside the gate.
 * - Alaron December 1996
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Dark, foggy path");
    set_long("   A thick, damp fog hangs over the area like a draped "+
	     "blanket of shadow. The overgrown road is not much more than "+
	     "a somewhat visible area of trampled grass and worn soil. "+
	     "There are a few ruts in the ground indicative of wagon "+
	     "traffic from years ago. The path is dominated to the north "+
	     "by a huge, twisted and broken iron gate. The soft sound of " +
             "crashing waves can be "+
	     "heard in the distance to the north and east just beyond "+
	     "the tops of the cliffs hidden by the mist. A small section "+
	     "of the path continues south.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"fog", "damp fog", "thick fog", "thick damp fog", "mist"}),
	     "The fog hanging over the area like a draped blanket dulls "+
	     "all of the surrounding colors, making it look as if you "+
	     "were looking at the world through a gray painted window.\n");

    add_item("ruts",
	     "The ruts in the soil were caused by frequent wagon traffic "+
	     "to and from this area long ago. The amount of overgrowth "+
	     "on the path leads you to believe that this place has not "+
	     "seen such traffic in a long time.\n");

    add_item(({"gate", "twisted gate", "iron gate", "huge gate",
	       "broken gate", "broken iron gate", "twisted iron gate",
	       "twisted broken gate"}),
	     "The gate covering the path just to the north of here is "+
	     "enormous. In its prime, it was a majestic iron gate of "+
	     "thick iron bars fenced by three horizontal iron beams "+
	     "pointed at the ends in an 'arrowhead' style. The gate has "+
	     "long since been bent and broken. The stone blocks on either "+
	     "side of the road which used to provide support and hinges "+
	     "for the fence are now not much more than rubble. There is "+
	     "a silver plate hanging from a rusted chain on the gate.\n");

    add_item( ({"plate", "silver plate", "rusted chain", "chain"}),
	     "The silver plate is on the north side of the fence. From "+
	     "the indentations and markings on the back of the plate, you "+
	     "guess that there might be something carved into the front "+
	     "of it but you can't see from here.\n");

    add_exit("coast7", "north");
    add_exit("coast9", "east");
}

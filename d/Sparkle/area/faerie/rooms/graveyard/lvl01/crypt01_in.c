/*
 * Inside the crypt of the the graveyard
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <money.h>

inherit "/std/room"; 
inherit GRAVEYARD_BASE;

void
create_graveyard_room()
{
    set_short("Inside a dark crypt");
    set_long("The crypt is circular and looks like it was once an elegant " +
        "building for the dead. Now, the room is bare and stripped of " +
        "anything valuable except for two coffins. A staircase leads " +
        "downstairs beneath the building.\n");

    add_item(({"lintel", "wide lintel"}),
        "This is a horizontal piece of stone. It runs horizontal and " +
        "is placed above the entrance. On the door are carved runes.\n");
    add_item(({"entrance"}),
        "The entrance is a wide opening that goes outside. It looks like " +
        "there may have been a door in its place, but now it is gone. " +
        "On either side of the entrance are pilasters, with a wide " +
        "lintel resting on top of them.\n");
    add_item(({"walls"}),
        "The walls are circular without any windows. They are made of " +
        "gray stones that were once painted, but the paint has flaked " +
        "off the walls, leaving the walls bare.\n");
    add_item(({"paint"}),
        "The colors look like they were once vibrant colors. Now they " +
        "have faded and been reduced to little more than flakes on " +
        "the walls and ground.\n");
    add_item(({"flakes", "flakes of paints", "paint flakes"}),
        "These are bits of paint that have fallen off the walls and dome.\n");
    add_item(({"dome"}),
        "The dome is large and circular. It is made of blocks of gray " +
        "stone. They are chipped and look like they were once painted and " +
        "smooth. Cracks run up the dome, and the oculus is broken.\n");
    add_item(({"oculus"}),
        "The oculus is the hole in the top of the dome. It is round " +
        "and the only source of light in the crypt. It is cracked and " +
        "chipped, and has expanded over time so that the hole is much " +
        "larger than originally constructed.\n");
    add_item(({"staircase"}),
        "The staircase is set in the back of the crypt. It's circular " +
        "and descends below the crypt.\n");
    add_item(({"coffins"}),
        "They are long and turned over on their sides. The coffins were " +
        "once made of wood, but are now broken and splintered.\n");
    add_item(({"ground", "floor"}),
        "The ground is made of gray stones. They are smooth but some " +
        "have cracks in them. Paint flakes lay in piles around the " +
        "perimeter of the room.\n");
    add_item(({"runes"}),
        "The runes are carved into the lintel. They are in an unknown " +
        "language that flows gracefully across the surface.\n");
    add_item(({"pilaster", "pilasters"}),
        "These are rectangular columns that extends partially from " +
        "the wall. It is strictly ornamental.\n");
    add_item(({"gray stone", "blocks of gray stone", "stone"}),
        "The blocks of grey stone are large and make up the crypt. They " +
        "are stacked so that the seams are barely noticeable. The blocks " +
        "of stone look like they were once very smooth, but now cracked.\n");
    add_item(({"paintings"}),
        "The paintings appear to have illustrated grand events in the " +
        "history of the bodies buried here. However, they have faded " +
        "and the paint has flecked off and fallen off the walls and dome.\n");
    add_item(({"cracks", "cracks in the dome", "cracks in dome"}),
        "The cracks are irregular and run through the dome. Many of " +
        "them are large and snake through the dome.\n");

    add_exit(GRAVE2_DIR + "crypt02",  "down");
    add_exit(GRAVE1_DIR + "crypt01",  "out");
    add_prop(ROOM_I_INSIDE, 1); // not outdoors!

    reset_room();
}

void
reset_room()
{

}

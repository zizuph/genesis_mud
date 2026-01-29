/*
 *  /d/Gondor/minas/citadel/palantir_room.c
 *
 *  Palantir Chamber at the top of the White Tower
 *
 *  Alto, 22 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

object ptable;

public void
create_gondor()
{
    set_short("Chamber at the top of the White Tower");
    set_long("This chamber perches at the very top of the White Tower of "
        + "Ecthelion. The room is of plain white stone, with no furnishings "
        + "save a small pedestal in the very center. Four windows "
        + "open into the chamber, and a rain-scented breeze blows through "
        + "the room. A stairwell leads down.\n");

    add_exit(INNER_MINAS + "/citadel/stair/stair22", "down", 0, 0);

    add_item(({"chamber", "white tower", "tower", "room"}), "It contains "
        + "little more than the small pedestal in the center.\n");
    add_item(({"stone", "white stone"}), "Like most of the tower, this room "
        + "is made from native stone quarried from the foothills of Mount "
        + "Mindolluin. Even the small pedestal in its center is made of the "
        + "same stone.\n");
    add_item(({"window", "windows"}), "Which one? There are four of them. "
        + "Each faces ninety degrees from those beside it, north, south, "
        + "east, and west.\n");
    add_item(({"first window", "north window"}), "This window opens upon the "
        + "north face of the tower. Looking through it you can see league "
        + "upon tens of leagues across the northern expanse of Gondor. Great "
        + "events are unfolding, and for a brief moment your mind is filled "
        + "with images of riders moving upon the plains of Rohan coming ever "
        + "closer, and strange giant creatures striding through a ruined "
        + "fortress with a tower in the middle of the wreckage.\n");
    add_item(({"northern expanse"}), "It can be seen through the north "
        + "window.\n");
    add_item(({"riders", "plains", "rohan"}), "Try as you might, you cannot "
        + "seem to focus on the things in Rohan long enough to gather more "
        + "details.\n");
    add_item(({"creatures", "strange creatures", "fortress", "wreckage"}),
        "You think it is Orthanc, stronghold of Saruman the Wise, but you "
        + "cannot seem to focus on things long enough to be sure.\n");
    add_item(({"second window", "west window"}), "This window opens upon the "
        + "west face of the tower. Looking through it you can see league "
        + "upon tens of leagues across the western expanse of Gondor. The "
        + "mountains of Ered Luin stretch away into the distance. Farmers "
        + "of the Lossarnach are busily herding cattle into shelters to "
        + "brace for the coming storm.\n");
    add_item(({"western expanse"}), "It can be seen through the west "
        + "window.\n");
    add_item(({"mountains", "ered luin", "ephel duath"}), "Both mountain "
        + "ranges, the Ered Luin and the "
        + "Ephel Duath, can be seen through the windows. It is too "
        + "difficult to focus on either for long enough to gather specific "
        + "details of the events unfolding there.\n");
    add_item(({"farmers", "lossarnach", "cattle", "shelters", "storm"}),
        "Try as you might, you cannot seem to focus on the things in the "
        + "Lossarnach long enough to gather more details.\n");
    add_item(({"third window", "south window"}), "This window opens upon the "
        + "south face of the tower. Looking through it you can see league "
        + "upon tens of leagues across the southern expanse of Gondor. "
        + "At the mouths of the Anduin, near the great Sea, a great fleet "
        + "of ships is gathering.\n");
    add_item(({"southern expanse"}), "It can be seen through the south "
        + "window.\n");
    add_item(({"mouths", "mouths of the anduin", "sea", "fleet", "ships"}),
        " The ships appear to be manned by the corsairs of Umbar. You "
        + "cannot seem to focus on them to gather more detailed information.\n");
    add_item(({"fourth window", "east window"}), "This window opens upon the "
        + "east face of the tower. Looking through it you can see league "
        + "upon tens of leagues across the eastern expanse of Gondor. You "
        + "see a great mountain range, the Ephel Duath, upon which rests a "
        + "great city that would be the twin of the one below, were it not "
        + "for the darkness surrounding it. Beyond the mountains is the orange "
        + "glow of fire, and just at the horizon is a darkness so complete "
        + "it cannot be penetrated. You have the strong feeling the darkness "
        + "is far from empty. Something inside it seems to be watching you "
        + "even now.\n");
    add_item(({"eastern expanse"}), "It can be seen through the east "
        + "window.\n");
    add_item(({"city"}), "The dark city on the Ephel Duath was once known "
        + "as Minas Ithil, but is now called Minas Morgul. You cannot seem "
        + "to focus on it long enough to gather more detail of what is "
        + "transpiring there.\n");
    add_item(({"darkness"}), "Darkness is gathering in the east. It nearly "
        + "obscures the view through the east window. At its deepest it "
        + "cannot be penetrated with the naked eye, and yet you can feel the "
        + "brooding malice lurking within it.\n");
    add_item(({"orange glow", "glow", "fire"}), "It must be coming from the "
        + "Cracks of Doom at Orodruin, which has wakened again after many "
        + "years of quiescence.\n");
    add_item(({"floor", "ceiling", "roof", "wall"}), "It is made of native "
        + "white stone.\n");
    add_item(({"stairwell", "stairs"}), "The stairwell opens to one side of "
        + "and leads back down to the great hall.\n");
    add_item(({"mountain", "mount mindolluin", "hill"}), "Rising "
        + "behind the "
        + "White Tower is the dark mass of Mount Mindolluin. The deep "
        + "purple shadows of its high glens and its tall face "
        + "are so large that you cannot take it all in at a single "
        + "glance.\n");
    add_item(({"glens", "face"}), "The mountain towers so huge about "
        + "the Citadel that you get dizzy looking up at it.\n");
    add_item(({"small pedestal", "pedestal", "stone pedestal"}),
          "This is a small pedestal made of native stone. In fact, "
        + "it appears to grow right out of the stone of the floor.\n"
        + "There is a small crystal stone on top of it.\n");

    ptable = clone_object(INNER_MINAS + "/obj/palantir.c");
    ptable->move(TO);


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);

    /* Note that I do not add reset_room() - only one palantir per boot! */
}

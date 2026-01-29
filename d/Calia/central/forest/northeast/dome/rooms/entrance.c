// ROOM:  Dome - Entrance to Dome
//        DOME_ROOMS + entrance

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        The main stopping point for hostile intruders, the
        hedonists still keep a strong guard here. Their
        wealth and luxery goods sometimes tempt bandits and
        worse to attack.

        AREA HISTORY
        This is the last vestige of the origional fortress
        nature of the dome. Even it has been beautifully
        decorated and furnished.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Pleasure Dome entrance");

    set_long("This oddly shaped room is lit by brightly " +
        "burning lamps set in the walls, and by a skylight " +
        "above. Two massive copper gates stand open, " +
        "allowing people in or out of the dome. To either " +
        "side of the gates are huge copper bars, ready to " +
        "seal the main gates if neccessary. The walls are " +
        "engraved with scenes of combat, and a rug on the floor " +
        "depicts the same.\n");

    /* ITEMS */

    add_item(({"lamps"}),
        "Works of art, these copper lamps are large and burn " +
        "very brightly. They're fixed to the " +
        "wall and so cannot be removed. The bronze surfaces " +
        "of the lamps have been etched with elaborate depictions " +
        "of combat, lone men and women fighting against " +
        "terrible monsters or hoards of enemies.\n");

    add_item(({"gate", "gates", "entrance", "double doors"}),
        "Two copper doors guard the entrance to the dome. " +
        "Over a foot thick, each two meters wide and three " +
        "meters high, they look unpenetrable without heavy " +
        "seige equipment. They are currently open.\n");

    add_item(({"bars", "copper bars"}),
        "These thick bars of copper slide along grooves to hold " +
        "the gates shut. They look able to withstand anything " +
        "except major seige equipment.\n");

    add_item(({"walls"}),
        "The walls are made of copper sheets which have been " +
        "etched skillfully with depictions of combat, lone men " +
        "and women fighting against terrible monsters or hoards " +
        "of enemies.\n");

    add_item(({"copper sheets", "sheets"}),
        "The walls are built with carefully fitted sheets of " +
        "copper. Skillful images have been etched into them " +
        "and they gleam as if new.\n");

    add_item(({"etchings", "images", "depictions", "pictures",
        "scenes"}),
        "Depictions of combat in which lone men and women " +
        "fighting against terrible monsters or hoards of " +
        "enemies have been etched with great skill into the " +
        "copper. The lone figures sometimes triumph, other " +
        "times fall heroically.\n");

    add_item(({"ceiling", "skylight", "glass"}),
        "A bright skylight of thick clear glass provides most " +
        "of this rooms lighting. The wall actually curves into " +
        "the cieling, as this is a dome.\n");

    add_item(({"floor", "rug"}),
        "The floor is made of fitted copper sheets but is " +
        "almost completely covered by a thick wool rug. " +
        "Immaculately clean, the rug is woven with pictures " +
        "of lone men or women fighting against terrible " +
        "monsters or hoards of enemies.\n");

    /* EXITS */

    add_exit("plateau01", "west", 0, 01);
    add_exit("storage", "south", 0, 01);
    add_exit("hall", "east", 0, 01);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 90);

    }

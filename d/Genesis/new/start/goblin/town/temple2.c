/*
 * File         : /d/Genesis/new/start/goblin/town/temple2.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : Temple of Xi Voch - Main Chamber
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <stdproperties.h>

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are in the main chamber of the Temple of Xi Voch");

    set_long("You are in the main chamber of the Temple of Xi Voch.\n" +
    "Your eye is immediately drawn to an imposing statue of Xi Voch " +
    "himself. Dominating the south end of the room, the ancient goblin " +
    "god gestures symbolically down to a small pool of water in a basin " +
    "at his feet. This basin is continually refreshed by a long, narrow " +
    "channel in the tile floor, bringing water in from the north.\n");

    add_item(({"statue", "imposing statue", "xi voch", "god", "goblin god",
    "shrine", "shrine to xi voch"}),
    "The stern posture of Xi Voch makes you a bit uneasy. He is clad in the " +
    "robes of a magic user, yet he has the shaved head and single braid of a " +
    "goblin warrior. High above you, the eyes of the huge statue glow red. " +
    "At the base of the statue, near the water offering, is an inscription.\n");

    add_item(({"eyes", "statue eyes", "eyes of statue",
    "eyes of xi voch", "red eyes"}),
    "The eyes of Xi Voch seem to follow your every move.\n");

    add_item("inscription",
    "Why don't you read it?\n");

    add_cmd_item("inscription", "read",
    "The inscription reads:\n\n" +
    "In this way, we the faithful of Kalerus,\n" +
    "remember the precious gift of life mercifully\n" +
    "given by Him. In this way also, we return to\n" +
    "Him the first of the waters which would sustain\n" +
    "and keep us.\n");

    add_item(({"basin", "water basin", "pool", "water pool", "small pool",
    "water offering", "marble basin"}),
    "The basin at the foot of the statue is carved from fine marble.\n");

    add_item(({"marble"}),
    "The deep red marble from which the water basin is carved is of exquisite " +
    "shade and texture. The color gives the water the appearance of blood.\n");

    add_item(({"channel", "water"}),
    "The water flowing down the channel is presumably diverted under the Temple and " +
    "into the chamber from the waterfall outside. Here, close to the source, the first " +
    "water obtained from the falls is offered back as a poignant sacrifice to Xi Voch.\n");

    add_item(({"floor"}),
    "The ornate tiling on the chamber floor is a change from the bare limestone " +
    "floors which are to be found nearly everywhere else in the cavern city. This " +
    "must be a very special room.\n");

    add_item(({"tile", "floor tile", "tiling"}),
    "The fine floor tiling is light blue until it reaches the water channel. The tiles " +
    "lining the channel are colored to give the water a blood red appearance.\n");

    add_item("chamber",
    "The spacious chamber is topped by a large dome which accomodates the spectacular " +
    "height of the statue.\n");

    add_item(({"dome", "large dome", "walkway", "circular", "walkway"}),
    "Looking up into the dome, you can see that a small, circular walkway offers visitors " +
    "a closer view of the face of the statue.\n");

    add_exit("temple1", "west");
    add_exit("temple3", "east");
}

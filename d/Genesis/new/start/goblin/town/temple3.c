/*
 * File         : /d/Genesis/new/start/goblin/town/temple3.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : Temple of Xi Voch - East Wing
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
    set_short("You are in the east wing of the Temple of Xi Voch");

    set_long("You are in the east wing of the Temple of Xi Voch.\n" +
    "A large circular pedestal rises from the center of the room. " +
    "Atop it burns a warm fire. There is a plaque attached to the " +
    "pedestal. A large chamber lies to the west while a passage to " +
    "the south will take you out of the Temple. A set of stairs leads " +
    "up.\n");

    /* Describe: fire shrine to The Six, stairs. */

    add_item(({"pedestal", "circular pedestal", "stone pedestal",
    "carving", "goblins"}),
    "The stone pedestal is intricately carved with hundreds of tiny " +
    "goblins. Near the scorching hot rim is a small plaque.\n");

    add_item(({"fire", "warm fire"}),
    "The fire burns with a blistering heat. Staring into the flickering " +
    "flames, you notice twelve small spheres floating inside. Slowly " +
    "spinning and falling about each other, they are propelled by an " +
    "unseen force.\n");

    add_item(({"spheres", "twelve spheres", "12 spheres", "eyes",
    "twelve eyes", "12 eyes", "eyes of the six"}),
    "The twelve little spheres careen around through the fire, never " +
    "touching one another, never ceasing.\n");

    add_item(({"plaque", "small plaque", "pedestal plaque", "gold plaque",
    "golden plaque"}),
    "The golden plaque is engraved with an inscription.\n");

    add_item(({"inscription", "engraving"}),
    "The inscription is done in very fine lettering.\n");

    add_cmd_item(({"inscription", "engraving", "plaque", "small plaque"}), "read",
    "The inscription reads:\n\n" +
    "Preserved here, in the burning fires\n" +
    "of their terrible ordeal, may the\n" +
    "Eyes of the Six keep eternal vigil\n" +
    "over us.\n");

    add_item(({"stairs", "stairway"}),
    "The stone stairs lead up.\n");

    add_exit("temple2", "west");
    add_exit("cavern_d4", "south");
    add_exit("temple4", "up");

    set_noshow_obvious(1);
}

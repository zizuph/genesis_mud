/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_a1.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : "Outdoors" in the Kalerus cavern
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
    set_short("You are in a large cavern");

    set_long("You are in a large cavern.\n" +
    "The walls here are dimly lit by a soft, green glow. Sleeping " +
    "cells dot the east, south, and west faces. To the north, the " +
    "small city of Kalerus lies quietly in the perpetual night. It " +
    "looks tiny in relation to the giant waterfall pouring down " +
    "from the north face just beyond it. Nearby, the Training Hall " +
    "is north of you, the Kalerus Museum and the Ghiza River to " +
    "the east. A small tunnel leads south.\n");

    /* 
     * Begin - Things that are visible from any "outdoor" location 
     * in the cavern.
     */

    add_item(({"cavern", "walls", "cavern walls"}),
    "The cavern is quite enormous. Whether it was created by natural " +
    "forces or otherwise, it must have taken quite some time.\n");

    add_item(({"north face", "north wall", "waterfall", 
    "enormous waterfall", "massive waterfall", "giant waterfall",
    "falls", "ghiza falls"}),
    "The giant waterfall enters the cavern near the top of the north " +
    "wall and disappears behind the city's largest structure.\n");

    add_item(({"cells", "sleeping cells", "faces", "east face",
    "east wall", "west face", "west wall"}),
    "All but the north face of the cavern interior are dotted with " +
    "the hundreds of goblin sleeping cells.\n");

    add_item(({"south face", "south wall"}),
    "The south wall of the cavern is dotted with many goblin " +
    "sleeping cells. In the distance, you can see the river " +
    "disappear into a large tunnel at the base of the wall. " +
    "Nearby, there is also a smaller tunnel leading south.\n");

    add_item(({"floor", "stone floor", "cavern floor"}),
    "The stone floor is extremely smooth. It is covered with a thin " +
    "layer of water.\n");

    add_item(({"large tunnel", "larger tunnel", "river tunnel",
    "ghiza river tunnel"}),
    "The river disappears into the tunnel as abruptly as it appears " +
    "from beneath the museum.\n");

    add_item(({"city", "small city", "kalerus"}),
    "There is a wonderful stillness to the city, a vast amount of " +
    "open space overhead gives the illusion of continuous night " +
    "time.\n");

    add_item(({"stone", "limestone", "architecture", "enclosures"}),
    "The interior of the cavern and all of the enclosures within it " +
    "are constructed of a highly polished, slightly damp limestone.\n");

    add_item(({"structure", "large structure", "largest structure",
    "temple", "temple of xi voch"}),
    "The city's most prominent structure lies at the base of the " +
    "waterfall. It is topped with several ornate spires, though you " +
    "can't make out much detail from this distance.\n");

    add_item(({"spires", "ornate spires"}),
    "You can't make out much detail from this distance.\n");

    add_item(({"glow", "green glow"}),
    "The walls are covered with tiny, worm-like creatures. Their " +
    "bodies give off a faint, green glow, illuminating the cavern " +
    "mist.\n");

    add_item(({"worms", "worm-like creatures", "creatures", "kuula"}),
    "The tiny, glowing worms slither blindly about on the rock " +
    "walls.\n");

    add_item(({"mist", "heavy mist"}),
    "A thick mist fills the air, presumably given off by the falls " +
    "and trapped here in the cavern.\n");

    /*
     * End - Things that are visible from any "outdoor" location 
     * in the cavern.
     */

    add_item(({"tunnel"}),
    "Which tunnel?\n");

    add_item(({"small tunnel", "smaller tunnel"}),
    "The small tunnel in the south face leads off into darkness.\n");

    add_item(({"plaza", "central plaza"}),
    "The Plaza is located at the heart of the cavern floor. A large " +
    "fire burns there.\n");

    add_item(({"hall", "training hall"}),
    "The Training Hall is a stone building which looks onto the " +
    "town's central plaza.\n");

    add_item(({"museum", "kalerus museum"}),
    "The Kalerus Museum looks onto the town's central plaza. It " +
    "seems to give rise to a sizeable which mysteriously appears " +
    "from beneath its foundation.\n");

    add_item(({"river", "ghiza river"}),
    "The river seems to emerge from beneath the museum. It " +
    "then runs briefly south before it exits the cavern through a " +
    "tunnel in the south wall.\n");

    add_exit("cavern_b1", "north");
    add_exit("cavern_a2", "east");
    add_exit("sleeping_tunnel7", "south");
}

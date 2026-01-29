/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_a2.c
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
    set_short("You are standing on the bank of The Ghiza River");

    set_long("You are standing on the bank of The Ghiza River.\n" +
    "The river emerges from beneath the nearby Kalerus Museum and " +
    "flows out of the cavern through a tunnel in the south wall. The " +
    "Training Hall is located off the Central Plaza to the " +
    "northwest. The walls here are dimly lit by a soft, green glow.\n");

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

    add_item(({"tunnel", "large tunnel", "river tunnel",
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

    add_item(({"river", "ghiza river", "tunnel"}),
    "The swirling river is accompanied into the south tunnel by a " +
    "narrow walkway along the opposite bank.\n");

    add_item(({"opposite bank", "far bank", "walkway", "narrow walkway"}),
    "You cannot see any way to reach it from here. It looks like " +
    "you'll just have to go around.\n");

    add_item(({"this bank", "near bank"}),
    "The river emerges from beneath the nearby Kalerus Museum and " +
    "flows out of the cavern through a tunnel in the south wall. The " +
    "Training Hall is located off the Central Plaza to the " +
    "northwest. The walls here are dimly lit by a soft, green glow.\n");

    add_item(({"bank"}),
    "Which bank?\n");

    add_item(({"plaza", "central plaza"}),
    "The Plaza is located at the heart of the cavern floor. A large " +
    "fire burns there.\n");

    add_item(({"training hall", "hall"}),
    "The Training Hall is a stone building which looks onto the " +
    "town's central plaza.\n");

    add_item(({"museum", "kalerus museum"}),
    "From here, you can see the rear of the building. Made " +
    "entirely of glass, the Museum stands out among the extensive " +
    "stonework of Kalerus. There appear to be some interesting " +
    "exhibits inside.\n");

    add_item(({"exhibits", "museum exhibits"}),
    "The glass of the Museum is too thick for you to get a good look " +
    "at the exhibits from here.\n");

    add_exit("cavern_a1", "west");
    add_exit("cavern_b1", "northwest");
}

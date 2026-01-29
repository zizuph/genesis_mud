/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_d5.c
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
    "The walls here are dimly lit by a soft, green glow. Nearby, the " +
    "massive waterfall plunges down behind the stone Temple. Emerging " +
    "from beneath the east side of the Temple is a rather large water " +
    "channel cut into the stone floor of the cavern. You can traverse " +
    "it by way of a stone footbridge to the north.\n");

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
    "wall and disappears behind the Temple.\n");

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
    "Lying at the base of the waterfall, the Temple is the city's " +
    "most prominent structure. Like most of the other Kalerian " +
    "architecture, the Temple seems to be more of a sculpture " +
    "than a building. Indeed, all of these enclosures appear to " +
    "have been carved directly from the surrounding limestone. " +
    "The magnificent Temple is topped with several ornate spires.\n");

    add_item(({"spires", "ornate spires", "carving", "carvings",
    "goblin carvings"}),
    "The Temple's many spires are adorned with carvings of goblins " +
    "reaching up to the massive waterfall which pours down behind " +
    "the structure.\n");

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

    add_item(({"channel", "water channel"}),
    "The channel emerges from beneath the Temple, efficiently " +
    "guiding the water down beneath the Shop where it " +
    "disappears again.\n");

    add_item(({"water", "channel water"}),
    "The water is crystal clear.\n");    

    add_item(({"bridge", "footbridge", "small bridge", 
    "small footbridge"}),
    "Arising seamlessly from the cavern floor, the small, limestone " +
    "bridge becomes a path which disappears behind the Temple.\n");

    add_exit("cavern_e4", "north");
    add_exit("cavern_d4", "west");
}

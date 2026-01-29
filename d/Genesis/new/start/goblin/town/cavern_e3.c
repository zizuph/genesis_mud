/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_e3.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : The base of Ghiza Falls
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
    set_short("You are at the base of a massive waterfall");

    set_long("You are at the base of a massive waterfall.\n" +
    "This small observation deck behind the Temple offers a closer " +
    "view of the enormous waterfall than anywhere else in the " +
    "cavern. A retaining wall prevents the hapless visitor from " +
    "stepping off into the swirling water. There is a plaque " +
    "mounted on the retaining wall. Paths leading off to the " +
    "southeast and southwest disappear around either side of the " +
    "Temple.\n");

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
    "As you stare up into the mighty falls, your mind tries to comprehend " +
    "the scale of it. High above, you can just barely see the point where " +
    "it enters the cavern. You can feel the cool spray on your face as the " +
    "water plunges into the swirling pool below.\n");

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
    "From the rear, the Temple appears just as grand as it does from " +
    "the front. The excellent stonework of the structure focuses your " +
    "eye upward to the intricate spires.\n");

    add_item(({"spires", "ornate spires", "carving", "carvings",
    "goblin carvings"}),
    "The Temple's many spires are adorned with carvings of goblins " +
    "reaching up to the massive waterfall.\n");

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

    add_item(({"wall", "retaining wall"}),
    "The retaining wall rises to roughly chest height, allowing you to " +
    "peer down into the churning water below.\n");

    add_item(({"plaque", "gold plaque", "golden plaque"}),
    "A golden plaque is attached to the retaining wall. An inscription " +
    "has been etched into it.\n");

    add_item(({"inscription", "plaque inscription", "etching"}),
    "An inscription has been etched into the gold plaque in fine " +
    "lettering.\n");

    add_cmd_item(({"plaque", "gold plaque", "golden plaque", "inscription",
    "plaque inscription", "etching"}),
    "read", "The inscription reads:\n\n" +
    "              -- Ghiza Falls --\n\n" +
    "By the will of Xi Voch was this gift given.\n" +
    "If, by His will, it should one day pass away,\n" +
    "so then shall we the faithful of Kalerus.\n");

    add_item(({"water", "swirling water", "churning water"}),
    "As the fresh water from the the falls crashes violently into the " +
    "reservoir below, it reaches out to gently caress your face with a " +
    "light spray \n");

    add_item(({"deck", "observation deck"}),
    "This is a small, semi-private area behind the Temple, which allows " +
    "for close observation of the very life-blood of Kalerus.\n");

    add_item(({"reservoir", "water reservoir"}),
    "The swirling water of the reservoir is carefully diverted around the " +
    "Temple via channels carved into the stone floor of the cavern.\n");

    add_item(({"channel", "water channel"}),
    "While simultaneously harnessing and paying homage to the precious water " +
    "provided by the falls, the channels are an enduring testimony to goblin " +
    "ingenuity.\n");

    add_item(({"water", "channel water"}),
    "The water is crystal clear.\n");

    add_exit("cavern_e4", "southeast");
    add_exit("cavern_e2", "southwest");
}

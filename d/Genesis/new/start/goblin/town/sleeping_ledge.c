/*
 * File         : /d/Genesis/new/start/goblin/town/sleeping_ledge.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 13, 1999
 * Modifications: 
 * Purpose      : Overlooks all of Kalerus
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
    set_short("You are standing on a narrow ledge");

    set_long("You are standing on a narrow ledge.\n" +
    "A massive cavern extends out below you. Dimly lit by a strange, " +
    "green glow, you can just make out a small city stretching out " +
    "across the cavern floor. The most prominent structure is " +
    "situated at the far end of the city, an enormous waterfall " +
    "cascading down behind it. A heavy mist fills the air. Through " +
    "the gloom, you can see a certain amount of activity going on " +
    "in the city. A river disappears into a tunnel far below you. " +
    "You can return to the sleeping cell through an opening in the " +
    "sheer rock wall here.\n");

    add_item(({"ledge", "narrow ledge"}),
    "The ledge does not leave you much room for moving around, but " +
    "affords you a breathtaking view of the cavern and the city " +
    "below.\n");

    add_item(({"glow", "green glow"}),
    "From here, it is difficult to determine what gives the cavern " +
    "its distinctive green glow.\n");

    add_item(({"cavern", "cavern floor", "city", "small city",
    "little city", "kalerus"}),
    "The cavern seems to swallow the little city, a vast amount of " +
    "open space above gives the illusion of perpetual night time. The " +
    "west, south, and east walls of the cavern are dotted with small " +
    "terraces like the one you are standing on.\n");

    add_item(({"structure", "prominent structure"}),
    "The city's largest structure is distant and barely visible " +
    "through the fog. It seems to have multiple spires but is " +
    "dwarfed by the massive waterfall which seems to pour right " +
    "down on it.\n");

    add_item(({"temple", "temple of xi voch"}),
    "The Temple of Xi Voch, the city's largest structure, is distant " +
    "and barely visible through the fog. It seems to have multiple " +
    "spires but is dwarfed by the massive waterfall which seems to " +
    "pour right down on it.\n");

    add_item(({"waterfall", "enormous waterfall", 
    "massive waterfall", "giant waterfall", "falls", "ghiza falls"}),
    "The giant waterfall enters the cavern near the top of the north " +
    "wall and disappears behind the city's largest structure.\n");

    add_item(({"mist", "heavy mist"}),
    "A thick mist fills the air, presumably given off by the falls " +
    "and trapped here in the cavern.\n");

    add_item(({"activity"}),
    "You can see movement down in the city. There is so little light " +
    "that it is difficult to tell who or what is down there.\n");

    add_item(({"river", "ghiza river"}),
    "The river seems to emerge from beneath one of the city's smaller " +
    "buildings which is almost directly below you. The river then " +
    "runs briefly south and appears to exit the cavern through a " +
    "tunnel in the south wall.\n");

    add_item(({"opening"}),
    "The opening leads back to the sleeping cell.\n");

    add_item(({"tunnel"}),
    "From this angle, you can barely see the tunnel, much less " +
    "where it leads.\n");

    add_item(({"cells", "sleeping cells", "other cells", 
    "other sleeping cells", "terraces", "other terraces"}),
    "Looking out over the city are hundreds of sleeping cell terraces " +
    "like this one.\n");

    add_item(({"small building", "smaller building"}),
    "The small building below you seems to give rise to a rushing " +
    "river which appears from beneath it.\n");

    add_item(({"museum", "kalerus museum"}),
    "The Kalerus Museum is directly below you and seems to give " +
    "rise to a rushing river which appears from beneath it.\n");

    add_exit("sleeping_cell", "south");
}

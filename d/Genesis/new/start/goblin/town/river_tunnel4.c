/*
 * File         : /d/Genesis/new/start/goblin/town/river_tunnel4.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 13, 1999
 * Modifications: 
 * Purpose      : The bottom of the oasis well
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#define BUCKET     "/d/Genesis/new/start/goblin/town/bucket"
#define TOP        "/d/Genesis/new/start/goblin/town/well"
#define BOTTOM     "/d/Genesis/new/start/goblin/town/river_tunnel4"

/* Prototypes */
public string bucket_desc1();
public string bucket_desc2();
public string enter_bucket();

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are standing at the base of a well");

    set_long("You are standing on a small rock outcropping at the " +
    "base of a well.\n" +
    "Below you, a river approaches from a tunnel to the north and " +
    "plunges into a black ravine. The tunnel walls are dimly lit by " +
    "a soft, green glow. There is a small control panel here. " +
    bucket_desc1() + "\n");

    add_item(({"glow", "green glow", "walls", "tunnel walls"}),
    "The walls are covered with tiny, worm-like creatures. Their " +
    "bodies give off a faint, green glow, illuminating the way " +
    "through here.\n");

    add_item(({"worms", "worm-like creatures", "creatures", "kuula"}),
    "The tiny, glowing worms slither blindly about on the rock walls.\n");

    add_item(({"bucket", "large bucket"}), bucket_desc2);

    add_cmd_item("bucket", "enter", "@@enter_bucket");

    add_item(({"panel", "control panel", "lever"}),
    "The control panel is carved completely from stone. It has one " +
    "lever.\n");

    add_cmd_item("lever down", ({"push", "pull"}),
    "/d/Genesis/new/start/goblin/town/bucket"->activate_bucket("/d/Genesis/new/start/goblin/town/river_tunnel4", "down"));

    add_cmd_item("lever up", ({"push", "pull"}),
    "/d/Genesis/new/start/goblin/town/bucket"->activate_bucket("/d/Genesis/new/start/goblin/town/river_tunnel4", "up"));

    add_item(({"river", "ghiza river"}),
    "The mighty river rushes past, threatening to sweep you away " +
    "if you venture out from the relative safety of the walkway. Just " +
    "south of you, the water pours over a cliff and disappears into what " +
    "appears to be a bottomless abyss.\n");

    add_item(({"cliff", "abyss", "bottomless abyss"}),
    "From here, the tunnel walls quickly fade out into the darkness. " +
    "You strain your eyes for a moment but are unable to discern even the " +
    "hint of a bottom to this black void.\n");

    add_item(({"tunnel"}),
    "The tunnel follows the river from the north, where it seems to originate, " +
    "to this spot where the river dumps over the cliff in a spectacular " +
    "waterfall.\n");

    add_item(({"waterfall", "falls"}),
    "The loud rush of the waterfall is quite deafening. You can feel a light " +
    "spray on your face as it rushes past.\n");

    add_item(({"walkway"}),
    "This narrow walkway carved into the limestone of the tunnel wall is all " +
    "that separates you from the turbulent waters of the river just below you.\n");

    add_item(({"limestone", "stone", "wall", "tunnel wall"}),
    "The tunnel seems to have been carved from the solid limestone rock which " +
    "now surrounds you.\n");

    add_exit("river_tunnel3", "north");
}

public string
bucket_desc1()
{
    int bucket_position = BUCKET->query_bucket_position();
    if (bucket_position == 0)
    {
        return "A large bucket hangs out over the water.";
    }
    else
    {
        return "";
    }
}

public string
bucket_desc2()
{
    int bucket_position = BUCKET->query_bucket_position();
    if (bucket_position == 0)
    {
        return "The bucket is suspended from a complex system of ropes and " +
        "pulleys which extend up into the shaft of the well. It looks " +
        "large enough to hold a person.\n";
    }
    else
    {
        return "You find no bucket.\n";
    }
}

public string
enter_bucket()
{
    this_player()->move_living("M", BUCKET);
    return "";
}

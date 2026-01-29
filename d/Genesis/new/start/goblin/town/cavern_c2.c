/*
 * File         : /d/Genesis/new/start/goblin/town/cavern_c2.c
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
#include <macros.h>

int sinkhole_open = 0;

public string cross_bridge();
public string open_sinkhole();
public string close_sinkhole();
public string enter_sinkhole();
public string sinkhole_desc();

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are in a courtyard");

    set_long("You are in a courtyard in front of the Training Hall.\n" +
    "There is a small, covered sinkhole here. A wooden sign " +
    "has been posted next to it. The Kalerus Central Plaza is " +
    "directly east. North of the Plaza, you can see the Temple, " +
    "across it to the east is the Shop, with the Museum to the " +
    "south. Your path to the southwest is intersected by a channel " +
    "in the rock carrying water from the Training Hall to the " +
    "Museum. A small footbridge crosses the channel.\n");

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

    add_item(({"hole", "sinkhole", "testing place"}),
    "@@sinkhole_desc");

    add_cmd_item(({"hole", "sinkhole"}), ({"open", "uncover"}),
    "@@open_sinkhole");

    add_cmd_item(({"hole", "sinkhole"}), ({"close", "cover"}),
    "@@close_sinkhole");

    add_cmd_item(({"hole", "sinkhole"}), "enter",
    "@@enter_sinkhole");

    add_item(({"cover", "hole cover", "sinkhole cover"}),
    "The sinkhole cover is fashioned from an unusual armour " +
    "plating.\n");

    add_cmd_item(({"cover", "hole cover", "sinkhole cover"}),
    ({"open", "lift"}), "@@open_sinkhole");

    add_cmd_item(({"cover", "hole cover", "sinkhole cover"}),
    ({"close", "lower"}), "@@close_sinkhole");

    add_item(({"plating", "armour plating"}),
    "The strange sinkhole cover glows green in the dim cavern " +
    "light.\n");

    add_item(({"sign", "wooden sign"}),
    "This little wooden sign looks very old. There is some writing " +
    "on it.\n");

    add_cmd_item(({"sign", "wooden sign", "writing"}), "read",
    "The sign reads:\n\n" +
    "      -- Goblin Ceremonial Testing Place --\n\n" +
    "It is the will of the Council of Elder Servants\n" +
    "that all young goblins seeking the mark of Tpa,\n" +
    "the true sign of goblin adulthood in the community\n" +
    "of Kalerus, must pass through here.\n\n" +
    "Beware, however, for if you enter without first\n" +
    "counseling with Gremulak, the trainer, your trials\n" +
    "will be in vain.\n");

    add_item(({"channel", "water channel"}),
    "The channel emerges from beneath the Training Hall, efficiently " +
    "guiding the water down beneath the Museum where it disappears " +
    "again.\n");

    add_item(({"water", "channel water"}),
    "The water is crystal clear.\n");

    add_item(({"bridge", "footbridge", "small bridge", 
    "small footbridge"}),
    "The small, limestone bridge crosses the water channel to the " +
    "southwest.\n");

    add_cmd_item(({"bridge", "footbridge", "small bridge", 
    "small footbridge"}),
    "cross", "@@cross_bridge");

    add_item(({"plaza", "central plaza"}),
    "The Plaza is located at the heart of the cavern floor. A large " +
    "fire burns there.\n");

    add_item(({"hall", "training hall"}),
    "The Training Hall is a stone building which looks onto the " +
    "town's central plaza.\n");

    add_item(({"museum", "kalerus museum"}),
    "The Kalerus Museum looks onto the town's central plaza.\n");

    add_exit("cavern_d1", "northwest");
    add_exit("cavern_d2", "north");
    add_exit("cavern_d3", "northeast");
    add_exit("cavern_c3", "east");
    add_exit("cavern_b1", "southwest");
    add_exit("training_hall", "west");
}

public string
cross_bridge()
{
    say(QCNAME(this_player()) + 
    " leaves crossing over the footbridge.\n", this_player());

    tell_room("/d/Genesis/new/start/goblin/town/cavern_b1",
    QCNAME(this_player()) + " arrives crossing over the footbridge.\n",
    this_player());

    this_player()->move_living("M", 
    "/d/Genesis/new/start/goblin/town/cavern_b1", 0, 0);

    return "";
}

public string
open_sinkhole()
{
    if (sinkhole_open == 1) return "The sinkhole is already open.\n";
    else
    {
        sinkhole_open = 1;
        add_exit("testing_place1", "down");
        say(QCNAME(this_player()) + " cautiously lifts the sinkhole " +
        "cover. The putrid smell of death wafts out of the dark " +
        "Testing Place.\n");
        return "You cautiously lift the sinkhole cover. The putrid " +
        "smell of death wafts out of the dark Testing Place.\n";
    }
}

public string
close_sinkhole()
{
    if (sinkhole_open == 0) return "The sinkhole is already closed.\n";
    else
    {
        sinkhole_open = 0;
        remove_exit("down");
        say(QCNAME(this_player()) + " lowers the sinkhole cover back " +
        "into place, sealing away the awful odor...for now.\n");
        return "You lower the sinkhole cover back into place, " +
        "sealing away the awful odor...for now.\n";
    }
}

public string
enter_sinkhole()
{
    if (sinkhole_open == 1)
    {
        write("You drop down into the cold, wet tunnel of the " +
        "Testing Place.\n");
        say(QCNAME(this_player()) + " drops down into the sinkhole.\n");
        this_player()->move_living("M",
        "/d/Genesis/new/start/goblin/town/testing_place1", 0, 0);
        return "";
    }
    else
    {
        return "You cannot enter the sinkhole as it is closed, " +
        "probably for good reason.\n";
    }
}

public string
sinkhole_desc()
{
    if (sinkhole_open == 1)
    {
        return "The sinkhole is open. The smell of death lingers " +
        "near the opening.\n";
    }
    else
    {
        return "The sinkhole is closed with a tight-fitting cover.\n";
    }
}

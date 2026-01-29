#pragma strict_types

#include "defs.h"

inherit STDROOM;

public string
island_desc()
{
    if (ELDORAL_KNOWN)
        return "Eldoral Isle";
    return "the strange island";
}

public void
reset_room()
{
    int i,
        num;

    ::reset_room();

    num = sizeof(filter(all_inventory(), &->id(RUBBLE_NAME)));    
    num -= 4;

    setuid();
    seteuid(getuid());

    while (num < 0)
    {
        num ++;
        if (!random(2))
            clone_object(OBJ + "large_rubble")->move(TO);
        else
            clone_object(OBJ + "small_rubble")->move(TO);
        tell_room(TO, "A piece of rubble falls from the " +
            "ceiling.\n");
    }
}

public void
create_room()
{
    set_short("in the ruins of a tower in " + CASTLE_NAME);
    set_long("You are inside of the remains of a tower in " +
        CASTLE_NAME + ". It might have once stood much higher, " +
        "as the ceiling and much of the upper walls have " +
        "collapsed into rubble. The remaining walls now " +
        "serve little more than protection against the " +
        "wind. In the remains of the west wall, you see " +
        "one of the only two apparent exits. What once " +
        "was probably a doorway, time and erosion has turned into a " +
        "V-shaped cleft in the entire wall. Near the base of the north " +
        "wall you see an opening in the floor, the top of a staircase " +
        "leading downwards.\n\n");

    add_item(({"ceiling", "roof", "upper walls"}),
        "What once was the ceiling has long since fallen " +
        "in, along with most of the upper parts of the " +
        "walls, and now lies in a pathetic heap of " +
        "rubble on the floor.\n");
    add_item(({"walls", "east wall", "south wall"}),
        "The walls of the tower are quite unextroardinary, " +
        "built from grey stone blocks, most of their mass " +
        "now lies in piles of debris and rubble on the " +
        "floor.\n");
    add_item(({"north wall"}),
        "Just like the other walls in the tower, most " +
        "of the north wall is missing and quite dreary. " +
        "However, you notice an opening leading down " +
        "a stairwell near it's base.\n");
    add_item(({"west wall"}),
        "The west wall of the tower has fallen to pieces, " +
        "as have the others. What makes it different, " +
        "however, is the large cleft-shaped opening " +
        "in it, that once must have been a doorway, " +
        "that leads out onto a walkway.\n");
    add_item(({"sky", "mist"}),
        "Through the opening left by the collapsed " +
        "ceiling, you can see nothing in the sky but " +
        "the dense white mist that blankets " +
        VBFC_ME("island_desc") + ".\n");
    add_item(({"floor", "ground"}),
        "The floor is quite common, constructed of " +
        "grey stone, and littered with piles of debris " +
        "and rubble. You notice an opening in the " +
        "floor agains the north wall, however, that leads " +
        "down a stairway.\n");
    add_item(({"pile", "piles","rubble", "debris"}),
        "Several piles of broken masonry and stone " +
        "cover the floor, some piled as high as a " +
        "man.\n");
    add_item(({"opening"}),
        "The opening in the floor might once have " +
        "contained a hatch of some sort, but now leads " +
        "directly down a stairway.\n");

    add_exit(RUIN + "skywalk", "west");
    add_exit(RUIN + "build6", "down");

    reset_room();
}

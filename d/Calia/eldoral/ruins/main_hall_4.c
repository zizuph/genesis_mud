#include "defs.h"

inherit STDROOM;

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
    set_short("in a wide hallway in the ruins of " +
        CASTLE_NAME);
    set_long("You have entered a massive room with " +
        "a high, vaulted ceiling. Against the east " +
        "wall stands a wide fireplace beneath a " +
        "magnificent, though cracked, carving on " +
        "the wall. To one side of the fireplace, " +
        "a wide staircase descends through the " +
        "floor. The room is T-shaped, its main " +
        "shape leading north and south, with a wide " +
        "hall branching off towards the west. All " +
        "along the walls you can see the corroded " +
        "remains of fixtures, and a number of piles " +
        "of rubble.\n\n");

    add_item(({"ceiling", "roof"}),
        "Above your head, the fine stonework which went into " +
        "the construction of the vaulted ceiling appears to " +
        "have paid off, as the arched columns have almost " +
        "completely prevented any real damage. Besides a " +
        "few cracks, it seems to be completely intact.\n");
    add_item(({"braces", "columns"}),
        "Tall, gracefully curving columns rise from the floor, " +
        "arching inwards to meet each other in pairs down the " +
        "length of the corridor.\n");
    add_item(({"walls"}),
        "The walls are strongly constructed from large blocks of " +
        "grey stone, which seems to have stood up rather well " +
        "to the passage of time. In fact, short of some crumbling " +
        "evident near the windows higher up, they look much like " +
        "they must have looked untold years ago.\n");
    add_item(({"windows", "window"}),
        "High in the walls, long windows rise vertically, allowing " +
        "ribbons of light to slice downwards through the dust.\n");
    add_item(({"floor", "ground"}),
        "The floor is made from carefully-placed flagstones, and " +
        "is in good shape, aside from a few places where water " +
        "has discoloured them over the years.\n");
    add_item(({"fireplace"}),
        "The fireplace is massive, long enough for two or three " +
        "humans to lie full length in, and certainly long enough " +
        "to allow a large number of people to warm themselves " +
        "before it on a cold night.\n");
    add_item(({"carving"}),
        "Cracked and crumbling in places, the carving still holds " +
        "enough of its original shape to identify the image of a " +
        "warrior impossibly sitting astride the back of a chimera.\n");
    add_item(({"stairway", "staircase"}),
        "In the center of the room, a wide staircase of grey " +
        "stone descends beneath the floor into darkness.\n");
    add_item(({"fixtures"}),
        "What they once may have been, you cannot tell. All that " +
        "remains of them are badly rusted stumps jutting out " +
        "of the walls.\n");
    add_item(({"pile of rubble", "piles of rubble"}),
        "They are simply piles of unidentifiable rubble, but " +
        "their uniformity in size and regularly spaced intervals " +
        "would suggest they were, at one time, statues.\n");
    INSIDE;

    add_exit(RUIN + "throne_room", "north");
    add_exit(RUIN + "dining_hall", "south");
    add_exit(RUIN + "main_hall_3", "west");
    add_exit(RUIN + "main_stairs_n", "down");

    reset_room();
}

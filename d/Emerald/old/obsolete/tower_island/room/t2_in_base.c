#include "../defs.h"

inherit TOWERISL_BASE;

void
create_t2_room()
{
}

nomask void
create_towerisl_room()
{
    add_item(({"floor", "cell floor"}),
        "Constructed of dark grey stone, well fitted blocks form the " +
        "floor of the cell.\n");
    add_item("ceiling",
        "Made out of the same, dark grey stone as the rest of the tower, " +
        "the ceiling stands 4 meters above the floor. You notice a grate " +
        "on one edge of the ceiling, close to the western wall.\n");
    add_item("grate",
        "This grate is far out of reach. When you stand directly " +
        "underneath it you can detect a slight breeze of cool, " +
        "fresh air.\n");

    create_t2_room();
}

void
add_cell()
{
    set_short("small cell");
    set_em_long("This dank room is quite small. There is just enough " +
                "space for a few essential furnishings. A thin, straw pallette " +
                "rests in one corner and a small privy in another. " +
                "In the middle of the room sits a simple wooden chair " +
                "and a small table.\n");
    add_item(({"pallette", "straw pallette", "straw", "bed", "straw bed",
               "thin pallette", "thin straw pallette"}),        
        "A small pile of straw fills the northwest corner of the room. " +
        "It does not look comfortable, but it is clean.\n");
    add_item(({"privy", "toilet", "small privy"}),
        "This privy is quite clean considering its function. You do not " +
        "detect a foul odor nor see any filth, though the seat seems quite " +
        "well used.\n");
    add_item(({"furnishings", "essential furnishings", "furniture"}),
        "You see a table and chair, a privy, and a thin straw pallette " +
        "in various locations around the room.\n");
    add_item(({"walls", "wall", "cell walls"}),
        "Dark grey stone blocks, one atop another form the walls of this " +
        "small cell.\n");
    add_item(({"table", "small table"}),
        "A small wooden table sits in the middle of the room. There are " +
        "scuff marks and scratches all over the surface, but it seems " +
        "stable. There is nothing on the table.\n");
    add_item(({"chair", "wooden chair", "simple chair", "simple wooden chair"}),
        "A simple chair made of wood. It is marked up and the seat is " +
        "well worn, but it seems structurally sound.\n");
}

void
add_hallway()
{
    set_short("Second floor hallway");
    set_em_long("You are walking through the second floor hallway.\n");
    add_item(({"walls", "wall"}),
        "Made of dark grey stone, the blocks that form the walls are well " +
        "fit and sturdy.\n");
}

void
add_dstair()
{
    set_short("Stairs down");
    set_em_long("Stairs down");
}

void
add_ustair()
{
    set_short("Stairs up");
    set_em_long("Stairs up");
}

#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("within a ruined structure in " + CASTLE_NAME);
    set_long("You are just inside of the ruins of a " +
        "fair-sized hall in the southern side of the " +
        "ruins of " + CASTLE_NAME + ". A thin layer of " +
        "dust covers the ancient floor, fallen from " +
        "decaying walls. Thick buttresses climb " +
        "the walls and arch across the high ceiling " +
        "giving it extra support. Through the gloom " +
        "you can see corridors in the north and east " +
        "walls leading off into darkness.\n\n");

    INSIDE;

    add_item(({"walls"}), "Every surface is " +
        "stone, and while the west and south walls " +
        "appear be showing signs of their age in " +
        "numerous cracks, missing blocks and generally " +
        "crumbly surfaces, the other surfaces seem to " +
        "be in fair condition.\n");
    add_item(({"south wall"}), "The southern wall has " +
        "several holes in it, high on the wall, which " +
        "you guess used to be high windows to allow " +
        "light into this hall.\n");
    add_item(({"west wall"}), "The west wall bears a " +
        "another hole, but lower and much larger than " +
        "any others, " +
        "now resembling more of a crude door than a " +
        "window, an opening large enough for you to " +
        "easily go through.\n");
    add_item(({"north wall", "east wall"}),
        "The wall is in fairly good shape, and " +
        "you can see through the darkness a narrow " +
        "corridor leading through it.\n");
    add_item(({"ceiling", "roof"}),
        "The ceiling has seen better days, but it " +
        "still manages to keep the brunt of the " +
        "weather out of this room, the buttresses " +
        "giving the ancient stone structure extra " +
        "strength\n");
    add_item(({"floor", "ground"}),
        "The floor is cold grey stone, covered with " +
        "a layer of dust and debris that has fallen " +
        "from the decaying walls and ceiling.\n");
    add_item(({"dust", "debris"}),
        "Scattered across the floor in a thin layer, " +
        "dust and debris of all ages have fallen " +
        "here together from the decaying walls and " +
        "ceiling.\n");
    add_item(({"buttresses"}),
        "Long, arching columns of sorts, the odd " +
        "design seems to be providing excellent " +
        "strength to the roof of the room.\n");

    add_exit(RUIN + "build1-build2", "north");
    add_exit(RUIN + "build1-cath", "east");
    add_exit(RUIN + "sw_wall_1", "west");
}

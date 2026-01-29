#include "defs.h"

inherit STDROOM;

void
create_corridor()
{
    set_short("a dark hallway in " + CASTLE_NAME);
    set_long("You are in a short, dark hallway somewhere in the ruins of " +
        CASTLE_NAME + ". The hallway is fairly plain, with the walls " +
        "arching upwards and meeting each other in a peak directly over " +
        "your head. Rust-dusted iron sconces are embedded within the " +
        "walls, their charges long since lost to the ravages of time. " +
        "Curiously enough, you note that aside from the effects of age, " +
        "there's no sign of things like animal droppings or even a cobweb " +
        "clinging to a wall.\n\n");

    add_item(({"ceiling", "roof", "peak"}),
        "The roof of the hallway arched to a point over your head, " +
        "with the walls curving smoothly up to the stone peak.\n");
    add_item(({"floor", "ground"}),
        "The floor of the hallway is made simply from stone blocks. " +
        "Once polished smooth, they are now littered with cracks, " +
        "chips, and thick dust.\n");
    add_item(({"cracks"}),
        "The floor and walls smooth, but sport countless cracks " +
        "all over the place.\n");
    add_item(({"chips"}),
        "All across the floor, countless stone chips lie where " +
        "they've fallen from larger cracks in the walls.\n");
    add_item(({"dust"}),
        "Thick dust, the refuse of the passing of time, covers most " +
        "things here like a burial shroud.\n");
    add_item(({"walls", "wall"}),
        "The plain, stone walls rise steadily, curving slightly " +
        "inwards at the top where they meet to form the peak in the " +
        "arched ceiling. Except for a handful of rusted sconces, " +
        "they are painfully barren.\n");
    add_item(({"sconce", "sconces"}),
        "The sconces are simple iron rings, anchored into the walls " +
        "presumably to serve as holders for torches. Now the torches " +
        "are gone, and they hold little more than rust.\n");

    INSIDE;
    DARK;
}

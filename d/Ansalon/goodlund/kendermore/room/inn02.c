#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit KENDERMORE_IN;

void
reset_kendermore_room()
{
    return;
}

create_kendermore_room()
{
    set_short("Above the Scorched Scorpion Inn");
    set_long("This room is lightly decorated after years of borrowing " + 
        "kender staying here. You're surprised that there is even the " + 
        "pillow on the bed left! A small twin bed is pushed against the " + 
        "wall by the window, and a wooden dresser stands beside the bed. " + 
        "The only other item in the room is a heavy colourful rug. If you " + 
        "have paid for a room, you can start here when you next decide to " + 
        "return to these realms.\n");
    add_item(({"bed", "twin bed"}), "It's covered in a bright blue " + 
        "comforter, and a brilliantly patterned blanket is neatly folded " + 
        "at the foot of the bed. Two fluffy pillows have been placed at " + 
        "the head. It looks very comfortable.\n");
    add_item("blanket", "It has bright reds, yellows and oranges woven " + 
        "into it. It looks very warm.\n");
    add_item("pillows", "They are very fluffy and covered in bright blue " + 
        "pillow cases.\n");
    add_item("comforter", "It's a beautiful bright blue.\n");
    add_item(({"dresser", "wooden dresser"}), "You can put your belongings " + 
        "here overnight if you dare, though they might disappear " + 
        "overnight.\n");
    add_item(({"rug", "heavy rug", "colourful rug", "heavy colourful rug"}),
        "It is skillfully woven, with white, blue, and green circles.\n");
    add_exit(KROOM + "inn01", "down", 0);
    reset_kendermore_room();
}
 

#include "defs.h"
#include <stdproperties.h>

inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the Captain's quarters.");
    set_em_long("Though the size of this room is significantly smaller " +
        "than the large communal barracks you just left behind, there " +
        "is only one bed in here. The rough, wooden walls are " +
        "decorated with assorted trophies and three iron wall lamps " +
        "which flood the windowless room with light. In one corner, " +
        "a huge bear stands at full height, in another, a large flag " +
        "hangs from a pole. Against the eastern wall, a bookcase stands " +
        "alongside a wooden desk.\n");

    add_item( ({"bed"}),
        "A goose down mattress lies on top of a wooden bed frame. The bed " +
        "looks so inviting that you almost feel like lying down for a quick " +
        "nap. At the foot of the bed is a long wooden footlocker.\n");

    add_item( ({"walls", "wooden walls", "rough walls", "rough wooden walls"}),
        "All four walls of the room are made from the same wood as the rest of " +
        "the building. Large logs have been placed horrizontally, one on top " +
        "of the other to form a good barrier from the weather. There are " +
        "many trophies on the walls, the heads of animals that were taken " +
        "during the hunt. There is a door in the north wall which leads back " +
        "to the main barracks.\n");
   
    add_item( ({"trophies", "trophy"}),
        "The heads of a wide variety of animals are mounted upon these walls. " +
        "All are well cared for and groomed to perfection and the face of each " +
        "animal has been manipulated to look fierce and threatening. Certainly " +
        "the champion who won all these prizes must be an expert hunter.\n");

    add_item( ({"lamp", "lamps", "iron lamps", "iron lamp", "wall lamp", 
                "wall lamps", "iron wall lamp", "iron wall lamps"}),
        "Iron wall lamps burn brightly on the eastern, western and southern " +
        "walls. Fueled by oil, they are capable of filling every inch of the " +
        "room with bright light.\n");

    add_item( ({"bear", "huge bear"}),
        "Claws extended and fangs exposed in an eternal snarl, this " +
        "bear is quite an impressive sight. Covered in shaggy, brown fur " +
        "and standing over 3 meters tall, the head of the great beast nearly " +
        "touches the ceiling.\n");

    add_item( ({"flag", "large flag", "pole"}),
        "A large gold and white flag hangs from the wooden pole. In the middle " +
        "of the flag is an intricately worked sigil.\n");

    add_item("sigil",
        "The sigil depicts a white, winged unicorn as it rears back upon its " +
        "hind legs. Underneath its hooves lies the broken corpse of a goblin.\n");

    add_item( ({"bookcase"}),
        "Assorted titles and scrolls fill the bookcase. Many of the books seem " +
        "to deal with strategy and diplomacy, and all are relatively old. The " +
        "bookcase itself is a rather simple design made from cherry.\n"); 

    add_item( ({"book", "books", "scroll", "scrolls"}),
        "Most of the books are old, the pages yellowed from age and " +
        "earmarked from use. There are a wide variety of scrolls in the bookcase, " +
        "their topics ranging from religeon to orders from the king in Telberin.\n");

    add_item( ({"desk", "wooden desk"}),
        "An old desk made of cherry sits along the eastern wall. Whomever uses " +
        "this desk must be a very organized individual because the surface " +
        "is perfectly clean. Some drawers are built into the desk on its right " +
        "side.\n");

    add_item( ({"drawer", "drawers"}),
        "You rummage through the drawers but find nothing other than assorted " +
        "writing implements, seals and paper.\n");

    add_prop(ROOM_I_LIGHT, 3);

    clone_object(OUTPOST_OBJ + "footlocker")->move(this_object());
    add_door_exit(OUTPOST_DOOR_OBJ, OUTPOST_DIR + "lbrcks", "north");
}

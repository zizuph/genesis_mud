/* end of West Hall in Bag End
 * -- Finwe, May 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <ss_types.h>

inherit BASE_SMIAL;

void create_smial()
{
    NO_STEEDS;
    FIXEUID;
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,5);

    set_short("A back entrance in a nice smial");
    set_long("This is the back entrance of the smial. It has been dug into the hill and is long and circular. Two long square beams run the length of the entrance and are supported by wooden posts at either end. The ceiling is supported by wooden ribs that are evenly spaced. A curved opening leads west to another room. Next to the opening is a long table, and across from the table sits a large wardrobe. A wide rug is laid in front of the door, and a large rug in front of the opening. A simple chandelier hangs from the ceiling.\n");

    add_floor("Some rugs are on the floor.");
    add_walls("");

    add_item(({"back entrance"}),
        "This is a long tunnel dug deep into the hill. It is comfortable " +
        "looking and has a openings leading deeper into the hill.\n");
    add_item(({"beams", "square beams", "square beam", "beam"}),
        "They are long and span the length of the tunnel. The beams " +
        "are made from wood and are held up by wooden posts at either " +
        "end. They support the ribs that hold up the ceiling. They are stained brown.\n");
    add_item(({"ribs", "wooden ribs", "rib", "wooden rib"}),
        "The wooden ribs are circular in shape and are evenly spaced " +
        "along the round ceiling. They hold up the round ceiling with " +
        "each end connecting to the long beams. They are stained brown.\n");
    add_item(({"north wall"}),
        "There is an opening that leads deeper into the smial.\n");
    add_item(({"south wall"}),
        "A door is set in the middle of the wall. On the right side  " +
        "of the door is a small round window. \n");
    add_item(({"east wall"}),
        "XXX\n");
    add_item(({"west wall"}),
        "XXX\n");
    add_item(({"right window"}),
        "It round and to the right of the door on the south wall.\n");
    add_item(({"tall table"}),
        "The table sits below the right window and made of wood. " +
        "Sitting on the table is a woven basket.\n");


    add_item(({"ceiling"}),
        "It is tall, for a hobbit, and circular shaped. Wooden ribs " +
        "are evenly spaced on the ceiling and hold it up. Two long beams " +
        "run the length of the ceiling.\n");
    add_item(({"posts", "wooden posts", "wooden post"}),
        "They are thick and hold up the long beams at either end of the " +
        "room. They are round and stained brown.\n");
    add_item(({"wide rug", "rug"}),
        "It is gray colored and sits before the back door. \n");

    add_item(({"chandelier"}),
        "It hangs from the ceiling on a short chain. Eight 'S' shaped " +
        "arms stretch out from an oval shaped ball in the center of " +
        "the chandelier. A tall candle burns on each arm, filling the " +
        "entrance with light.\n");
    add_item(({"candle", "candles", "tall candle", "tall candles"}),
        "They are tall and golden colored. They burn brightly and " +
        "fill the room with light.\n");
    add_item(({"books", "stacks of books", "piles of books"}),
        "They are all sizes and stacked on the table. Most look well " +
        "read and worn.\n");
    add_item(({"papers", "stacks of papers", "piles of papers"}),
        "They are stacked haphazardly on the table and look well read.\n");

    room_add_object(BE_OBJ + "whall03_door");

    add_exit("whall02", "north");

    reset_shire_room();
}

void reset_shire_room()
{
    ::reset_shire_room();
}

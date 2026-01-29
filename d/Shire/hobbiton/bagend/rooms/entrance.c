/* A passage in Bag End
 * -- Finwe, April 2020
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

    set_short("An entrance inside a nice smial");
    set_long("This is the entrance of the smial. It has been dug into the hill and is long and circular. Two long square beams run the length of the entrance and are supported by wooden posts at either end. The ceiling is supported by wooden ribs that are evenly spaced. A curved opening leads west to another room. Next to the opening is a long table, and across from the table sits a large wardrobe. A wide rug is laid in front of the door, and a large rug in front of the opening. A simple chandelier hangs from the ceiling.\n");

    add_floor("Some rugs are on the floor.");
    add_walls("");

    add_item(({"entrance"}),
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
        "The door is set in the middle of the wall. On either side " +
        "of the door are small round windows. Above the left window " +
        "hangs a bell. \n");
    add_item(({"east wall"}),
        "Against the east wall stands a large wardrobe.\n");
    add_item(({"west wall"}),
        "There is an opening that leds to another room. Next to the " +
        "opening is a long table.\n");
    add_item(({"left window"}),
        "It is round set to the left of the door. Above the window " +
        "is a bell. \n");
    add_item(({"right window"}),
        "It round and to the right of the door on the south wall. " +
        "Below the window is a tall table wth a basket sitting on it \n");
    add_item(({"tall table"}),
        "The table sits below the right window and made of wood. " +
        "Sitting on the table is a woven basket.\n");
    add_item(({"basket", "woven basket"}),
        "The basket is rectangular shaped and sits on the tall table. " +
        "It is made of fibers woven together. Inside the basket is " +
        "some mail.\n");
    add_item(({"fiber", "fibers"}),
        "They are thin strips of a plant that hazve been woven " +
        "together to make up the basket.\n");   
    add_item(({"mail"}),
        "They are letters sent to the hobbit who lives here.\n");
    add_cmd_item(({"letters", "letter", "mail"}), 
        ({"read", "examine", "exa", "get"}), 
        "You take the letters from the basket and flip through " +
        "them. They are addressed to a hobbit named 'F. Baggins'. You " +
        "put the mail back in the basket.\n");

    add_item(({"ceiling"}),
        "It is tall, for a hobbit, and circular shaped. Wooden ribs " +
        "are evenly spaced on the ceiling and hold it up. Two long beams " +
        "run the length of the ceiling.\n");
    add_item(({"posts", "wooden posts", "wooden post"}),
        "They are thick and hold up the long beams at either end of the " +
        "room. They are round and stained brown.\n");
    add_item(({"opening", "curved opening"}),
        "It's a round tunnel dug into the west wall and leads to another " +
        "room.\n");
    add_item(({"table", "long table"}),
        "It is long and narrow and sits against a wal. The table is " +
        "plain and stained brown. A vase with some flowers sits on the " +
        "table. It is surrounded by stacks of books and piles of papers. " +
        "Above the table hangs a plaque.\n");
    add_item(({"vase", "ceramic vase"}),
        "The vase is made of clay and glazed a faded blue. It is is " +
        "full of small white flowers.\n");
    add_item(({"white flowers", "flowers", "daisys", "daisy", "daisies"}),
        "They fill the vase and are freshly picked. Each flower has " +
        "a yellow center and is surrounded by many thin, white petals.\n");
    add_item(({"wide rug"}),
        "It is gray colored and sits in before the front door. Large " +
        "diamonds are woven into it with smaller diamonds around the " +
        "edges. \n");
    add_item(({"large rug"}),
        "It is blue colored and sits between the opening and the " +
        "wardrobe. It stretches from the front door to the rest of " +
        "the room. It is plush with white outlines of overlapping hexagons.\n");
    add_item(({"rugs", "rug"}),
        "There are two of them in the entrance. A wide rug in front " +
        "of the door and a large rug in front of the of the opening.\n");
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

    add_item(({"bell"}),
        "It hangs next to the door. A leather cord is attached to it.\n");
    add_item(({"leather cord", "bell pull", "bellpull"}),
        "It is a strip of leather connecting to the bell. It is pulled " +
        "by a visitor outside to annouce their arrival at the front " +
        "door.\n");
    add_cmd_item("bell", "ring", "You reach out and ring the bell " +
        "next to the door.\n");

    add_item("plaque", "It is small and hangs on the wall. There is " +
        "something written on it tht can be read.\n");
    add_cmd_item("plaque",({"read"}), "@@read_plaque@@");

    room_add_object(BE_OBJ + "ent_door");
    room_add_object(BE_OBJ + "ent_wardrobe");

    add_exit("road", "north");
    add_exit("parlor", "west");

    reset_shire_room();
}

void reset_shire_room()
{
    ::reset_shire_room();
}

string read_plaque()
{
    return "On the plaque you see:\n" +
"\n" +
"                     ______\n" +
"                    /*    *\\\n" +
"                   /        \\\n" +
"                  /          \\\n" +
"                 /            \\\n" +
"                /              \\\n" +
"               /                \\\n" +
"              /                  \\\n" +
"             /                    \\\n" +
"        +------------------------------+\n" +
"        |                              |\n" +
"        |     Where ever you wander    |\n" +
"        |     Where ever you roam      |\n" +
"        |          ~~~~ * ~~~~         |\n" +
"        |     Be happy and healthy     |\n" +
"        |     And glad to come home    |\n" +
"        |                              |\n" +
"        +------------------------------+\n" +
"\n\n";
}
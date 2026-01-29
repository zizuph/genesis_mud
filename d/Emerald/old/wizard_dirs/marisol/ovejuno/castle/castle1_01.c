/* Castle_room01-The Foyer.
 * Coded by Marisol (09/03/98)
 * Copyright (c) Marisol Ramos 1998
 */


#pragma strict_types
#include "defs.h"
#include "macros.h"
#define DOOR01 DOORS + "castle_in.c"
inherit CASTLE_OV;

object door01;

void 
create_castle_room()
{

    set_short("The Foyer");
    set_long("The foyer is a wide, high-ceiling, receiving room. This "+
        "room is also used as the ball room, where dancing and singing "+
        "is celebrated. This beautiful room contrast greatly with the "+
        "abandoned look of the outside portico. Gleaming white walls "+
        "are covered with expensive-looking paintings and tapestries. "+
        "High on the walls, stained-glass windows let in soft colored "+
        "light. The floor is also covered with exquisite rugs so thick "+
        "that you can't heard your footsteps. A huge mahoney door is "+
        "guarded by two stern-looking elves guards. A roaring fireplace "+
        "add light and warm to this room. Torches are sets high in the "+
        "walls that illuminate the whole room.\n");

    add_item("fireplace",
        "A roaring fire is burning inside the stone fireplace in one of "+
        "the walls. The mouth of the fireplace is huge! Big logs are "+
        "burning merrily giving warm to this huge room. The chimney is "+
        "also made from stone and mortar and rise high to the ceiling, "+
        "disappearing into the second floor.\n");

    add_item("rugs",
        "These rugs are so thick that you can't only hear your "+
        "footsteps, you can't either see your feet. They are of a "+
        "rich light blue, giving a cheery look to this room\n");

    add_item("floor",
        "The floor is all covered with exquisite rugs.\n");

    add_item(({"elves guards", "guards"}),
        "The guards are guarding the main entrance. They look stern "+
        "and professional.\n");

    add_item(({"windows", "stained-glass windows"}),
        "The tall stained-glass windows are set high in the walls. "+
        "They have colorful designs of mystical animals, like unicorns, "+
        "alicorns, sirens, griffins and other magical creatures. They "+
        "look so realistic, that you feel they are ready to step out "+
        "of the windows.\n");

    add_item(({"mystical animals", "animals"}),
        "There are five mystical animals represented in the stained- "+
        "glass windows. On the left wall, there is an unicorn and a "+
        "siren window. On the right wall, there is an alicorn and a "+
        "griffin window. On the top of the main entrace there is a "+
        "tall window with a beautiful human maiden.\n");

    add_item("unicorn",
        "A white handsome unicorn. This animal looks like a stallion "+
        "but it has a long, spiral-like mean-looking horn in its "+
        "forehead. The animal looks so realistic that it seems that "+
        "is going to jump any time from the window.\n");

    add_item("siren",
        "A stunning siren brush eternally her hair in this window. "+
        "Her tresses are emerald green. Her eyes are aquamarine. Her "+
        "bosom is impossible beautiful. Her tail shines with golden-red "+
        "scales. She looks like the image of perfection. Her "+
        "gazes is so alluring that you feel that she is alive.\n");

    add_item("alicorn",
        "An impossing red alicorn. This animal looks like a cross "+
        "between a unicorn and a pegasus. This one is scarlet in color, "+
        "has yellow-red wings and a wicked looking horn in its "+
        "forehead. Bright yellow flames shoot out from its notrils. "+
        "You have the uneasy feeling that this creature can escape any "+
        "time from its window.\n");

    add_item(({"beautiful human maiden", "human maiden", "maiden"}),
        "You wonder why a beautiful human maiden is portrayed in this "+
        "stained-glass window. Her image is even more beautiful than "+
        "the siren, if that is possible, although you don't know why "+
        "you feel that way. Her skin is like sweet cream. Her eyes are "+
        "dark and mysterious. Her hair is long, silky blue-black that "+
        "reaches almost to her feet. Her figure is too perfect to. "+
        "describe. There is something dark and forbidden about the "+
        "whole picture that make you feel uneasy though.\n");

    add_exit("castle1_02.c", "north");
    door01= clone_object(DOOR01);
    door01->move(TO);

    reset_room();
}

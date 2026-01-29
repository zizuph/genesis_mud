/*
 * File:          /d/Avenir/common/dark/submissions/a_vast_majestic_cave.c
 * Creator:       Lior
 * Date:          Sat Sep 27 02:24:26 2003
 * Note:          This room was auto-generated using
 *                the room creator module inherited by
 *                /d/Avenir/common/dark/mon/foreman#64698
 * Comments:      
 *                I am creating a beautiful cave! I don't know
 *                what will its future be. Maybe it will
 *                magically appear right here? It would be
 *                great.
 */
#include "defs.h"
inherit "/std/room";

void
create_room ()
{
    set_short("a vast majestic cave");
    set_long("This cave, in contrast with the outside tunnels, "
        + "displays a great variety of colours and shapes. "
        + "Wrinkled stalagmites of all possible hues protrude "
        + "from the stone floor, and sinuous stalactites hang "
        + "from the ceiling. Columns and walls of sparkling "
        + "stone form a majestic maze, beckoning you to "
        + "explore its mysterious depths.\n");

    add_item(({"stalagmites"}),
        "Stalagmites are thick pillars of stone, protruding "
        + "from the floor. They are coloured like the "
        + "stalactites above, but in a slightly darker tint.\n");
    add_item(({"stalactites"}),
        "Myriads of glowing stlactites hang from every spot "
        + "of the ceiling. Occasionally a drop of water falls "
        + "off onto the stalagmites below.\n");
    add_item(({"floor"}),
        "The floor is uneven and hard to walk on, as you "
        + "have to make your way through the stalagmites.\n");
    add_item(({"walls"}),
        "Massive walls of stone rise high to the ceiling, "
        + "where stalagmites merged together.\n");
    add_item(({"columns"}),
        "Towering columns of stone have various colours and "
        + "shapes. They look as if they are supporting the "
        + "cave ceiling.\n");
    add_item(({"ceiling"}),
        "The ceiling is dotted with myriads of stalactites. "
        + "It looks like a many-coloured upside-down forest.\n");
    add_item(({"shapes"}),
        "Looking at the shapes of the stalagmites, you "
        + "suddenly notice that they are not stalagmites, but "
        + "something else! You see an army of dwarven "
        + "warriors, a solitary howling wolf, a wine barrel, "
        + "a slender girl dancing upon a ball, a bearded "
        + "wizard deep in thought, a falling tower and many "
        + "other objects.\n");
    add_item(({"warriors"}),
        "A group of hooded dwarven warriors to the west is "
        + "of a dark red colour. They are marching towards "
        + "the southern part of the cave... Suddenly you "
        + "realize that they are just figures of stone, inert "
        + "as ever.\n");
    add_item(({"wolf"}),
        "An ochre-coloured wolf sits on top of a hill to "
        + "your north. You hear an unearthly howl which "
        + "chills you to the bone. Suddenly you hear nothing, "
        + "and see only a yellowish rock.\n");
    add_item(({"barrel"}),
        "A stout barrel sits in the southwestern corner. A "
        + "golden trickle is pouring out, smelling very "
        + "familiar and inviting. As you move to reach the "
        + "wine pool, the stalagmite shifts and destroys the "
        + "impression.\n");
    add_item(({"girl ball"}),
        "In the eastern end, a dancer of unspeakable beauty "
        + "displays an athletic show on a ball of sparkling "
        + "silver. Suddenly, a drop falls on her face, and "
        + "the magic is broken.\n");
    add_item(({"wizard"}),
        "A great wizard in dark-blue robes is sculptured "
        + "deep in thought to your southeast. You are "
        + "startled as he suddenly looks at you, but it is "
        + "just a play of light and shade.\n");
    add_item(({"tower"}),
        "A magnificent many-storeyed tower is emerald-green "
        + "in colour. You can almost see tiny people in its "
        + "windows... They speed towards you... The tower is "
        + "falling straight on you! CRASH!! - A small "
        + "stalactite falls off the ceiling. You find the "
        + "tower in its place, unmoved.\n");
    add_cmd_item(({"stalagmite stalagmites"}),
        ({"break take crush hit"}),
        "Although looking soft and gummy, the stalagmites "
        + "are rock-hard and ignore your attempt.\n");
    add_cmd_item(({"stalactite stalactites"}),
        ({"break take crush hit"}),
        "The stalactites hang just a bit above your reach, "
        + "as if teasing you.\n");


}

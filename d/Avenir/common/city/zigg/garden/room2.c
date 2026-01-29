// Ziggurat Garden (room2.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_GARDEN;

public void
zig_room(void)
{
    set_long("The white flagstone path twists and turns here, weaving "+
      "around ashwood poles erected here amongst a carpet of colorful "+
      "wildflowers. Long flowered garlands hang down from baskets "+
      "suspended overhead from the poles. Beyond the hanging vines to "+
      "the west and south a breathtaking view of the City spreads out "+
      "below while the upper levels of the Ziggurat rises to the "+
      "northeast.\n");

    add_exit("room3", "north", "@@exit_string");
    add_exit("room1", "east", "@@exit_string");
}

static void
garden_items(void)
{
    ::garden_items();

    add_ground("The ground of the terrace is made of flat, rich soil and "+
      "covered with a carpet of wildflowers.");

    add_views("From this side of the Ziggurat you can see the High Lord "+
      "Commisioner's enclave to the south, opulent noble houses circle "+
      " the High Lord's palace on the central hill. Farther off to the "+
      "west, you can just see part of the High Lord Inquisitor's enclave "+
      "and its similar layout.", "enclaves, giving them");

    add_rock("a painted half-green, half-blue circle divided by a white "+
      "lightning bolt", ", the symbol of Tabris-Zeffar");

    add_item(({"basket","baskets","vines","vine","garlands","garland"}),
      "Baskets woven out of strips of wood hang overhead, suspended "+
      "from special ebony poles. They hold an abundance of flowering "+
      "plants, including colorful sweetpeas and morning glories, "+
      "their pretty garlands spilling over the sides. Some baskets "+
      "also hold white and green spider plants with their white "+
      "glistening flowers.\n");

    add_item(({"pole","poles","ashwood pole","ashwood poles"}),
      "Many tall ashwood poles form a makeshift grove here. Each pole "+
      "supports three arms from which hanging plants in wooden baskets "+
      "are suspended.\n");

    add_item(({ "spider plant", "spider plants" }),
      "Spider plants make excellent hanging baskets. The long, grassy "+
      "leaves are available in green or striped yellow or white. "+
      "Long wiry stems appear on healthy plants with many small white "+
      "flowers and miniature plantlets. If these new plantlets touch "+
      "soil, they will root. The plantlets can be either detached to "+
      "produce new plants, or left on to create a very full basket.\n");

    remove_item("grass");
}

static void
garden_flowers(void)
{
    add_flower("morning glory");
    add_flower("moonflower");
    add_flower("spider plant");
    add_flower("sweetpea");
    add_flower("wildflower");

    ::garden_flowers();
}

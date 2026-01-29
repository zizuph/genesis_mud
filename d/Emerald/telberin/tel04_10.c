#include "defs.h";

inherit TELBERIN_WAVENUE;

void
create_west_avenue()
{
    set_short("Western gate of Telberin");
    set_em_long(
        "Just inside the western gate of Telberin, at the great West Avenue " +
        "and Ri Circle.  The wide avenue leads east through two of " +
        "Telberin's famous gardens; their fragrances reaching you even from " +
        "here.  The line of the roadway draws your eye down its length into " +
        "the grand Royal Circle and up to the gates of the Royal Palace. " +
        "Its magnificent, perfectly symmetrical form dominates the skyline. " +
        "The tall, pure-white, stone spires rise toward the sky, gleaming " +
        "brilliantly in the light.\n");

    add_item(({"gate", "west gate", "western gate"}),
        "You examine this magnificent west gate closer. It is a very tall gate "+
        "made from the strongest of iron, which one must pass through to enter "+
        "or leave Telberin.\n");

    add_item(({"gardens", "garden", "famous gardens"}),
        "The wide avenue leads east through two of Telberin's famous "+
        "gardens. Their fragrances are subtle and yet soft as they reach you "+
        "even here.\n");

    add_item(({"tower", "towers"}),
        "The two majestic towers rest on each side of the royal gate, "+
        "which spiral upward to form a perfect point.\n");

    add_item(({"royal gate"}),
        "You will need to be closer to the gate to examine it.\n");

    add_item(({"ri circle"}),
        "The Ri Circle is the main road that runs through all four quarters of "+
        "Telberin. It is made from cobblestones and you can reach the many shops "+
        "that are open.\n");

    add_item(({"circle", "royal circle"}),
        "Royal Circle is the center of the city where the Palace, "+
        "Keepers of Telberin, Temple, and other government buildings are. "+
        "The road that surrounds the Royal Circle bares the same name.\n");

    add_item(({"circle"}),
        "Did you want to examine the Royal Circle or the Ri Circle?\n");

    add_item(({"fragrance", "fragrances"}),
        "The sweet fragrances here are a mixture of roses and honeysuckle.\n");

    add_item(({"skyline"}),
        "You look at the skyline and its filled with the majestic and "+
        "flawless Royal Palace.\n");

    add_wflower_garden("A wildflower garden borders the West Avenue to the " +
        "north.");
    add_rose_garden("A rose garden borders the West Avenue to the south.");

    add_exit("tel03_10", "west");
    add_exit("tel05_10", "east");
    add_exit("tel04_11", "north");
    add_exit("tel04_09", "south");
}

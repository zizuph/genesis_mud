// Ziggurat Clips Shop (ZIG_RL3 + "clips.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Ziggurat shop where players can buy clips.
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_ROOM;

private static object keeper;

private void
reset_npc(object npc)
{
    keeper = npc;
}

public void
zig_room(void)
{
    set_short("A colorful shop");
    set_long("This store is a wash of rich colors drawn together by the "+
      "pale gold floor and accents. Toward the back, a red sandstone "+
      "table serves as both a worktable and a sales counter for the "+
      "busy shop owner who is usually found sorting through the clutter "+
      "on the table, fashioning beads to be stored in the many tiny "+
      "drawers in the chest at the back of the shop. The shop has a "+
      "frenzied air about it that is almost dizzying and fueled not only "+
      "by the clutter but by the rainbow walls and wild mosaic above.\n" );

    add_item(({"walls","stone walls","wall","stone wall"}),
      "The walls are covered with hanging panels of silk in alternating, "+
      "rainbow colors. \n");
    add_item(({"panel","panels","green panels","red panels","blue panels",
      "violet panels", "orange panels", "yellow panels","indigo panels"}),
      "The panels hang from the mosaic ceiling down to the tile floor. "+
      "They are made of light silk and dyed in rich, rainbow hues.\n");
    add_item(({"chest","chest of drawers","drawers",}),
      "It stands almost as tall as an elf and is fashioned of highly polished "+
      "rosewood. Hundreds of tiny drawers cover the front, storing the "+
      "clips for sale here.\n ");
    add_item(({"table","counter","clutter"}),
      "A heavy red sandstone worktable doubles as the sales counter "+
      "of this shop. The table is covered with a clutter of vases filled "+
      "with fresh flowers, piles of bones and colored beads and feathers "+
      "among other things, including scores of tiny gift boxes.\n ");
    add_item(({"light","lights","lanterns","poles","light-poles"}),
      "Several gold poles soar upwards toward the ceiling where they "+
      "support hooks which in turn hold golden lanterns. The lanterns "+
      "are too high to see what lights them, but judging from the soft, "+
      "mostly steady glow, they probably hold some of the small source-"+
      "crystals used to light much of the Ziggurat.\n");
    add_item(({"floor","ground","tile","tiles","gold tile","gold tiles"}),
      "The floor is tiled with square tiles composed of gold, pressed and "+
      "sandwiched between two layers of the highest quality lead "+
      "crystal glass.\n");
    add_item(({"ceiling", "ceiling tiles",}),
      "The ceiling is covered by an elaborate mosaic. Scrolling vines "+
      "made of gold with glass leaves and flowers dominate the mosaic. "+
      "All sorts of seemingly random objects and animals peek out "+
      "between the vines. You seem to notice something new "+
      "each time you look at them.\n");
    add_item(({"objects", "animals", "mosaic"}), "@@see_mosaic");

    add_exit("room7", "north", 0);

    add_npc(ZIG_MON + "nisa", 1, reset_npc);
}

string
see_mosaic()
{
    string cover = one_of_list(({"some leaves", "a large purple flower",
        "a patch of blue blossoms", "a thick clump of leaves",
        "a cluster of vines","an enormous emerald leaf",}));

    string item = one_of_list(({"a tiny bird","a large bone","a green lizard",
        "a treasure chest","a red shoe","a scary eyeball","a graceful deer",
        "a colorful clam","a rocking chair","a clay jug","a statue arm",
        "an aglyna talon","a walking fish","a shimmering fairy","a tiny waif",
        "a silver chalice","an ivory brush","a fluffy black kitten",
        "a silvery wolf","a shiny ring","a crystal goblet","a golden trident",
        "a noble elf","a grumpy-looking dwarf","a coiled snake","a thigh bone",
        "a wooden sign which reads: ~Tangles~","a mithril gauntlet",
        "a satin slipper", "a pair of bloomers","a blue-speckled frog",
        "a painting of "+ cover,"a tiny orange newt","a sparkling diamond",
        "a bamboo fishing pole","a porcelain doll","a scarlet rose",
        "a yellow and orange striped worm", }));

    write("You look up to carefully examine the mosaic:\n\n"+
        "Gold vines connect big emerald leaves and blue and purple flowers "+
        "made out of pieces of glass tiles. The vines are thick and sprawl "+
        "across the entire ceiling. Following the winding lines of one of "+
        "the vines, you notice "+ item +" peeking out from behind "+ cover +
        ".\n");

    say(QCTNAME(TP) +" looks up to carefully examine the ceiling mosaic.\n");

    return "";
}

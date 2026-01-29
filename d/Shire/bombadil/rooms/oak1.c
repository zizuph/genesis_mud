/*
 * Middle of the Oak Tree at Tom Bombadill's house.
 * Originally coded by Dondon in 1994 for the original barrow downs.
 * Updated for the new area.
 * Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h" 
#include "../local.h"

inherit CLEAR_BASE;

void create_path_room()
{
    set_areadesc("large branch of a");
    set_area("mighty oak next to");
    set_areaname("the merry cottage");
    set_land("the clearing");
    set_areatype(0);
   
    set_extraline("The branches are very large and reach upwards. " +
        "Below, you can barely make out the merry cottage through " +
        "the walls of green leaves. The tree still goes up a ways.");
    add_item("tree",
        "This is an ancient, oak tree. It is the only tree growing " +
        "in the clearing and has long, thick branches. Green leaves " +
        "cover the branches and higher up in the branches, birds " +
        "nest in the tree.\n");
    add_item(({"nests", "bird nests",}),
        "Many bird nests are higher up in the tree. Some are new " +
        "with birds in them and others are borken and falling apart. " +
        "The nests are small, and made of twigs and feathers.\n");
    add_item(({"old bird nests", "old nests"}),
	    "The older nests look abandoned and broken, piles of all " +
        "kinds of small feather and broken twigs.\n");
    add_item(({"new bird nests", "new nests"}),
        "The new nests sit on the branches of the trees. They are " +
        "made of small twigs and feathers, and bowl shaped. Some " +
        "have babies in them, while others have larger birds sitting " +
        "in them, watching your every move.\n");
    add_item(({"birds"}),
        "You see a variety of birds in the trees. They are " +
        "different colors and sizes, and fly  about the tree, " +
        "primarily to nests built in the branches. Some birds are " +
        "brightly colored while others are dull, dark colors. They " +
        "all seem friendly, yet wary of your presence. Their singing " +
        "fills the clearing with cheerful music.\n");
    add_item(({"bird feathers", "feathers"}),
        "The bird feathers are soft and yet colorful in their own " +
        "way. Those used in the nests are downy looking, soft " +
        "enough to hold baby birds.\n");
    add_item(({"twigs", "broken twigs"}),
        "The twigs are all sizes and shapes. They were gathered " +
        "from trees in the forest and bound together to make nests " +
        "by the birds. Some of the twigs are broken and part of old " +
        "nests while others look fresh and new, being part of the " +
        "newer nests.\n");
    add_item(({"branches", "branch", "tree branches"}),
        "The tree branches are thinner up here, but are of " +
        "considerable size. They spread out and up and are covered " +
        "with many leaves. Hanging from some of the branches are " +
        "small acorns, ready to fall.\n");
    add_item(({"chestnuts", "acorns"}),
        "The acorns are a dull brownish-red color. They are round" +
        "with a sharp point on the end and a flat, scaly top. The " +
        "acorns hang from the trees in small clusters, ready to " +
        "fall. \n");
    add_item(({"leaves"}),
        "The oak leaves are a deep green color. They are long with " +
        "several lobes extending from each side of the leaf.\n");
    add_item(({"lobe", "lobes"}),
        "These are the extentions of the leaves, similar to " +
        "fingers or claws.\b");
    add_item(({"cottage", "merry cottage", "house", "merry house"}),
	  "The cottage is beneath you, at the base of the tree. Below, " +
      "you see the rooftop and not much more as the leaves block " +
      "your view.\n");

    remove_item(({"oak tree", "oak", "mighty oak", "mighty oak tree"}));

    add_exit(ROOMS_DIR + "oaktop", "up");
    add_exit(ROOMS_DIR + "path12", "down");
}

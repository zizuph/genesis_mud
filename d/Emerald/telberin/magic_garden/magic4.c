/* Emerald/Telberin/
 * Magic Garden room
 * Created by Damaris
 * Updated 05/Y2K
 */

#include "../defs.h"

inherit MAGIC_ROOM;

void
create_magic_garden()
{
	/* To set the long desc. in an Emerald room. */
    set_em_long("You have found a secluded section of the garden. "+
       "You feel as if you have entered a sanctuary because it is "+
       "so peaceful. The trees are tall and their branches reach out to "+
       "each other above your head. There are many vines with soft "+
       "pink blossoms. The air is filled with soft fragrances from the "+
       "many flowers that surround you.\n");

    add_item(({"trees", "tree"}),
       "You look around at all the tall trees that fill this section of the "+
       "garden. You look above you and are amazed at the intricate "+
       "patterns the branches make as they weave in and out of each "+
       "other. The sight is remarkable and very serene.\n");

    add_item(({"flowers", "flower"}),
       "You cannot help but look closer at all the lovely flowers. You "+
       "see splashes of pink and lavender mixed with red and yellow "+
       "all around you. The different colors are spread out in such "+
       "a pleasing way you feel yourself becoming peaceful and quiet. "+
       "The sweet fragrances have a calming effect on you making you "+
       "take an internal reflection.\n");

    add_item(({"bushes"}),
       "You look closer at the bushes. They are tall and form a "+
       "perimeter with the trees in this secluded area. The leaves are "+
       "quite large and dark green with a slippery texture. There are "+
       "white blossoms just beginning to bloom all over the bushes.\n");

    add_item(({"vines", "vine"}),
       "You look closer at the vines that grow in this section. They are "+
       "everywhere you turn. There are a few climbing up the trees "+
       "and even intertwined with the tree branches that stretch above "+
       "your head. There are scattered pink blossoms on the vines, "+
       "which makes them appear soft and delicate.\n");

    add_item(({"blossoms", "pink blossoms"}),
       "The pink blossoms are soft with a delicate sweet scent.\n");

    /* To add exits to the room. */

    add_exit("magic5", "north");

}

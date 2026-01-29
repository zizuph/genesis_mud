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
    set_em_long("You feel your senses come alive as you enter this "+
       "section of the garden. You can see large trees looming over a "+
       "long winding creek and many different flowers. The grass is "+
       "different here than the rest of the garden and you notice a "+
       "different fragrance here also.\n");

    /* To add items to be examined. */

    add_item(({"trees", "tree"}),
       "You look closer at the trees and realize they are cottonwood "+
       "trees.\n");

    add_item(({"cottonwood", "cottonwood trees", "cottonwood tree"}),
       "You look closer at the cottonwood trees that are in this "+
       "section. They are tall and follow along the creek in a "+
       "decorative pattern, which draws your eyes to them. The "+
       "light green leaves are interesting to look at with the bits of "+
       "cotton bursting from tiny buds along the branches. These trees "+
       "are large and are known for cotton harvesting on special "+
       "occasions.\n");

    add_item(({"flowers", "flower"}),
       "There are so many different flowers here that you cannot "+
       "concentrate on any one species. However you are able to "+
       "appreciate their mixture of colors and beauty which makes "+
       "this area more inviting.\n");

    add_item(({"bush", "bushes"}),
       "You look closer at the bushes and you take delight in their "+
       "presentation. They are scattered throughout this area with "+
       "no real pattern or design. The leaves range from small to large "+
       "in size and dark green to red in color with white blossoms, "+
       "which give off a subtle fragrance.\n");

    add_item(({"creek", "water"}),
       "You look closer at the creek. It flows in a silent manner with "+
       "an occasional burst of water that tumbles down the rocks. "+
       "The clearness of the water is exquisite to look upon.\n");

    add_item(({"grass"}),
       "The grass here is different than the rest of the garden. It has "+
       "a sparkling emerald appearance and grows thickly, which is "+
       "unusual near a creek. You can see very tall blades of the "+
       "grass surround the trunks of the trees as if protecting them.\n");

    /* To add exits to the room. */

    add_exit("magic2", "east");

}

    /* This is for smells in the room. */

public void
hook_smelled(string str)
{
    if (!strlen(str))
    {
        write("Exotic scents fill your senses.\n");
	return;
    }

    if (str == "flowers")
    {
        write("Their sweet exotic scent caresses you softly.\n");
	return;
    }

    if (str == "grass")
    {
        write("A wonderfully exotic scent fills your senses.\n");
	return;
    }
}

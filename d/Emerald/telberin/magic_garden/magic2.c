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
    set_em_long("In this section of the garden you can see even more "+
       "beautiful trees with their branches hanging low. There is a grassy "+
       "path and with different types of flowers on both sides of the "+
       "path. The air feels light here and is full of fragrances. As you "+
       "survey this area you get a sense that things here are other than they seem.\n");

    add_item(({"trees", "tree"}),
       "You look around at all the tall trees that fill this section of the "+
       "garden and discover there are a mixture of weeping willows and "+
       "date trees.\n");

    add_item(({"branches", "branch"}),
       "You can see many long flimsy branches cascading beautifully to "+
       "the ground from the willow trees.\n");

    add_item(({"weeping willow", "willow", "willows"}),
       "You look closer at the weeping willows. They are quite attractive "+
       "with their long flimsy branches cascading to the ground. The "+
       "rustle of their thin, light green leaves in the breeze is like music "+
       "to your ears, calling you to come find refuge under them.\n");

    add_item(({"willow tree", "willow trees"}),
       "You look closer at the weeping willows. They are very attractive "+
       "with their long flimsy branches cascading to the ground. The "+
       "rustle of their thin, light green leaves in the breeze is like music "+
       "to your ears, calling you to come find refuge under them.\n");

    add_item(({"date tree", "date trees"}),
       "You are amazed to find date trees in this garden. Date trees are "+
       "normally found in hot dry climates and it is far from hot here. "+
       "The silhouette of the date trees with the willows is breath taking "+
       "and "+
       "inviting.\n");

    add_item(({"date", "dates"}),
       "You can see dates hanging in the date trees and a few scattered "+
       "on the ground under the trees.\n");

    add_item(({"grass", "grassy path", "path"}),
       "You look closer at the grassy path and discover it leads you "+
       "throughout the garden. The grass is quite soft and pliable yet you "+
       "notice as you walk your imprints disappear instantly.\n");

    add_item(({"flower", "flowers", "blossoms"}),
       "There are so many flowers here to choose from. You can see "+
       "silver flowers with red tips dangling from bright green bushes, "+
       "which are next to dark green plants with long bladed flowers. "+
       "You also see small purple blossoms among patches of sweet "+
       "clover.\n");

    add_item(({"silver flowers", "green bushes", "bushes"}),
       "You look closer at the bright green bushes with the silver "+
       "flowers. They are quite beautiful flowers with pointed red "+
       "tips. They have an incredible musk scent that leaves you "+
       "yearning for more.\n");

    add_item(({"dark plants", "long flowers", "bladed flowers", "green plants"}),
       "You look closer at the dark green plants with the long bladed "+
       "flowers. The blades a long like grass but are firm and with "+
       "blossoms. The blossoms range from red to gold in color and "+
       "the petals are small but cluster together in large bunches. "+
       "The fragrance they produce is rather light and is similar to "+
       "roses.\n");

    add_item(({"purple blossoms", "purple flowers", "blossoms", "blossom"}),
       "You look closer at the soft purple blossoms. These exquisite "+
       "blossoms cover the ground and are intermingled with sweet "+
       "clover. You can only catch a glimpse of their sweet fragrance "+
       "because the clovers scent is overshadowing it.\n");

    add_item(({"sweet clover", "clover", "clovers"}),
       "You look closer at the clover. The clover is a refreshing sight of "+
       "small soft green leaves. It looks like a blanket covering the "+
       "ground with the purple blossoms mingled to give it an inspiring "+
       "appearance.\n");

    /* To add exits to the room. */

    add_exit("magic6", "west");
    add_exit("magic1", "northwest");
    add_exit("magic3", "southwest");
}

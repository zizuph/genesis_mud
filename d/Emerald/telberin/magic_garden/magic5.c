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
    set_em_long("You find yourself in a most beautiful area of this "+
       "garden. You are among the sweetest of flowers and bushes "+
       "with lush and sparkling trees all around you. The air is filled "+
       "with mystery and magic. You catch a glimpse of a statue nestled in "+
       "between the trees which resembles a memorial.\n");

    /* To add items to be examined. */
    add_item(({"bushes"}),
       "You look closer at the bushes and find they are enjoyable "+
       "to look at. They have many different colors of green embedded "+
       "in their leaves. They grow tall and thickly, giving an appearance "+
       "of a solid hedge.\n");

    add_item(({"flowers", "flower"}),
       "You cast your eyes around you and examine the captivating "+
       "flowers. There are so many different colors, shapes and sizes, "+
       "all pooled together bringing forth such lustrous bouquets to "+
       "tantalize your senses.\n");

    add_item(({"sparkling trees", "trees"}),
       "You look in wonder at the sparkling trees that surround you in "+
       "this section. The light envelops the trees in such a way, that "+
       "they sparkle with silver and crystal light from their leaves. They "+
       "are not too tall but are very full and resemble evergreen trees "+
       "in early winter mornings with snow and frost covering them. "+
       "It is relaxing to watch the squirrels scurry up into the trees "+
       "and birds resting on branches singing sweetly.\n");

    add_item(({"statue", "memorial", "warrior", "elven warrior"}),
       "You look closer at the statue that is almost hidden as it is nestled "+
       "in between two of the sparkling trees. It is quite clearly an image "+
       "of a noble elven warrior, gallantly standing with a sword in one "+
       "hand and a scroll in the other. There is no writing or symbols to "+
       "explain this apparent memorial.\n");

    add_item(({"sword", "statue sword"}),
       "You look closer at the sword in the statue and see it is unlike any "+
       "sword you have seen before. It is double bladed and the size and "+
       "dimensions are somewhat unique. You can tell there are runes "+
       "on the sword by this sculpture's representation, however they "+
       "are unreadable on the statue. You also notice the sword is "+
       "stretched outwards as if he is pointing south.\n");

    add_item(({"scroll", "statue scroll"}),
       "You look closer at the scroll in the statue and realize you are "+
       "unable to make out any symbol or writing.\n");

    add_item(({"runes"}),
       "You look closer at the runes on the sword in the statue, however "+
       "you are unable to read them.\n");

    /* To add exits to the room. */

    add_exit("magic4", "south");
    add_exit("magic3", "southeast");
    add_exit("magic1", "northeast");

}

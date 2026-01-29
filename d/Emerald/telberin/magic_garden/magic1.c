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
    set_em_long("You are in a most mysterious garden. A dazzling "+
       "magical essence is flowing here. The trees sparkle in the light "+
       "and the bushes and flowers are an incredible sight to behold. "+
       "Most things here have an enchanted look about them, and you get"
     + " the feeling you may need a closer look at things to determine"
     + " what you are actually seeing. Through the silver gate, one can"
     + " return to the Royal Circle.\n");

    /* To add items to be examined. */

    add_item(({"gate", "the gate"}),
       "You take a closer look at the silver gate. It is a spendid "+
       "silver with etched designs of dark green and dark red "+
       "which give the illusion of vines with red roses covering "+
       "it.\n");

    add_item(({"trees", "tree"}),
       "You look around at all the tall trees that fill this section "+
       "of the garden and discover there are a mixture of elm and oak.\n");

    add_item(({"oak", "oak tree"}),
       "You look closer at the oak trees and you are astonished to "+
       "realize it isn't oak at all. You aren't sure if you've ever seen a tree like " +
       "this one before. It stands tall and proud just like an oak "+
       "but you notice the leaves sparkle and twinkle in the light "+
       "from gold to silver.\n");

    add_item(({"elm", "elm tree", "bark"}),
       "You take a closer look at an elm tree only to discover that it isn't an elm at all. You " +
       "can determine this because you can see blue sap dripping from "+
       "a mark in the bark.\n");

    add_item(({"blue sap", "sap"}),
       "You study the blue sap for a moment. It is a thick syrup with a "+
       "sweet smell, which reminds you of blueberry syrup.\n");

    add_item(({"mark"}),
       "You study the mark carefully and recognize it is a small initial "+
       "carved in the bark.\n");

    add_item(({"initial", "initial carved"}),
       "You inspect the carved initial closer running your fingers along "+
       "the surface brushing away bits of stray bark. You can clearly "+
       "make out the initial to be T.\n");

    add_item(({"bushes", "bush", "leaves"}),
       "You look at the bushes that surround this section of the "+
       "garden. The leaves are an assortment of colors that you've "+
       "never seen combined before. You see pale yellow, dark "+
       "green, light red all mixed together in a single bush. They "+
       "are tall and grow thickly together leaving a most "+
       "magical impression.\n");

    add_item(({"flowers", "flower", "blossoms", "blossom"}),
       "You look at all the beautiful flowers that are scattered in an "+
       "intricate pattern of mystery and magic. You see Honeysuckle "+
       "glisten with fresh dew. You watch the dew evaporate and "+
       "the honeysuckle changes before your eyes and become "+
       "soft pink lilacs. This truly is a garden of magic.\n");

    add_item(({"honeysuckle"}),
       "You look closer at the honeysuckle. They glisten quite beautifully "+
       "with the fresh dew.\n");

    add_item(({"fresh dew", "dew"}),
       "You look closer at the fresh dew that covers the soft "+
       "honeysuckle and watch it magically evaporate before your "+
       "eyes.\n");

    add_item(({"lilac", "lilacs"}),
       "You look closer at the lilacs, the petals so soft and pink which "+
       "is so very unusual. But that is to be expected in a magical "+
       "garden.\n");

    /* To add exits to the room. */

    add_door_exit(TELBERIN_MAGIC_GARDEN_DIR + "garden_gate",
                  "/d/Emerald/telberin/royal_circle02",
                  "west", 0, 0, 1);
    add_exit("magic2", "southeast");
    add_exit("magic5", "southwest");
}

    /* This is for smells in the room. */
public void
hook_smelled(string str)
{
    if (!strlen(str))
    {
        write("The sweet smell of lilacs and honeysuckle suround you.\n");
	return;
    }

    if (str == "honeysuckle")
    {
        write("An intoxicating sweet scent envelopes you.\n");
	return;
    }

    if (str == "lilacs")
    {
        write("A soft lingering scent caresses your senses.\n");
	return;
    }

    if (str == "grass")
    {
        write("A soft sweet scent caresses your senses.\n");
	return;
    }
}


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
    set_em_long( "You are surrounded by the intoxicating scent of "+
       "pine. You can see pinecones scattered under the different "+
       "species of trees and along the path. The mixture of different "+
       "sizes, shapes, and colors of pine trees is phenomenal and quite "+
        "pleasing to your senses. There is definitely something beguiling"
      + " about this place.\n");

    /* To add items to be examined. */

    add_item(({"trees", "tree", "pine trees"}),
       "You scan all the pine trees in this section and find red flame "+
       "pine, black forest pine and blue moon pine. It is extraordinary "+
       "to have this variety growing together in the same place.\n");

    add_item(({"red flame", "flame pine", "red pine"}),
       "Red flame pine is a mystical pine tree, known only to exist in "+
       "Emerald. You stare transfixed at finally seeing one up close. "+
       "This tree is considered holy and very rare by the elven race. "+
       "You stare in awe at the burnt red colored pine needles. The "+
       "dark brown pinecones can be quite painful if handled incorrectly "+
       "because of the sharp red spikes on their tips.\n");

    add_item(({"pine", "pines"}),
       "Did you wish to look at pine trees or pinecones?\n");

    add_item(({"black forest", "black pine", "forest pine"}),
       "You stare intently at the black forest pines. They are tall and "+
       "slender with dark green needles that cluster in small diamond "+
       "shapes on very dark, almost black branches. The pine cones "+
       "range from dark brown to black in color, but has a soft yellow "+
       "center, which has been known to heal wounds if used "+
       "correctly.\n");

    add_item(({"blue moon", "blue pine", "moon pine"}),
       "The blue moon pines are so perfect in their dimensions. They "+
       "stand tall and regal with full branches bursting forth. The pine "+
       "needles cluster together in crescent moon shapes along the "+
       "branches. The trees give off a bluish aura and produce a most "+
       "charming scent.\n");

    add_item(({"pinecones", "pinecone"}),
       "You can see a variety of pinecones scattered all over the ground "+
       "and in the trees.\n");

    add_item(({"path"}),
       "You study the path before you. You can see it leads you "+
       "throughout the garden. The grass is quite soft and pliable yet you "+
       "notice your imprints as you walk disappear instantly.\n");

    add_item(({"grass", "ground"}),
       "The grass is sweet smelling and soft to the touch, covering "+
       "the ground in a delightful blanket.\n");

    /* To add exits to the room. */
    add_exit("magic2", "northeast");
    add_exit("magic5", "northwest");
}

    /* This is for smells in the room. */
public void
hook_smelled(string str)
{
    if (!strlen(str))
    {
        write("The sweetness of pines surrounds you and fills your senses.\n");
	return;
    }

    if (str == "trees")
    {
        write("The sweetness of pines fill your senses.\n");
	return;
    }

    if (str == "tree")
    {
        write("The sweetness of pines fill your senses.\n");
	return;
    }

    if (str == "pine")
    {
        write("The sweetness of pines fill your senses.\n");
	return;
    }

    if (str == "pines")
    {
        write("The sweetness of pines fill your senses.\n");
		return;
    }

    if (str == "grass")
    {
        write("A soft sweet scent caresses your senses.\n");
	return;
    }


}


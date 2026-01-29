/* Fountain's garden for the Rose garden at
 * Telberin. Main code by Shiva, modified by
 * Marisol (04/06/99)
 * modified by Damaris (04/03/2k) */

#include "../defs.h"

inherit ROSE_ROOM;

#include <macros.h>
#include <stdproperties.h>
#define TO this_object()
#define TP this_player()
#define ENV environment

void
create_rose_garden()
{
    set_short("The rose garden's fountain");
    set_em_long("You are standing in the center of the rose garden. "+
       "Before you is a beautiful ivory fountain. At the base of the "+
       "fountain is a six petal formation. You can feel the mist of the "+
       "cool water as it sprays upward forming an arch through the "+
       "clean air before falling musically into the basin.\n");

     add_item("fountain",
         "You look at the ivory fountain in awe. It is the centerpiece of "+
         "the rose garden. It has a round basin of white luminous ivory "+
         "and is filled with clear water from a higher tower of the same "+
         "material. The water sprays upward forming an arch through "+
         "the clean air only to fall musically in the pristine basin below.\n");

     add_item(({"formation", "base"}),
         "This formation is part of the base of the fountain. It is made "+
         "from the finest ivory and is clearly the work of Elven hands. "+
         "It spreads out from the base to form enchanting rose petals.\n");

     add_item(({"mist", "spray"}),
         "The mist is cool and gently floats from the upward spray of "+
         "the water.\n");

     add_item(({"ivory", "carving"}),
         "The ivory carving is free from inperfections, shining as it "+
         "reflects the mystical light that surrounds it.\n");

     add_item(({"arch", "water"}),
         "The water sprays upward forming an arch through the clean "+
         "air only to fall musically in the pristine basin below.\n");

     add_item(({"basin", "tower"}),
         "The basin and tower resembles a huge white rose and is "+
         "clearly the carving work of caring Elven hands.  The purest "+
         "of ivory was carved to create both the basin and the tower. "+
         "The ivory is free from imperfections, shining as it reflects the "+
         "mystical light that surounds it. A silver ladle hangs from a silver "+
         "chain that is fastened to the basin.\n");

    set_up_roses(0, ({"orange","red", "yellow", "pink"}));

    add_item( ({"roses"}),
      "Such wonderous flowers all around you. There are many "+
      "different colored roses.\n");


    add_item(({"ladle", "silver ladle", "silver chain", "chain"}),
        "A beautiful polished silver ladle hangs from a thin but strong "+
        "silver chain. You can see an ivory design is placed along the "+
        "handle of the ladle. The silver chain is fastened to the ivory "+
        "basin, so it cannot be removed.\n");

    add_item(({"design", "ivory design"}),
        "You look closer at the ivory design on the handle of the ladle. "+
        "You find it is of a single long stemmed rose with two pointed "+
        "leaves. One leaf on each side of the stem. You notice a small "+
        "nick in the center petal of the ivory rose.\n");

    add_prop(OBJ_I_CONTAIN_WATER, 1);


    add_exit("rose1", "north");
    add_exit("rose3", "west");
    add_exit("rose4", "south");
    add_exit("rose5", "east");
    add_exit("rose2", "northwest");
}

int
drink_it(string str)
{
    string what, where;
    int i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    /* See if syntax is "drink <something> from <something>" */
    if (sscanf(str, "%s from %s", what, where) != 2)
    {
        /* See if syntax is "drink from <something>" */
        if (!sscanf(str, "from %s", where))
        {
            /* Syntax must simply be "drink <something>" */
            what = str;
        }
    }

    if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (where && !parse_command(where, ({}), "[the] 'fountain' / 'basin'"))
    {
        /* Technically, this isn't going to show because of the standard
         * 'drink' command.  Really, there's not much choice, though,
         * since we don't want to return 1.
         */
        notify_fail("Drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("After you dip the ladle into the basin, you " +
            "take a drink of the sweet-tasting water.  Having " +
            "drunk your fill, you feel refreshed.\n");
    }
    else
    {
        write("After you dip the ladle into the basin, you take a "+
            "drink of the sweet-tasting water. You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) +" drinks some water from the "+
       "basin.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(drink_it, "drink");
}


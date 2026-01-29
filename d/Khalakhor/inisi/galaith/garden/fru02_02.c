#include "../defs.h"

inherit FRUIT_ROOM;

#include <macros.h>
#include <stdproperties.h>

void
create_fruit_garden()
{

    set_long("An enchanting fruit garden rests quietly within the "+
      "protective fold of towering pines. There are different sizes "+
      "and shapes of fruit all around you. Some fruits are ripe and "+
      "ready to be picked among the bushes and trees, and some are "+
      "not quite ready to be sampled. There is a simple stone path "+
      "that winds its way through the various plants and vines.\n");
    set_up_fruits(0, ({"cherry","blueberry", "blackberry"}));
    add_item(({"bushes", "blackberries", "blueberries", "berries"}),
      "There are blueberry and blackberry bushes growing along "+
      "side the path.\n");
    add_item(({"red fruit", "red tree", "cherry tree"}),
        "Sweet dark cherries grow in a few scattered cherry trees.\n");
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_exit("fru01_03", "northeast");
    add_exit("fru01_01", "northwest");
    add_exit("fru03_03", "southeast");
    add_exit("fru03_01", "southwest");

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
        write("After drinking your fill of water, you feel refreshed.\n");
    }
    else
    {
        write("After you dip the ladle into the basin, you take a "+
            "drink of the sweet-tasting water. You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the basin.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(drink_it, "drink");
}

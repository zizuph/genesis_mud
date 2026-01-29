#include "../defs.h"

inherit FRUIT_ROOM;

#include <macros.h>
#include <stdproperties.h>

void
create_fruit_garden()
{
    set_em_long("You are in a sweet smelling garden with sounds of life all around "+
       "you. There is a solitary tree at the very center of this section of "+
       "the garden. It is full of big, bright red fruits. You notice under "+
       "the tree there is a small fountain. There are berry bushes that "+
       "surround this area that isolates it from the rest of the garden. "+
       "The tree provides plenty of shade, suggesting that this might be"
     + " a very well suited place to spend a relaxing hour or two.\n");

     set_up_fruits(0, ({"pomegranate"}));

     add_item(({"etched designs", "designs"}),
        "You look closer at the etched designs on the fountain. They are "+
        "obviously carved by skilled elven hands. The designs are small "+
        "and delicate images of an asortment of fruits and leaves. All "+
        "different sizes and shapes.\n");

     add_item(({"berries", "elvenberries"}),
         "You look closer at the berries and discover they are "+
         "Elvenberries. Elvenberries are small, round and purple in color "+
         "with a splash of yellow near the stem. They quite rare and are "+
         "thought to hold magical powers.\n");

     add_item("fountain",
        "This fountain is a modest pillar of white marble with etched "+
        "designs that holds a simple but elegant basin.\n");

     add_item(({"basin"}),
        "This white marble basin is oval in shape but quite elegant with "+
        "etched designs along the outer rim. Cool water lightly sprays "+
        "upwards creating a light mist only to softly casade back into the "+
        "basin.\n");



    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_item(({"tree", "pomegranate"}),
        "This is a Pomegranate tree. This tree produces big round balls "+
        "that are bright red in color. Pomegranates are famous and "+
        "desired by many because of its reputation to give fertility to "+
        "those that eat it.\n");


    add_exit("fruit01", "north");
    add_exit("fruit03", "south");
    add_exit("fruit02", "west");
    add_exit("fruit05", "east");
    add_exit("fruit04", "southeast");


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

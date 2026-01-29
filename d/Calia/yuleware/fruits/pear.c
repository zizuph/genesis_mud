// OBJECT:  pear

    /* Calia Domain

    HISTORY

    [99-11-30] Created from [D:\CALIA\YULEWARE\FRUITS\PEAR.DOC] by Uhclem.

    PURPOSE

    This fruit can be tied with a ribbon and given as a gift to one player from
    another.  */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/yuleware/fruits/base_fruit";

#include <macros.h>
#include <language.h>

// Function:  special_effect(num)

/*

Purpose:  adds human interest (or hobbit, gnome, dwarf, elf, or goblin
interest) to the eating experience.

Arguments:  number of this type of fruit consumed.

Returns:  nothing.

*/

void
special_effect(int num)

{

    object tp = this_player();
    string tp_pro = tp->query_pronoun();
    string tp_obj = tp->query_objective();
    string tp_pos = tp->query_possessive();
    string *fruitwords = query_fruit_config();
    string hue = fruitwords[0];
    string glaze = fruitwords[1];
    string fruit = fruitwords[2];
    string hueword = explode(hue, " ")[sizeof(explode(hue, " ")) - 1];
    int n;

    string *write_single =
        ({
        "It's crunchy on the outside, moist and gooey on the" +
        " inside; 'a little like biting into a turtle,' you" +
        " muse, albeit " + LANG_ADDART(fruit) +
        "-flavored turtle in " + LANG_ADDART(glaze) +
        "-flavored candy shell.",
        "As you bite into the fruit, its juice" +
        " erupts through the " + glaze +
        " shell like a " + fruit + " volcano!"
        });

    /*
     *  The number of elements in write_multiple MUST equal the number in 
     *  say_multiple.    
     */

    string *write_multiple =
        ({
        "As you devour the " + fruit + "s, their juices" +
        " stampede across your taste buds like a herd of" +
        " wild " + fruit + " buffalo leaving " + hueword +
        " trails of " + glaze + " as they disappear" +
        " down your gullet.",
        "You greedily devour " + LANG_WNUM(num) +
        " " + fruit + "s at once, slurping up the pulp and" +
        " liquid and muttering incoherently, 'the" +
        " juice... the juice!'"
        });

    string *say_multiple =
        ({
        "devours the " + fruit + "s, their juices" +
        " stampeding across " + tp_pos + " taste buds like a herd of" +
        " wild " + fruit + " buffalo leaving " + hueword +
        " trails of " + glaze +
        " as they disappear down " + tp_pos + " gullet.",
        "greedily devours " + LANG_WNUM(num) +
        " " + fruit + "s at once, slurping up the pulp and" +
        " liquid and muttering incoherently, 'the" +
        " juice... the juice!'"
        });

    if (num == 1)

    {

        write (write_single[random(sizeof(write_single))] + "\n");

    }

    else

    {

        n = random(sizeof(write_multiple));
        write (write_multiple[n] + "\n");
        say (QCTNAME(tp) + " " + say_multiple[n] + "\n");

    }

}

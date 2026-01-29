// OBJECT:  orange

    /* Calia Domain

    HISTORY

    [99-12-05] Created from [D:\CALIA\YULEWARE\FRUITS\ORANGE.DOC] by Uhclem.

    PURPOSE

    This fruit can be tied with a ribbon and given as a gift to one player from
    another.  */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/yuleware/fruits/base_fruit";

#include <macros.h>
#include <language.h>
#include "defs.h"

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
        "The " + fruit + " breaks apart as you bite into" +
        " it, separating neatly into " + glaze + "-glazed sections," +
        " and you eat them all in quick succession, relishing" +
        " the combination of sweet flavors.",
        "The glaze cracks and dissolves as the fruit releases" +
        " its juice, and while both " + fruit +
        " and " + glaze + " glaze are sweet, the flavors mingle" +
        " in a blend that's surprisingly complex and satisfying."
        });

    /*
     *  The number of elements in write_multiple MUST equal the number in 
     *  say_multiple.    
     */

    string *write_multiple =
        ({
        "You have to tilt your head back to avoid losing any" +
        " of the luscious " + glaze + "-sweetened juice" +
        " as you pile " + LANG_WNUM(num) +
        " " + fruit + "s into your gaping mouth!",
        "You hold the " + fruit + "s aloft and squeeze, breaking" +
        " them into neat little sections, each edged with " + glaze +
        " glaze, then stuff the pieces into your mouth and" +
        " consume them in one, glorious, juicy gulp!"
        });

    string *say_multiple =
        ({
        "hase to tilt " + tp_pos + " head back to avoid losing any" +
        " of the luscious " + glaze + "-sweetened juice" +
        " as " + tp_pro + " pile " + LANG_WNUM(num) +
        " " + fruit + "s into " + tp_pos + " gaping mouth!",
        "holds " + LANG_WNUM(num) + " " + fruit + "s" +
        " aloft and squeezes, breaking them into neat" +
        " little sections, each edged with " + glaze +
        " glaze, then stuffs the pieces into " + tp_pos +
        " mouth and consumes them in one, glorious, juicy gulp!"
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

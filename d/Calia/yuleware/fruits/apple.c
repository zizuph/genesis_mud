// OBJECT:  apple

    /* Calia Domain

    HISTORY

    [99-12-02] Created from [D:\CALIA\YULEWARE\FRUITS\APPLE.DOC] by Uhclem.

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
        "The creamy flesh of the " + fruit + " is still firm" +
        " and tangy after being submerged under a layer of " + glaze +
        " glaze, but they both melt away in your mouth" +
        " with a delectable amalgamation of flavors.",
        "The " + glaze + " glaze and crisp " + fruit +
        " cleave into firm but succulent chunks, releasing" +
        " a unique combination of sweet and tangy flavors" +
        " with every bite."
        });

    /*
     *  The number of elements in write_multiple MUST equal the number in 
     *  say_multiple.    
     */

    string *write_multiple =
        ({
        "You stuff the " + fruit + "s into your mouth one" +
        " after the other, hardly pausing to swallow in" +
        " between, but the delectable taste of the fruit and" +
        " the " +  glaze + " glaze overwhelms your self-control!",
        "You greedily consume " + LANG_WNUM(num) +
        " " + fruit + "s in quick succession, acting as if" +
        " you had an uncontrollable addiction to fruit" +
        " covered with " + glaze + " glaze!"
        });

    string *say_multiple =
        ({
        "stuffs " + LANG_WNUM(num) +
        " " + fruit + "s into " + tp_pos + " mouth one" +
        " after the other, hardly pausing to swallow in" +
        " between, but the delectable taste of the fruit and" +
        " the " +  glaze + " glaze overwhelms " + tp_pos +
        " self-control!",
        "greedily consumes " + LANG_WNUM(num) +
        " " + fruit + "s in quick succession, acting as if" +
        " " + tp_pro + " had an uncontrollable addiction to fruit" +
        " covered with " + glaze + " glaze!"
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

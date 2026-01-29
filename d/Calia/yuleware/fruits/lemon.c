// OBJECT:  lemon

    /* Calia Domain

    HISTORY

    [99-12-02] Created from [D:\CALIA\YULEWARE\FRUITS\LEMON.DOC] by Uhclem.

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
        "The tart " + fruit + " juice dissolves and combines" +
        " with the sweet " + glaze + " to produce an" +
        " ambrosial flavor that would be difficult to duplicate" +
        " with even the finest cuts of meat!",
        "The " + glaze + " shell collapses as you" +
        " bite into the " + fruit + ", producing a rush of" +
        " zesty sweetened juice that dazzles your taste" +
        " buds and sinuses!"
        });

    /*
     *  The number of elements in write_multiple MUST equal the number in 
     *  say_multiple.    
     */

    string *write_multiple =
        ({
        "You stuff " + LANG_WNUM(num) + " " + fruit + "s" +
        " into your mouth, and the " + glaze + " glaze" +
        " covering them shatters into tiny sugary crystals, release" +
        " a flood of tart juice that makes you squint" +
        " and pucker savagely!",
        "It takes both hands and a gaping maw" +
        " to ravage the " + LANG_WNUM(num) + " " + fruit + "s" +
        " simultaneously, but the pleasure you derive from the" +
        " rush of tart juice tempered with sweet " + glaze +
        " is worth the effort!"
        });

    string *say_multiple =
        ({
        "stuffs " + LANG_WNUM(num) + " " + fruit + "s" +
        " into " + tp_pos + " mouth, and the " + glaze + " glaze" +
        " covering them shatters into tiny sugary crystals, release" +
        " a flood of tart juice that makes " + tp_pro + " squint" +
        " and pucker savagely!",
        "needs both hands and a gaping maw" +
        " to ravage the " + LANG_WNUM(num) + " " + fruit + "s" +
        " simultaneously, but the expression on " + tp_pos +
        " face attests that the pleasure of gorging on " + fruit +
        " and " + glaze + " is worth the effort!"
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

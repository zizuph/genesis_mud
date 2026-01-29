// OBJECT:  nectarine

    /* Calia Domain

    HISTORY

    [99-12-07] Created from [D:\CALIA\YULEWARE\FRUITS\NECTARIN.DOC] by Uhclem.

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
        "The flesh of the " + fruit + " is succulent" +
        " and exquisitely sweet, each bite enhanced by a" +
        " bit of " + glaze + ", a rich concoction tempered" +
        " with secret savory ingredients that prevent" +
        " the combination from being too sweet.",
        "The first bite is mostly " + glaze + ", but a" +
        " rush of " + fruit + " juice follows close behind," +
        " and the flavors blend into a delectable concoction" +
        " that leaves a lingering, exquisite aftertaste."
        });

    /*
     *  The number of elements in write_multiple MUST equal the number in 
     *  say_multiple.    
     */

    string *write_multiple =
        ({
        "You grasp the " + fruit + "s and toss - nay, hurl -" +
        " them in the direction of your gaping mouth, and with" +
        " a loud, sopping SPLAT they - well, the bulk of them -" +
        " explode within, releasing their heavy load of juice" +
        " and " + glaze + "!",
        "You glare at the " + fruit + "s and mutter" +
        " in a guttural voice, 'I want... I want to smash 'em!' And" +
        " smash them you do, ramming them one after the other" +
        " into your mouth and plundering their bounty" +
        " of juice and " + glaze + "!"
        });

    /*
     *  The quote 'I want... I want to smash 'em!' comes from the film A 
     *  Clockwork Orange.  It's the main character's response during a
     *  psychological test when shown a picture of some eggs and prompted,
     *  "you can whatever you want with these."    
     */

    string *say_multiple =
        ({
        "grasps " + LANG_WNUM(num) +
        " " + fruit + "s and tosses - nay, hurls -" +
        " them in the direction of " + tp_pos +
        " gaping mouth, and with a loud, sopping SPLAT they - well," +
        " the bulk of them - explode within, releasing their" +
        " heavy load of juice and " + glaze + "!",
        "glares at " + LANG_WNUM(num) + " " + fruit + "s and mutters" +
        " in a guttural voice, 'I want... I want to smash 'em!' And" +
        " smash them " + tp_pro + " does, ramming them one after" +
        " the other into " + tp_pos + " mouth and plundering" +
        " their bounty of juice and " + glaze + "!"
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

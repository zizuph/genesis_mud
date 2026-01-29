// OBJECT:  pinwheel

    /* Calia Domain

    HISTORY

    [99-11-22] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\PINWHEEL.DOC].

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_short("glittering pinwheel");
    set_name("pinwheel");
    add_name("paddles");
    add_name("toy");

    set_long("On top of a slender stick, stiff paper has" +
        " been shaped into multicolored glitter-speckled paddles" +
        " that spin when you blow on them. The paddles are" +
        " attached to the stick with a sturdy pin so they won't" +
        " come off no matter how hard you swing the pinwheel.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 125);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "The pinwheel is worth far more" +
        " to you in sentimental value than you could ever" +
        " obtain from selling it.\n");

    /*
     *  ITEMS    
     */

    add_item(({"paper", "paddles", "stiff paper", "paper paddles"}),
        "The paper paddles are painted in brilliant red, green," +
        " and white and speckled with bits of gold" +
        " and silver glitter.\n");

    add_item(({"stick", "slender stick"}),
        "The stick is long enough to let swing the pinwheel and" +
        " short enough to let you blow on it without poking" +
        " your eye out.\n");

    add_item(({"pin", "sturdy pin"}),
        "The pin is smooth and driven into the stick so that hardly" +
        " any of it is showing; it should hold firmly even" +
        " under the hardest use.\n");

}

// FUNCTIONS

// Function:  blow_pinwheel

/*

Purpose:  blow on the pinwheel to spin its paddles.

Arguments:  string indicating this pinwheel

Returns:  0/1

*/

int
blow_pinwheel(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to blow. */

    {

        notify_fail("Blow what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "[on] %o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " blows on a " + query_short() +
            ", sending its paddles spinning in vivid whirls" +
            " of green, red, and white laced with sparkles" +
            " of gold and silver.\n");

        write("You blow on your " + query_short() +
            ", sending its paddles spinning in vivid whirls" +
            " of green, red, and white. The myriad of sparkles in" +
            " front of your face looks like a miniature blizzard" +
            " of gold and silver!\n");

        return 1;

    }

    return 0;

}

// Function:  swing_pinwheel

/*

Purpose:  swing the pinwheel to spin its paddles.

Arguments:  string indicating this pinwheel

Returns:  0/1

*/

int
swing_pinwheel(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to blow. */

    {

        notify_fail("Swing what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " swings a " + query_short() +
            " around in circles, making great arcs of green," +
            " red, gold, and silver, spinning its paddles so" +
            " fast that they hum as loud as a swarm of bees!\n");

        write("You swing your " + query_short() +
            " around in circles, making great arcs of green," +
            " red, gold, and silver, spinning its paddles so" +
            " fast that they hum as loud as a swarm of bees!\n");

        return 1;

    }

    return 0;

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(blow_pinwheel, "blow");
    add_action(swing_pinwheel, "swing");

}

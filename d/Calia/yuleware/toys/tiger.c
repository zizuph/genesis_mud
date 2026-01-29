// OBJECT:  tiger

    /* Calia Domain

    HISTORY

    [99-11-22] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\TIGER.DOC].

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

    set_short("little toy tiger");

    set_name("tiger");
    add_name("toy");
    add_name("toy tiger");

    set_long("This little tiger is made of yellow cloth" +
        " with black stripes. Its broom-bristle wiskers and" +
        " bright button eyes make it look much more friendly" +
        " than ferocious, a cheerful companion to be cuddled" +
        " or squeezed when you're travelling far from home.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "The merchant says to you: What -" +
        " sell your little toy tiger? 'Tis the season to" +
        " give, not sell!\n");

    /*
     *  ITEMS    
     */

    add_item(({"cloth", "yellow cloth", "stripes", "black stripes"}),
        "The yellow cloth is thick and soft to the touch. The" +
        " stripes are jet black and run from the tip of the" +
        " tiger's nose all the way to the end of his tail.\n");

    add_item(({"ear", "ears", "tail"}),
        "The tail and ears on the little toy tiger feel a bit stiff," +
        " as if a wire inside gives them their shapes.\n");

    add_item(({"nose", "painted nose", "whiskers", "long whiskers",
        "bristles", "broom-bristles", "broom-bristle whiskers"}),
        "The broom-bristle whiskers stick straight out to either" +
        " side of the tiger's painted nose, and they're so long" +
        " they give his face a rather comical expression.\n");

    add_item(({"eyes", "button eyes", "face", "expression"}),
        "The tiger's face has a rather silly expression." +
        " Two buttons painted black and white for eyes" +
        " and long broom-bristles for whiskers sticking out" +
        " around its painted nose suggest a combination" +
        " of surprise and confusion.\n");

}

// FUNCTIONS

// Function:  cuddle_tiger

/*

Purpose:  it's what soft toy tigers are for!

Arguments:  string indicating this tiger

Returns:  0/1

*/

int
cuddle_tiger(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to cuddle. */

    {

        notify_fail("Cuddle what or whom?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " cuddles a " + query_short() +
            ", pressing it close against " + tp->query_possessive() +
            " body.\n");

        write("You cuddle your " + query_short() + " close" +
            " against your body, and as you hold it tightly the" +
            " expression on its face seems to change to" +
            " one of sheer contentment.\n");

        return 1;

    }

    return 0;

}

// Function:  squeeze_tiger

/*

Purpose:  it's the other thing that soft toy tigers are for!

Arguments:  string indicating this tiger

Returns:  0/1

*/

int
squeeze_tiger(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to squeeze. */

    {

        notify_fail("Squeeze what or whom?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " squeezes a " + query_short() +
            ". Its tail and ears stand up in an alert posture, and" +
            " it emits a tiny but ferocious growl!\n");

        write("You squeeze your " + query_short() +
            ". Its tail and ears stand up in an alert posture, and" +
            " it emits a tiny but ferocious growl!\n");

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
    add_action(cuddle_tiger, "cuddle");
    add_action(squeeze_tiger, "squeeze");

}

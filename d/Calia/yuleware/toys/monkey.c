// OBJECT:  monkey

    /* Calia Domain

    HISTORY

    [99-11-22] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\MONKEY.DOC].

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

    set_short("wooden monkey puppet on a string");
    set_name("puppet");
    add_name("monkey");
    add_name("string");
    add_name("monkey puppet");
    add_name("wooden monkey puppet");
    add_name("toy");

    set_long("The monkey is made of many small pieces of" +
        " wood, carved in exquisite detail and joined with metal" +
        " hooks and rings to make a remarkably flexible puppet." +
        " It moves almost like a real monkey whenever you jiggle" +
        " or jerk the string.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "The monkey puppet catches on" +
        " your clothes, almost like a child desperately holding" +
        " on to a parent! It's only a momentary illusion, of" +
        " course, but it persuades you to change your mind" +
        " about selling this little toy.\n");

    /*
     *  ITEMS    
     */

    add_item(({"wood", "pieces", "pieces of wood"}),
        "The individual pieces of wood are carefully carved" +
        " to simulate the look of fur.\n");

    add_item(({"metal", "hooks", "rings", "metal hooks", "metal rings"}),
        "The pieces of wood are joined by hooks and rings that" +
        " allow a wide range of movement.\n");

    add_item(({"string", "hands", "feet"}),
        "The monkey puppet is attached to the string at its" +
        " hands and feet, whose positions make it look like it" +
        " is climbing, but whether it is going up or down isn't" +
        " clear while it is motionless.\n");

}

// FUNCTIONS

// Function:  jiggle_string

/*

Purpose:  make the monkey climb the string.

Arguments:  string indicating this monkey

Returns:  0/1

*/

int
jiggle_string(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to jiggle. */

    {

        notify_fail("Jiggle what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " jiggles the string from which" +
            " a wooden monkey puppet is hanging. The little" +
            " monkey shimmies up to the top of the string, down" +
            " to the bottom, and then back to the middle where" +
            " it started, making cheerful clicking noises" +
            " all the way.\n");

        write("You jiggle the string from which your wooden" +
            " monkey puppet is hanging. The little monkey shimmies up" +
            " to the top of the string, down to the bottom, and then" +
            " back to the middle where it started," +
            " making cheerful clicking noises all the way.\n");

        return 1;

    }

    return 0;

}

// Function:  jerk_string

/*

Purpose:  make the monkey do a somersault.

Arguments:  string indicating this monkey

Returns:  0/1

*/

int
jerk_string(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to jerk. */

    {

        notify_fail("Jerk what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " jerks the string from which a" +
            " wooden monkey puppet is hanging. The" +
            " little monkey gyrates wildly around the string," +
            " then performs a somersault and neatly springs back" +
            " to the point on the string where it started!\n");

        write("You jerk the string from which your wooden" +
            " monkey puppet is hanging. The little monkey" +
            " gyrates wildly around the string, then performs a" +
            " somersault and neatly springs back to the point" +
            " on the string where it started!\n");

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
    add_action(jiggle_string, "jiggle");
    add_action(jerk_string, "jerk");

}

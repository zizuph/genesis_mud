// OBJECT:  spinboing

    /* Calia Domain

    HISTORY

    [99-11-22] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\SPINBOIN.DOC].

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. This toy is a silly variation on the popular
    fortune-telling 8-ball sold in modern novelty stores. The unusual words in
    the messages are all actual English words, most archaic but a few still in
    use in scientific circles.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// OBJECT DEFINITION

void
create_object()

{

    string color = ({"mauve", "beige", "puce", "taupe"})[random(4)];

    /*
     *  DESCRIPTION    
     */

    set_short(color + " spinboing");
    set_name("spinboing");
    add_name("toy");
    add_adj(color);

    set_long("It's an odd-looking thingumajig indeed: a little" +
        " like a teetotum, a little like a loggan," +
        " yet something quite different entirely carved from " + color +
        " stone. It's small enough to shake and smooth enough to" +
        " spin, but your examination of its parts leaves you with" +
        " more questions than answers.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 75);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "The merchant looks at you" +
        " with a bewildered expression and says: you can" +
        " keep that thing, whatever it is!\n");

    /*
     *  ITEMS    
     */

    add_item(({"parts", "part", "stone", color + " stone"}),
        "Each part is attached to every other part, if indeed" +
        " they are separate parts, as it's unclear exactly how" +
        " many parts there are. They're not shaped like any" +
        " other parts you've seen, unless, of course, you've" +
        " seen a genuine Calian spinboing before, but there" +
        " are some things about the parts that are recognizable: the" +
        " words YES, NO, MAYBE, and MAYBE-NOT etched so that" +
        " only one is visible at a time.\n");

    add_item(({"word", "words"}), "MAYBE.\n");

}

// FUNCTIONS

// Function:  spin_spinboing

/*

Purpose:  skip the spinboing.

Arguments:  string indicating this spinboing

Returns:  0/1

*/

int
spin_spinboing(string str)

{

    string word = ({"YES", "NO", "MAYBE",
        "UNLIKELY", "PROBABLY", "YES"})[random(6)];

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to spin. */

    {

        notify_fail("Spin what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " spins " + tp->query_possessive() +
            " " + query_short() + ". The" +
            " spinboing turbinates wantonly, circumvolving" +
            " rapidly at first, then slowing, all the" +
            " while producing an irritating screeching noise as" +
            " its parts rub together. When it stops, the word " + word +
            " is displayed on top.\n");

        write("You spin your " + query_short() + ". The" +
            " spinboing turbinates wantonly, circumvolving" +
            " rapidly at first, then slowing, all the" +
            " while producing an irritating screeching noise as" +
            " its parts rub together. When it stops, the word " + word +
            " is displayed on top.\n");

        add_item(({"word", "words"}), word + ".\n");
        return 1;

    }

    return 0;

}

// Function:  shake_spinboing

/*

Purpose:  shake the spinboing.

Arguments:  string indicating this spinboing

Returns:  0/1

*/

int
shake_spinboing(string str)

{

    string word = ({"YES", "NO", "MAYBE",
        "PROBABLY", "UNLIKELY", "NO"})[random(6)];

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to shake. */

    {

        notify_fail("Shake what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " shakes " + tp->query_possessive() +
            " " + query_short() + ". The" +
            " spinboing nutates with abandon, making a" +
            " clickety-clack sound as its parts strike each" +
            " other. It wabbles noisily for a few seconds, then" +
            " stops with the word " + word + " on top.\n");

        write("You shake your " + query_short() + ". The" +
            " spinboing nutates with abandon, making a" +
            " clickety-clack sound as its parts strike each" +
            " other. It wabbles noisily for a few seconds, then" +
            " stops with the word " + word + " on top.\n");

        add_item(({"word", "words"}), word + ".\n");
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
    add_action(spin_spinboing, "spin");
    add_action(shake_spinboing, "shake");

}

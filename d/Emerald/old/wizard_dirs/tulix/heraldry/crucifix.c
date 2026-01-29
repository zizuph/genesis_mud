/* A crucifix. This item is a part of the Heraldry quest in Emerald. */
/* Take it to the alter in the church. Coded by Tulix, 18/4/1993     */
/* It is worth a great deal of money, but you might have difficulty  */
/* selling it. #:-) */

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_object()
{
    set_name("crucifix");
    set_adj("golden");
    set_short("golden crucifix");
    set_long(break_string("It is a large and heavy golden crucifix. " +
        "It is obviously worth a lot of money, and should be returned " +
        "to the church, from where it was stolen by these despicable " +
        "thieves.\n",78));

    add_prop(OBJ_I_WEIGHT, 38600);    /* weighs 38.6kg     */
    add_prop(OBJ_I_VOLUME, 2000);     /* takes up 2litres  */
    add_prop(OBJ_I_VALUE, 20000);     /* Ouch! Expensive!  */
    add_prop(OBJ_M_NO_SELL, "@@my_sell");
}

/* *************************************************************************
 * This is to foil all those greedy bastards who want money - ho-ho! #:-)
 */

int
my_sell()
{
    say("The shop keeper takes the stolen crucifix from " + 
        QCTNAME(this_player())+", and hides it away.\n");
    write("The shop keeper gasps in astonishment!\n" +
        "He takes the crucifix from you, " +
        "and says: This crucifix was stolen!\n" +
        "The shop keeper then puts the crucifix " +
        "away in a safe place, so that he can\n" +
        "return it to its rightful owner.\n");

    seteuid(getuid());
    this_object()->move("/d/Emerald/tulix/workroom.c");
    return 1;
}


/* A tuning fork. This item is part of the Heraldry quest in Emerald. */
/* It is needed to shatter the quartz wall. Coded by Tulix, 18/4/1993 */

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_object()
{
    set_name("fork");
    set_adj("tuning");
    set_short("tuning fork");
    set_long(break_string("It is a large tuning fork, used for tuning " +
        "musical instruments. It looks like it is made of brass.\n ",78));

    add_prop(OBJ_I_WEIGHT, 850);     /* weighs 850g      */
    add_prop(OBJ_I_VOLUME, 100);     /* takes up 100ml   */
    add_prop(OBJ_I_VALUE, 100);      /* Quite expensive  */
}

void
init()
{
    ::init();
    add_action("do_ring", "ring");
    add_action("do_ring", "tap");
    add_action("do_ring", "hit");
}

int
do_ring(string str)
{
    notify_fail("What do you wish to do to what?\n");

    if (!str)
        return 0;

    if (str == "fork" || str == "tuning fork" )
    {
        write("The fork rings out a sharp 'CLANG!'. It hurts your ears!\n");
        say(QCTNAME(this_player()) + " rings out " + 
            this_player()->query_possessive() + " tuning fork with a sharp " +
            "'CLANG!'.\nIt seems to hurt your ears.\n");
    }
    return 1;
}


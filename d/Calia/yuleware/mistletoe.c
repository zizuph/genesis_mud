
/* Sprig of mistletoe.

   Coded by Maniac.
*/
inherit "/std/object";
inherit "/cmd/std/command_driver";

#include <macros.h> 
#include <const.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("mistletoe");
    add_name("sprig");
    set_short("sprig of mistletoe");
    set_long("A sprig of mistletoe. You could try `mistletoe <player>' " +
        "with it!\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
}


/* Mistletoe action */
int
do_mistletoe(string str)
{
    object *oblist, tp;

    tp = this_player();

    if (!stringp(str)) {
        notify_fail("Mistletoe whom?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Mistletoe whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You cannot mistletoe more than one person at once!\n");
        return 0;
    }

    target(" holds a " + short() + " above " + tp->query_objective() +
        "self and you and gives you a merry kiss!", oblist);
    actor("You hold the " + short() + " above yourself and", oblist, 
        " and give " + oblist[0]->query_objective() + " a merry kiss!");
    all2act(" holds a " + short() + " above " + tp->query_objective() +
        "self and", oblist, " and gives " + oblist[0]->query_objective() +
        " a merry kiss!");
    return 1;
}



void
init()
{
    ::init();
    add_action(do_mistletoe, "mistletoe");
}


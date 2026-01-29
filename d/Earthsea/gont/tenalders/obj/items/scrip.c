/*

 * a scrip (coin purse)
 * coded by Amelia 6/27/97
 * added gems - nov '02, Rhyn
 * Cotillion - 2016-08-10
 * - Removed steal protection
 * - Removed buggy put command override
 */

#pragma strict_types

inherit "/std/receptacle";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>

#define SUBLOC "_wearing_purse_subloc_"

public void
create_receptacle()
{
    set_keep();
    set_name(({"purse", "scrip"}));
    add_name("_amelias_scrip");
    add_name("equipment");
    set_adj(({"leather", "brown"})),
    set_short("leather purse");
    set_pshort("leather purses");
    set_long("A scrip. A dark-brown leather " +
        "purse that can be attached to your belt. It has a metal " +
        "clasp that fastens it securely. You can attach it " +
        "to (or detach it from) your belt.\n");
    add_prop(CONT_I_WEIGHT,100);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
    add_prop(CONT_I_MAX_VOLUME, 120000);
    add_prop(CONT_I_REDUCE_WEIGHT, 200);
    add_prop(CONT_I_REDUCE_VOLUME, 200);
    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_I_VALUE, 275);
}

public string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

public void
init_recover(string arg)
{
    init_container_recover(arg);
}

public int
prevent_enter(object ob)
{
    if (!ob->id("coin") && !ob->id("gem")) 
    {
        write("This purse is for coins and gems only.\n");
        return 1;
    }

    return 0;
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if(for_obj == carrier)
    {
        return "You have a brown leather scrip" +
            " tied to your belt with a bronze clasp.\n";
    }

    return capitalize(carrier->query_pronoun()) + " has a " +
        "brown leather scrip fastened to " +
        carrier->query_possessive() + " belt " +
        "with a bronze clasp.\n";
}

public int
attach(string str)
{
    object tp = this_player(), to = this_object();
    string dummy;

    if(!str || !present(to, tp) || !parse_command(str, environment(to),
        "%w [to] / [onto] [belt]", dummy) || !id(dummy))
    {
        return notify_fail("Attach what to what?\n");
    }

    if(query_prop(OBJ_M_NO_DROP))
    {
        return notify_fail("The scrip is already attached to your belt.\n");
    }

    tp->add_subloc(SUBLOC, to);
    write("You attach the leather scrip to your belt securely " +
        "fastening the clasp.\n");
    add_prop(OBJ_M_NO_DROP, "You must detach the scrip first.\n");
    return 1;
}

public int
detach(string str)
{
    object tp = this_player(), to = this_object();
    string dummy;

    if(!str || !present(to, tp) || !parse_command(str, environment(to),
        "%w [from] [belt]", dummy) && id(dummy))
    {
        return notify_fail("Detach what?\n");
    }

    if(!query_prop(OBJ_M_NO_DROP))
    {
        return notify_fail("The purse is not attached to your belt.\n");
    }

    write("You detach the purse from your belt.\n");
    tp->remove_subloc(SUBLOC);
    remove_prop(OBJ_M_NO_DROP);
    return 1;
}

public void
init()
{
    ::init();
    add_action(attach, "attach");
    add_action(detach, "detach");
}

public void
leave_env(object ob, object to)
{
    if (interactive(ob))
    {
        remove_prop(OBJ_M_NO_DROP);
    }

    ::leave_env(ob, to);
}

/*
 * rose pomade (lip stick)
 * coded by Amelia 6/27/97
*/

#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define SUBLOC "_rosey_lips_"

public void
create_object()
{
    set_name(({"jar", "pomade"}));
    set_adj(({"lovely", "rose", "rose-tinted"}));
    set_short("tiny jar of rose pomade");
    set_long("A tiny jar filled with rose " +
        "pomade, which can be applied to the lips to make them " +
        "appear more luscious and beautiful. You may <remove pomade> " +
        "later for a more natural look.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if(for_obj == carrier)
    {
        return "Your full lips have a luscious rose tint.\n";
    }

    return capitalize(carrier->query_possessive()) + " full " +
        "lips have a luscious rose tint.\n";
}

public int
apply(string str)
{
    object tp = this_player(), to = this_object();
    string dummy;

    if(!present(to, tp) || !str || !parse_command(str, environment(to),
        "%w [to] / [onto] [lips]", dummy) || !id(dummy))
    {
        return notify_fail("Apply what to what?\n");
    }

    tp->add_subloc(SUBLOC, to);
    write("You delicately apply a touch of rose pomade " +
        "to your lips, and instantly you feel more beautiful.\n" +
         "You use up the small container of pomade and discard it.\n");
    tell_room(environment(tp), QCTNAME(tp) + " applies a touch of " +
        "rose pomade to " + tp->query_possessive() + " lips, making "+
        "them appear luscious and red.\n", ({ tp }));
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    return 1;
}

public int
remove(string str)
{
    object tp = this_player();

    if(query_no_show() && id(str) && present(this_object(), tp))
    {
        write("You remove the pomade from your lips, " +
            "wiping it off delicately.\n");
        tell_room(environment(tp), QCTNAME(tp) + " delicately " +
            "wipes the pomade from " + tp->query_possessive() +
            " lips.\n", ({ tp }));
        tp->remove_subloc(SUBLOC);
        remove_object();
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();
    add_action(apply, "apply");
    add_action(remove, "remove");
}

public int
query_recover()
{
    return 0;
}

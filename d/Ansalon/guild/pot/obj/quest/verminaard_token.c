/* Ashlar, 29 Oct 97
        The object handling the Verminaard task
*/

inherit "/std/object";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../../guild.h"

int gotten_artifact;

string
long_descr()
{
    if (gotten_artifact)
        return "This black metal token is useless now. You can discard it.\n";
    else
        return "This black metal token is a message to Verminaard that " +
        "you are the courier to carry the artifact back to the Temple. " +
        "Just show it to the Highlord.\n";
}

void
create_object()
{
    set_name("token");
    add_name("verminaard_token");
    set_adj("black");
    add_adj("metal");
    set_long("@@long_descr");
    add_prop(OBJ_M_NO_DROP, "You better hold on to the black metal token.\n");
    add_prop(OBJ_M_NO_GIVE, "Better keep this token to show to Verminaard.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

int
do_discard(string arg)
{
    if (!stringp(arg) || !id(arg))
    {
    	NF("Discard what?\n");
    	return 0;
    }
    if (!gotten_artifact)
        write("The token may still be of use, better hold on to it.\n");
    else
    {
        write("You throw away the black metal token.\n");
        set_alarm(2.0,0.0,&remove_object());
    }
    return 1;
}

void
give_artifact(object verm, object tp)
{
    object art;
	
    if (!objectp(verm) || !objectp(tp))
        return;
    if (E(verm) != E(tp))
        return;

    verm->command("say Good. Bring this artifact to the Temple " +
    "quickly, and look out for trouble on the way.");
    verm->command("say I hope, for your sake, that you will not fail.");

    art = clone_object(GUILDDIR + "obj/quest/verminaard_artifact");
    tp->catch_msg(QCTNAME(verm) + " gives you " +
    LANG_ADDART(art->short()) + ".\n");
    tell_room(E(tp), QCTNAME(verm) + " gives something to " +
    QTNAME(tp) + ".\n", ({ verm, tp }));
    if (art->move(tp))
    {
    	tp->catch_msg("It is too heavy, and you drop it on the floor.\n");
    	art->move(E(tp));
    }
    gotten_artifact = 1;
}

int
do_show(string arg)
{
    string what, whom;
    object verm;
    
    NF("Show what to whom?\n");
    if (!stringp(arg))
        return 0;

    if (sscanf(arg, "%s to %s", what, whom) != 2)
        return 0;

    if (!id(what))
        return 0;

    if (C(whom) != "Verminaard")
    {
    	NF("The token would not be of much interest to anyone but Verminaard.\n");
    	return 0;
    }

    verm = P("verminaard", E(TP));
    if (!objectp(verm))
    {
    	NF("Verminaard isn't here.\n");
    	return 0;
    }

    TP->catch_msg("You show your black metal token to " + QTNAME(verm) + ".\n");
    tell_room(E(TP), QCTNAME(TP) + " shows something to " + QTNAME(verm) +
    ".\n", ({ TP, verm }));

    set_alarm(3.0,0.0,&give_artifact(verm,TP));
    return 1;
}

void
init()
{
    ::init();
    add_action(do_show, "show");
    add_action(do_discard, "discard");
}

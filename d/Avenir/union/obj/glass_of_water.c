// name:  glass_of_water   /d/Avenir/union/obj/glass_of_water.c
// creator(s):    Cirion, January 1998
// purpose:       Water for members of the Union
#pragma strict_types
#include "../defs.h"

inherit "/std/drink";

#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>

#define TOAST_STR "_avenir_s_toast_str"
#define TOAST_WHEN "_avenir_i_toast_when"


public void
create_drink(void)
{
    reset_euid();

    set_name("water");
    add_name(({"glass","crystal","goblet", "_crucible_component"}));
    set_short("crystal of pure water");
    set_pshort("crystals of pure water");
    set_long("It is a goblet made from thin, delicate crystal. It is "+
	"filled with pure, cold, sparkling water.\n");
    set_soft_amount(100);
    set_alco_amount(0);

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

// clone an empty glass for the player
public void
special_effect(int num)
{
    if (!ENV(TO))
	return;

    for (int i = 0; i < num; i++)
	catch(clone_object(OBJ + "glass")->move(ENV(TO), 1));
}

public int
toast(string str)
{
    object *whom;
    string to_what;

    if (!strlen(str) || !sscanf(str, "to %s", to_what))
    {
	if ((str = TP->query_prop(TOAST_STR)) &&
	    (time() - TP->query_prop(TOAST_WHEN) < 100))
	{
	    write("You raise your " + short() + " and toast in unison "+
		str + ".\n");
	    say(QCTNAME(TP) +" raises " + HIS(TP) + " " + short() +
		" and toasts in unison " + str + ".\n");
	    return 1;
	}

	NF("Toast to what?\n");
	return 0;
    }

    write("You raise your "+ short() +" in a toast to "+ str + ".\n");
    say(QCTNAME(TP) +" raises "+ HIS(TP) +" " + short() +
	" in a toast to " + str + ".\n");

    whom = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
    whom->add_prop(TOAST_STR, str);
    whom->add_prop(TOAST_WHEN, time());

    return 1;
}

public void
init(void)
{
    ::init();

    if (environment() == TP)
	add_action(toast, "toast");
}

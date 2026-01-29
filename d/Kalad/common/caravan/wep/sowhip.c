#include "../default.h"
inherit (STD + "weapon");

#include <ss_types.h>
#include <wa_types.h>

#define SUBLOC "holding_whip_subloc"

void
create_weapon()
{
    ::create_weapon();

    set_name("whip");
    set_adj("vicious");
    set_long("A tanned leather whip, it is at least 6 feet long.\n");
    set_hit(25);
    set_pen(14);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_VALUE,240);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,500);
}

void
enter_env(object to, object from)
{
    if (living(to))
	to -> add_subloc(SUBLOC, this_object());
    ::enter_inv(to, from);
}

void
leave_env(object from, object to)
{
    if (living(from))
	from -> remove_subloc(SUBLOC);
    ::leave_env(from, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
    if (for_obj == carrier)
	str = "You look ";
    else
	str = capitalize(carrier->query_pronoun()) + " looks ";
    return str + "quite terrifying with that whip.\n";
}

void
init()
{
    ::init();
    add_action("crack","crack");
}

int
crack()
{
    if(!query_wielded())
    {
	write("You must wield the whip first!\n");
	return 1;
    }
    write("You raise the whip above you and snap it down.\n");
    write("The whip goes CRACK!\n");
    say(QCTNAME(TP) + " raises the whip above " + TP->query_objective() + "self and snaps it down.\n");
    say("The whip goes CRACK!\n");
    return 1;
}

#include "../default.h"
inherit (STD + "armour");

#define SUBLOC "wearing_cloak_subloc"

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("cloak");
    set_adj("concealing");
    add_adj("black");
    set_long("An extremely dark fur-lined cloak designed to conceal its "+
      "wearer's features. A large hood on the cape accomplishes that task "+
      "nicely.\n");
    set_ac(5);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,720);
    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,2500);
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
	str = "Your face ";
    else
	str = capitalize(carrier->query_possessive()) + " face ";
    return str + "is hidden by the hood of the concealing black cloak.\n";
}

inherit "/std/object";
#include "/sys/stdproperties.h"
#define SUBLOC "holding_spectacles_subloc"
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
    set_name("spectacles");
    set_adj("iron-rimmed");
    set_long("A set of seeing glasses, probably used by some librarian "+
      "or other avid reader.\n");
    add_prop(OBJ_I_VALUE,180);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,50);
    add_prop(OBJ_M_NO_SELL,1);
}
void
enter_env(object to, object from)
{
    if (living(to))
	to->add_subloc(SUBLOC, TO);
    ::enter_inv(to, from);
}
void
leave_env(object from, object to)
{
    if (living(from))
	from->remove_subloc(SUBLOC);
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
    return str + "quite intelligent wearing those spectacles.\n";
}

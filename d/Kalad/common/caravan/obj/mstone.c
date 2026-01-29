inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#define SUBLOC "holding_stone_subloc"
/* by Antharanos */
void
create_object()
{
    set_name("stone");
    set_adj("mundane");
    set_long("An utterly worthless piece of rock, the kind you find in the "+
      "gutter.\n");
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,250);
}
void
enter_env(object to, object from)
{
    if (living(to))
	to->add_subloc(SUBLOC, this_object());
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
    return str + "pretty stupid holding that mundane stone.\n";
}

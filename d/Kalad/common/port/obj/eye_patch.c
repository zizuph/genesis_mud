inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#define SUBLOC "wearing_eyepatch_subloc"
/* by Antharanos */
void
create_object()
{
    set_name("patch");
    set_adj("eye");
    set_short("eye patch");
    set_long("A large black eye patch, with a bone-white star at its "+
      "center.\n");
    add_prop(OBJ_I_VALUE,120);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_WEIGHT,100);
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
	str = "You have ";
    else
	str = capitalize(carrier->query_pronoun()) + " has ";
    return str + "a large black eye patch over the right eye.\n";
}

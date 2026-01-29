inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#define SUBLOC "wearing_tattoo_subloc"
query_auto_load()
{
    return MASTER;
}
/* by Antharanos */
void
create_object()
{
    set_name("dkcpot13");
    add_name("skeeverisreallyaniceguy");
    set_long("A tattoo.\n");
    add_prop(OBJ_I_VALUE,144);
    add_prop(OBJ_I_INVIS,100);
    add_prop(OBJ_M_NO_DROP,1);
    set_no_show();
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
    return str + "a tattoo of a great sailing ship, entitled 'The Seahawk'.\n";
}

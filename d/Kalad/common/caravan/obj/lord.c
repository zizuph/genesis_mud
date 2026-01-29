inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#define SUBLOC "wearing_lord_subloc"
/* by Antharanos */
void
create_object()
{
    set_name("jewel");
    set_adj("priceless");
    set_long("The bearer of this precious jewel is recognized as the "+
      "Lord of the Trading Company. You could probably show it off, just to "+
      "prove who you really are.\n");
    add_prop(OBJ_I_VALUE,8640);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_M_NO_DROP,"Only death can rob you of this! You cannot be rid of it!\n");
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
	str = "You are ";
    else
	str = capitalize(carrier->query_pronoun()) + " is ";
    return str + "the Lord of the Trading Company.\n";
}
init()
{
    ::init();
    add_action("show","show");
}
show()
{
    write("You haughtily show off your priceless jewel.\n");
    say(QCTNAME(TP) + " haughtily shows off " + TP->query_possessive() + " priceless jewel.\n");
    set_alarm(2.0,0.0,"show_effect");
    return 1;
}
show_effect()
{
    write("You catch yourself admiring the jewel's glorious beauty.\n");
    say("You gaze at the priceless jewel in all its glorious beauty.\n");
    return 1;
}

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "defs.h"
#define SUBLOC "having_skincolour_subloc"

string colour_desc = "none";

string
query_auto_load()
{
	return (MASTER_OB(this_object()) + ":#d#" + colour_desc + "#");
}

void
init_arg(string arg)
{
    string garbage;
 
    if (!strlen(arg)) return;
    sscanf(arg, "%sd#%s#%s", garbage, colour_desc, garbage);
}


void
create_object()
{
	set_name("colourob");
	add_name("_colour_ob_");
	add_prop(OBJ_I_VALUE, 1728);
	add_prop(OBJ_I_INVIS, 100);
	add_prop(OBJ_I_NO_STEAL, 1);
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
      str = "You have " + colour_desc + " ";
   else
      str = capitalize(carrier->query_pronoun()) + " has " + colour_desc + " ";
   return str + "skin.\n";
}

string return_colour_desc() { return colour_desc; }

void
set_colour_desc(string new_desc)
{
	if (new_desc=="none") remove_object();
	colour_desc = new_desc;
	return;
}

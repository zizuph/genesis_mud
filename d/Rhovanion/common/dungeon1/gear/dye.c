inherit "/std/object";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
void
create_object() {
set_name("mute's_dye");
set_long("none\n");
add_prop(OBJ_I_INVIS, 1);
add_prop(OBJ_I_VALUE, 0);
add_prop(OBJ_I_WEIGHT, 0);
add_prop(OBJ_I_VOLUME, 0);
}
void
enter_env(object dest, object old)
{
   if (interactive(dest))
      dest->add_subloc("it_subloc",this_object());
   ::enter_env(dest, old);
}

void
leave_env(object from, object to)
{
   if (interactive(from))
      from->remove_subloc("it_subloc");
   ::leave_env(from, to);
}
string
show_subloc(string subloc, object me, object for_obj)
{
   string str;
   if (subloc != "it_subloc")
      return me->show_subloc(subloc, me, for_obj);
   
   if (me->query_prop("_temp_subloc_show_only_things"))
      return "";
   
   if (for_obj == me)
str = "Your skin is ";
else
str = capitalize(me->query_pronoun()) + " has skin that is ";
return str + "brightly colored " + ONE_OF_LIST(({
"red","orange","green","blue","purple","purple with yellow spots",
"red and white striped"})) + ".\n";
}

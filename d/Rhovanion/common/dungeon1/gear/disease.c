inherit "/std/object";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
void
create_object() {
   set_name("disease");
   set_adj("sexually transmitted");
   set_long("This horrid disease is making your genitals " +
      "ooze goo.  You'd better get rid of it quick!!!\n");
   add_prop(OBJ_I_HIDE, (ONE_OF_LIST(({ 25, 30, 30, 30,
                  35, 35, 40, 60 }))));
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
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
      str = "You are ";
   else
      str = capitalize(me->query_pronoun()) + " is ";
   return str + "inflicted with a foul sex disease " +
   "causing an oozing of the genitalia.\n";
}

string
query_auto_load()
{
   return MASTER_OB(this_object()) + ":";
   
}
void
init_arg(string str) { }

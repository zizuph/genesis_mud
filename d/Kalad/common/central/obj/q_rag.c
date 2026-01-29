inherit "/std/object";
#include "/d/Kalad/defs.h"
#define SUBLOC "holding_rag_subloc"
/* The rag used to polish the bell within the tower in the Central 
District in Kabal */
/* by Antharanos */
void
create_object()
{
   set_name("rag");
    add_name("smelly_quest_rag");
   set_adj("smelly");
   set_long("A dirty, nasty-smelling tattered rag.\n");
   add_prop(OBJ_I_VALUE,10);
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
      str = "You are ";
   else
      str = capitalize(carrier->query_pronoun()) + " is ";
   return str + "holding a smelly rag.\n";
}
init()
{
   ::init();
   add_action("show","show");
}
show()
{
   write("You show off the smelly rag.\n");
   say(QCTNAME(TP) + " shows you a smelly rag.\n");
   set_alarm(2.0,0.0,"show_effect");
   return 1;
}
show_effect()
{
   write("The rag sure does smell. Ugh.\n");
   say("Boy, that rag held by " + QTNAME(TP) + " sure does stink.\n");
   return 1;
}

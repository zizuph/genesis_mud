inherit "/std/object";

#include "/d/Emerald/defs.h"

#define PEG_LEG_SUBLOC "_peg_leg"

void
create_object()
{
   set_short("old wooden peg leg");
   set_name("leg");
   set_adj("old");
   set_adj("wooden");
   set_adj("peg");
   set_long("This is an old peg leg.\n");
   
   add_prop(OBJ_M_NO_DROP,1);
   add_prop(OBJ_M_NO_GIVE,1);
   
   seteuid(getuid());
}


string
query_auto_load()
{
return PIRATES_DIR+"obj/peg_leg:"+"0";
}


void
enter_env(object env,object from)
{
   object lost_leg;
   ::enter_env(env, from);
   env->add_subloc(PEG_LEG_SUBLOC,this_object());
   if(present("lost_leg",TP))
      {
      lost_leg = present("lost_leg",TP);
      lost_leg ->remove_object();
      return;
   }
   return;
}
string
show_subloc(string subloc,object carrier,object for_obj)
{
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return"";
   if(for_obj == carrier)
      return "You are wearing a wooden peg leg.\n";
   return CAP(carrier->query_pronoun())+" is wearing "+
   "a wooden peg leg.\n";
}

inherit "/std/object";

#include "defs.h"

#define LOST_LEG_SUBLOC "_lost_leg"

void
create_object()
{
   set_short(0);
   set_name("lost_leg");
   set_no_show();
   
   add_prop(OBJ_M_NO_DROP,1);
   add_prop(OBJ_M_NO_GIVE,1);
   
   seteuid(getuid());
}

string
show_subloc(string subloc,object carrier,object for_obj)
{
   if(for_obj == carrier)
      return "You are missing a leg.\n";
   return CAP(carrier->query_pronoun())+" is missing a leg.\n";
}

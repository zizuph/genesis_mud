
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

string namn;

void
create_object()
{
   namn="";
   set_name("skin"); 
   set_short("shark skin");
   set_long("The skin is torn from a white shark.\n");
   set_adj("white");
}

enter_env(object dest, object from)
{
   ::enter_inv(dest,from);
   if (namn=="") 
      namn=dest->query_real_name();
}

query_namn() {return namn; }



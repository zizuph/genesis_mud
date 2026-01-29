 
inherit "/std/object";
#include <spguild.h>
 
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
  set_name(({"spider"}));
  set_long("It's your huge black spider.\n"+
           "You are riding it.\n");
  set_short("huge black spider");
  set_adj(({"huge","black"}));
  add_prop(OBJ_I_VOLUME, 1);
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VALUE,  100000);
  add_prop(OBJ_M_NO_SELL,1);
  add_prop(OBJ_M_NO_DROP,1);
}
 
void install()
{
  TP->add_subloc(file_name(TO),TO);
  set_no_show_composite(1);
}
 
void remove_me()
{
  TP->remove_subloc(file_name(TO));
  ::remove_object();
}
 
string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != file_name(TO))
      return "";
 
    if (for_obj != on)
      return CAP(HE(on))+" is riding a huge black spider.\n";
    else
      return "You are riding the huge black spider.\n";
}

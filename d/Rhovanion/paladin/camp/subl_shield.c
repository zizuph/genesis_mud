 
inherit "/std/object";
 
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
  set_name(({"shield"}));
  set_long("It is magical shield glowing in rainbow clours!\n");
  set_short("magical shield");
  set_adj(({"magical"}));
  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
  add_prop(OBJ_I_VOLUME, 1);
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VALUE,  100000);
  add_prop(OBJ_M_NO_SELL,"No! This shield protects you really WELL !"+
          " You don't want to sell it !\n");
  add_prop(OBJ_M_NO_DROP,"No! This shield protects you really WELL !"+
          " You don't want to drop it !\n");
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
      return CAP(HE(on))+" has a bright magical shield glowing in "+
             "rainbow colours around "+HIS(on)+" body!\n";
    else
      return "You have a bright magical shield glowing in "+
             "rainbow colours around your body!\n";
}

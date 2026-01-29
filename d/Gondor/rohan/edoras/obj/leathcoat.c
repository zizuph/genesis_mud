/* testing armour */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

create_armour()
{
  set_name("coat");
  set_pname("coats");
  set_adj("leather");
  set_short("leather coat");
  set_pshort("leather coats");
  set_long(break_string("This is a leather coat, made out of deer hide and adorned with embroidery. " +
    "It probably was quite expensive when it was new, but it has seen much use since then.\n",70));
  set_default_armour(10,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,3500);
  add_prop(OBJ_I_VOLUME,500+random(400));
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(300)-100);
 }


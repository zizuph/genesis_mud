/* Pelargir orphan armour */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

create_armour()
{
  set_name("vest");
  set_adj("leather");
  set_name("leather vest");
  set_short("leather vest");
  set_pshort("leather vests");
   set_long(break_string("This leather vest has been smeared "+
      "with so much grease it has turned black.\n",70));
  set_default_armour(6,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,500+random(400));
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)+random(300)-100);
 }


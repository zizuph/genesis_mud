/* Pelargir orphan armour */
inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

create_armour()
{
  set_name("coat");
  set_adj("cloth");
  set_name("cloth coat");
  set_short("cloth coat");
  set_pshort("cloth coats");
   set_long(break_string("This is a shabby cloth coat, not much of a fashion statement.\n",70));
  set_default_armour(6,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,500+random(400));
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)+random(300)-100);
 }


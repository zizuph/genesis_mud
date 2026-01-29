/* Shield of the Haradrim */
inherit "/std/armour";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
  set_name("shield");
  add_name("Harad_Shield");
  set_pname("shields");
  set_short("round spiked shield");
  set_pshort("round spiked shields");
  set_adj("yellow");
  set_adj("black");
  set_adj("round");
  set_adj("spiked");
  set_long("The round shield is yellow and black, with big spikes. It is a shield\n"+
    "from the far south, from Harad.\n");
  set_default_armour(20,A_SHIELD,({ -1, 1, 2}),0);
  add_prop(OBJ_I_WEIGHT, 3300);
  add_prop(OBJ_I_VOLUME, 900);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(15)-7);
}

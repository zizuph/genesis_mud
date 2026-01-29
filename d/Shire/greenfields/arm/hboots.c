inherit "/std/armour";
inherit "/lib/keep";
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

object wearer;

void create_armour()
{
  set_name("boots");
  add_name(({"pair of boots","pair of steel-clad leather boots"}));
  set_adj(({"steel-clad","leather","thick","blue","dark blue"}));
  set_short("pair of steel-clad leather boots");
  set_pshort("pairs of steel-clad leather boots");
  set_long("This "+short()+" has sturdy steel plates bound directly "+
    "to thick leather to offer improved protection. The leather "+
    "has been dyed dark blue to match the lacquered stripes of "+
    "dark blue edged in gold and silver that crisscross their "+
    "way along the length of the steel cladding. The leather is "+
    "very thick and stiff, and the cladding covers both the shins and "+
    "the thighs, so the "+short()+" was obviously meant to be worn "+
    "in combat.\n");
  set_default_armour(30,A_LEGS | A_FEET,({1,1,-2}),0);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(30,A_LEGS) - 1234);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30) + random(101));
  add_prop(OBJ_I_VOLUME,F_VOLUME_ARMOUR);
  set_keep();
}


public int wear()
{
  wearer = this_player();
  WRITEN("You slide your feet into the "+short()+".");
  SAY(" pulls on the "+short()+".");
  return 1;
}
  

public int remove()
{
  WRITEN("You tug the "+short()+" off your legs.");     
  say(QCTNAME(wearer)+" pulls off the "+short()+".\n");
  return 1;
}

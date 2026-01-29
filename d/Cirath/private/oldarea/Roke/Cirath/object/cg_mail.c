inherit "/std/armour";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include "/std/combat/combat.h"

create_armour()
{
  set_name("scalemail");
  set_short("guardian scalemail");
  set_long("The scalemail are made of robust steel and are black and red with "+
    "the sign of the cirathian guardian force on it.\n");
  set_adj("guardian");
  add_adj("cirathian");

  set_ac(35);
  set_am(({0,1,1}));
  set_at(A_TORSO);

  add_prop(OBJ_I_WEIGHT,15000);
  add_prop(OBJ_I_VOLUME,10000);
}

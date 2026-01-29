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
  set_name("ringmail");
  set_short("rust-stained ringmail");
  set_long("The ringmail lokks very used and is filthy. It has some "+
    "stains of rust on it too, but looks like it can protect you anyway.\n");
  set_adj("rust-stained");

  set_ac(16);
  set_am(({-1,1,1}));
  set_at(A_TORSO);

  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,3000);
}

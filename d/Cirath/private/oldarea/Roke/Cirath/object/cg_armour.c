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

#define OBJ_I_CIRATHIAN "_obj_i_cirathian"

int a_class;

void
create_object()
{
  a_class = 5;

  set_name("scalemail");
  set_short("cirathian scalemail");
  set_long("The scalemail are made of robust steel and are black and red with "+
    "the sign of the cirathian guardian force on it.\n");
  set_adj("cirathian");
  add_adj("excellent");

  set_ac((6 * a_class) + random(a_class) + 1);
  set_am(({0,1,1}));
  set_at(A_TORSO);
  add_prop(OBJ_I_WEIGHT,7500 + random(7500));
  add_prop(OBJ_I_VOLUME,10000);
  return;
}

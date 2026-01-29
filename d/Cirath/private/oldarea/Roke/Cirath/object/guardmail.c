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
  set_name("platemail");
  set_short("heavy guardian platemail");
  set_long("Ouch! This platemail is something else! Heavy.\n");
  set_adj("guardian");
  add_adj("heavy");

  set_ac(25);
  set_am(({-1,1,1}));
  set_at(A_TORSO);


}

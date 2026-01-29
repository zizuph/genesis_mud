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
  set_name("armour");
  set_short("nomad leather armour");
  set_long("This armour is made of leather. It is made "+
           "by the cirathian nomad warriors, a violent "+
           "tribe that is living in the desert.\n");
  set_adj("leather");
  add_adj("nomad");

  set_ac(10);
  set_am(({-1,1,1}));
  set_at(A_TORSO);


}

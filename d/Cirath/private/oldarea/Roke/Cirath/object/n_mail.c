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
  set_name("mail");
  set_short("nomad splint mail");
  set_long("This is a splint mail made of steel. The mail "+
           "is made by armourers in Cirath and used by the "+
           "hostile, nomad warriors that lives in the desert.\n");
  set_adj("splint");
  add_adj("nomad");

  set_ac(15);
  set_am(({-1,1,1}));
  set_at(A_TORSO);


}

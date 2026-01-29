/* l_shirt.c : Body armour for Jaryx of the Golden Inix Inn : 06/19/98 */

inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
  ::create_armour();
  set_name("shirt");
  set_pname("shirts");
  set_short("leather shirt");
  set_adj("leather");
  set_long("A simple shirt made of hardened leather.");

  set_ac(20);
  set_am(({0, 0, 0}));
  set_at(A_BODY);

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME,  700);
}

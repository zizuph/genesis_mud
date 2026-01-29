// Standard mail shirt for guards in the Bazaar area.
//    -Ilyian, May 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>


void
create_armour ()
{
  set_name("mail");
  add_name("shirt");
  set_short("steel chain-link shirt");
  add_adj(({"steel", "chain-link", "chain", "link"}));
  set_long ("This shirt is expertly fashioned from small links of steel "
           +"worked together to provide good protection for the torso. "
           +"It is quite light, and seems to be standard issue.\n");
  set_ac (25 + random (3));
  set_am(({ -1, 3, -2}));
  set_at (A_BODY);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(28, A_BODY));
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(28));
}


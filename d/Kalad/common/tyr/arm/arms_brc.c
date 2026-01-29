/* arms_brc.c : Bracers for Jaryx of the Golden Inix Inn : 06/16/98 */

inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
  ::create_armour();
  set_name("bracers");
  set_short("pair of leather bracers");
  set_pshort("pairs of leather bracers");
  set_long("These bracers are made from hardened leather.\n");

  set_adj("leather");

  set_ac(15);
  set_am(({0,0,0}));
  set_at(A_ARMS);

  add_prop(OBJ_I_WEIGHT,  800);
  add_prop(OBJ_I_VOLUME,  400);
}

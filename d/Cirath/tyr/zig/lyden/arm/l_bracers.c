/* Bracers for Jaryx */

inherit "/std/armour";
#include <wa_types.h>
#include "../local.h"

void create_armour()
{
  set_name("bracers");
  set_pname("bracers");
  set_short("pair of leather bracers");
  set_pshort("pairs of leather bracers");
  set_long("These bracers are made from hardened leather.");

  set_adj("leather");

  set_ac(35);
  set_am(({0,0,0}));
  set_at(A_ARMS);

  add_prop(OBJ_I_WEIGHT,  800);
  add_prop(OBJ_I_VOLUME,  400);
}

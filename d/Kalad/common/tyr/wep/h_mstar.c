/* A weapon for Jaryx */

inherit "/d/Kalad/std/weapon";
#include "defs.h"
#include <wa_types.h>

void create_weapon()
{
  set_name("morningstar");
  set_pname("morningstars");
  set_adj("huge");
  add_adj("stone");
  set_short("huge stone morningstar");
  set_long("This club is large, very heavy, and worn "+
     "from extensive use.\n");

  set_default_weapon(
    28,
    40,
    W_CLUB,
    W_NONE,
    0);

  add_prop(OBJ_I_WEIGHT, 50000);
  add_prop(OBJ_I_VOLUME,  9000);
}

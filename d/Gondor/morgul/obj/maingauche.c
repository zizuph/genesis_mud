/* A main gauche
 * Last Modification: Olorin, July 1994
 */

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"gauche", "dagger", "knife"}));
    set_pname(({"gauches", "daggers", "knives", "weapons"}));
  set_adj(({"main", "sharp", "steel"}));
  set_short("main gauche"); set_pshort("mains gauches");
  set_long(BSN("This is a sharp steel dagger to be " +
    "wielded in the left hand. It has a slender steel blade " +
    "and a wooden hilt covered with leather. On the hilt, " +
    "you see the picture of a Moon disfigured with a ghastly " +
    "face of death."));

  set_default_weapon(16,12,W_KNIFE,W_SLASH|W_IMPALE,W_LEFT,0);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(16,12)+random(150)+50);
  add_prop(OBJ_I_WEIGHT,
	(F_WEIGHT_DEFAULT_WEAPON(16, W_KNIFE) + random(200) - 100));
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
  add_prop(GONDOR_M_MORGUL_NO_SELL, 1);
}


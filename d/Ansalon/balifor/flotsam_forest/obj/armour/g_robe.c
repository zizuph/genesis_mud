/* created by Aridor, 09/15/94 */

inherit "/std/armour";

#include <wa_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_armour()
{
    set_name("robe");
    set_adj("grey");
    set_short("grey robe");
    set_long("This thick grey robe is made of some strange " +
      "fabric. While old and seemingly well worn, you notice " +
      "no patches on it or a single frayed edge.\n");
    set_ac(30);
    set_am(({0,0,-23}));
    set_at(A_TORSO | A_LEGS | A_ROBE);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This grey robe is enchanted so that it is very " +
	"difficult for it to be cut in any way, thus making it " +
	"great protection against cutting and piercing " +
	"weapons.\n",20}));
}


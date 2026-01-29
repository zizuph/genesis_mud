
// Infidel chain mail
//    -Ilyian, Oct 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void create_armour()
{
  set_name(({"mail","shirt"}));
  set_short("shirt of light steel mail");
  add_adj(({"steel", "chain-link", "chain", "link", "light"}));
  set_long ("The links of this shirt are small, and expertly "
           +"woven together to form a strong protection. The "
           +"sleeves of the shirt extend down over the arms.\n");
  set_ac (25 + random (3));
  set_at (A_BODY | A_ARMS);
  set_am(({ -1, 3, -2}));
  add_prop (OBJ_I_WEIGHT, 2000);
  add_prop (OBJ_I_VOLUME, 1000);
}


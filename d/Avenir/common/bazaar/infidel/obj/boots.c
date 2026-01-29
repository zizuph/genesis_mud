
// Infidel boots
//    -Ilyian, Oct 1995

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour ()
{
  set_name(({"boots","pair"}));
  set_short("long pair of hardened leather boots");
  add_adj(({"long", "leather", "hardened"}));
  set_long ("These boots reach to the mid-thigh, and are "
           +"made from fairly sturdy leather. They are "
           +"not terribly comfortable, but they offer "
           +"good protection.\n");
  set_ac (12);
  set_am(({ 0, 2, -1}));
  set_at (A_LEGS | A_FEET);
}


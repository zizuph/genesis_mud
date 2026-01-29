#include <wa_types.h>

inherit "mweap";

void
create_weapon()
{
  ::create_weapon();
  set_name("bow");
  add_name("longbow");
  set_short("longbow");
  set_long("A longbow for testing the missile weapon launcher.\n");
  set_hit(20);
  set_pen(20);
  set_wt(W_POLEARM);
  set_dt(W_BLUDGEON);
  set_hands(W_ANYH);

  set_ammo(({"longbow arrow","arrow"}));
  set_rate(4);
}

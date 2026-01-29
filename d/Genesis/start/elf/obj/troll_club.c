#pragma save_binary

inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

#define LONG \
  "It is a massive, heavy club in hard wood, with long, wicked spikes.\n"

create_weapon()
{
  set_name( "club");
  set_pname("clubs");
  set_adj(({"heavy", "spiked"}));
  set_short("heavy spiked club");
  set_long(LONG);

  set_hit(25);
  set_pen(25);
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON | W_IMPALE);
  set_hands(W_BOTH);

  add_prop(OBJ_I_WEIGHT, 10000);
  add_prop(OBJ_I_VOLUME, 12000);
  add_prop(OBJ_I_VALUE,   1200);
}
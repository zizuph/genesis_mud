// -*-C++-*-
// file name: ~Avenir/common/outpost/obj/r_cloak.c
// creator(s): Boriska, Sep 1995
// last update:
// purpose:    armor  for outpost/rider.c
// note:       
// bug(s):
// to-do:     

#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/armour";

void
create_armour()
{
  set_name("cloak");
  set_short("dark cloak");
  add_adj ("dark");
  set_long("Dark long cloak, starting to wear down. It emanates a strong " +
	   "smell of horse sweat.\n");
  set_ac(8);
  set_at(A_ROBE);
  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 3000); 
}

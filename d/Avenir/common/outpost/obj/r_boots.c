// -*-C++-*-
// file name: ~Avenir/common/outpost/obj/r_boots.c
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
  set_name("boots");
  set_pname("boots");
  set_short("pair of riding boots");
  set_pshort("pairs of riding boots");
  add_adj ("riding");
  set_long("Black knee-high boots made of hard leather, custom made for " +
	   "horse riding. The leather is worn down above the heels, where " +
	   "spurs are usually worn.\n");
  set_ac(15);
  set_at(A_LEGS);
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 1000); 
}

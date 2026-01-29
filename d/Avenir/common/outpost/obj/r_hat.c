// -*-C++-*-
// file name: ~Avenir/common/outpost/obj/r_hat.c
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
  set_name("hat");
  set_short("soft hat");
  add_adj ("soft");
  set_long("Ordinary looking black hat with no decorations.\n");
  set_ac(8);
  set_at(A_HEAD);
  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 1000); 
}

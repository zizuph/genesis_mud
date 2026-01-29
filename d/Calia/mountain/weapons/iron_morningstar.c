/*
    An iron morningstar wielded by some lesser krougs.

    Coder(s) : Maniac

    History : 
          4/8/95                Created             Maniac
*/
inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_weapon()
{
  set_name("morningstar"); 
  set_adj("iron"); 
  set_short("iron morningstar"); 
  set_pshort("iron morningstars"); 
  set_long("A nasty looking weapon used by some lesser kroug warriors, " +
           "a big spiked iron club-head on a chain which is attached " +
           "to a short haft.\n");
  set_hit(20);
  set_pen(20);
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hands(W_ANYH);
  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 4000);
}


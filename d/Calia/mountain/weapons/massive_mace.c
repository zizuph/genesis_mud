/*
    A massive steel mace wielded by some high ranking krougs.

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
  set_name("mace");
  set_adj(({"massive", "steel"}));
  set_short("massive steel mace"); 
  set_pshort("massive steel maces"); 
  set_long("An impressive looking weapon used by high ranking kroug warriors. "+
           "The steel mace head is huge and has thick, penetrative " +
           "looking spikes.\n");
  set_hit(31);
  set_pen(31);
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hands(W_BOTH);
  add_prop(OBJ_I_WEIGHT, 13500);
  add_prop(OBJ_I_VOLUME, 7000);
}


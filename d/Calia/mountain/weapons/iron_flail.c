/*
    An iron flail wielded by regular kroug warriors. 

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
  set_name("flail"); 
  set_adj(({"big", "iron"})); 
  set_short("iron flail"); 
  set_pshort("iron flails"); 
  set_long("A nasty looking weapon used by regular kroug warriors. " + 
           "It's a big iron flail.\n"); 
  set_hit(27);
  set_pen(27);
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hands(W_BOTH);
  add_prop(OBJ_I_WEIGHT, 7000);
  add_prop(OBJ_I_VOLUME, 4500);
}


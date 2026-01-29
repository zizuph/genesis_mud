/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/wep/guardclub.c
* Comments: Updated by Luther Oct. 2001
*/
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include "defs.h"

void
create_weapon()
{
  set_name("club");
  set_name("clubs");
  set_short("iron club");
  set_short("iron clubs");
  set_long("This club looks nice to crush someone's head with. It has "+
           "old stains of blood on it and is rather filthy.\n");

  set_adj("iron");

  set_hit(27);
  set_pen(27);

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON | W_SLASH); 

  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 4000);
  add_prop(OBJ_I_VOLUME, 2500);
}

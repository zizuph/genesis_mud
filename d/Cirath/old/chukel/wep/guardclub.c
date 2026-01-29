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
  set_pname("clubs");
  
  set_short("brutal brain-beating club");
  set_short("brutal brain-beating clubs");
  
  set_long("This club looks nasty. You could propably "+
           "bonk a horse to unconciousness easily with it.\n");

  set_adj("brutal");
  add_adj("brain-beating");

  set_hit(35);
  set_pen(35);

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON | W_SLASH); 

  set_hands(W_RIGHT);

  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 2500);
}

/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/t_mail.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("ringmail");
  set_short("rust-stained ringmail");
  set_long("The ringmail lokks very used and is filthy. It has some "+
    "stains of rust on it too, but looks like it can protect you anyway.\n");
  set_adj("rust-stained");

  set_ac(16);
  set_am(({-1,1,1}));
  set_at(A_TORSO);

  add_prop(OBJ_I_VALUE, 25);
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,3000);
}

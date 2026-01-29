/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/n_mail.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("mail");
  set_short("nomad splint mail");
  set_long("This is a splint mail made of steel. The mail "+
           "is made by armourers in Cirath and used by the "+
           "hostile, nomad warriors that lives in the desert.\n");
  set_adj("splint");
  add_adj("nomad");

  set_ac(15);
  set_am(({-1,1,1}));
  set_at(A_TORSO);

  add_prop(OBJ_I_VALUE, 50);
  add_prop(OBJ_I_WEIGHT,12000);
  add_prop(OBJ_I_VOLUME,10000);
}

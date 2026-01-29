/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/n_leather.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("armour");
  set_short("nomad leather armour");
  set_long("This armour is made of leather. It is made "+
           "by the cirathian nomad warriors, a violent "+
           "tribe that is living in the desert.\n");
  set_adj("leather");
  add_adj("nomad");

  set_ac(10);
  set_am(({-1,1,1}));
  set_at(A_TORSO);

  add_prop(OBJ_I_VALUE, 60);
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,2000);
}

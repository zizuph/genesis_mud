/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/n_greaves.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>


void
create_armour()
{
  set_name("greaves");
  set_short("nomad steel greaves");
  set_long("These greaves are made of red-painted steel. "+
           "The colour red is holy to the nomad warriors "+
           "that lives in the desert of Cirath.\n");
  set_adj("steel");
  add_adj("nomad");

  set_ac(10);
  set_am(({ 0, 0, 0}));
  set_at(A_LEGS);
  
  add_prop(OBJ_I_VALUE, 45);
  add_prop(OBJ_I_WEIGHT, 3200);
  add_prop(OBJ_I_VOLUME, 1400);
}

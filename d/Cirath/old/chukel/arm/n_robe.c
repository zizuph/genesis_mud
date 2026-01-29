/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/n_robe.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("cloak");
  set_short("nomad silk cloak");
  set_adj("guardian");
  set_long("The cloak is made by the finest silk and the "+
           "clour is red, blood-red, the colour that the "+
           "cirathian nomad warriors are very fond of.\n");
  set_ac(5);
  set_am(({0,1,-1})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  
  add_prop(OBJ_I_VALUE, 300);
  add_prop(OBJ_I_WEIGHT,200);
  add_prop(OBJ_I_VOLUME,100);
}

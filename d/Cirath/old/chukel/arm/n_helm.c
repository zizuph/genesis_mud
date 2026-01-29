/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/n_helm.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("helm");
  set_short("nomad steel helm");
  set_long("This is the type of helme that the "+
           "nomads populating the cirathian desert "+
           "use. It is made of steel and has a "+
           "visor to protect the eyes from the sun and "+
           "the nose from sand. It looks quite crude.\n");
  set_adj("nomad");
  add_adj("steel");

  set_ac(14);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);
  
  add_prop(OBJ_I_VALUE, 80);
  add_prop(OBJ_I_WEIGHT,800);
  add_prop(OBJ_I_VOLUME,400);
}
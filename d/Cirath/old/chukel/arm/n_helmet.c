/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/n_helmet.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>


void
create_armour()

{
  set_name("helmet");
  set_short("nomad helmet");
  set_long("This is the type of helmet that the "+
           "nomads populating the cirathian desert "+
           "use. It is made of iron and has a leather "+
           "visor to protect the eyes from the sun and "+
           "the nose from sand.\n");
  set_adj("nomad");

  set_ac(10);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

  add_prop(OBJ_I_VALUE, 40);
  add_prop(OBJ_I_WEIGHT,1200);
  add_prop(OBJ_I_VOLUME,700);
}
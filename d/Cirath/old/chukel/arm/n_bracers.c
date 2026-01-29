/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/n_bracers.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("bracers");
  set_short("nomad steel bracers");
  set_long("These bracers are made of steel and painted "+
           "red, the favourite colour of the cirathian "+
           "nomads that lives in the desert.\n");
  set_adj("steel");
  add_adj("nomad");

  set_ac(10);
  set_am(({ 0, 0, 0}));
  set_at(A_ARMS);
}

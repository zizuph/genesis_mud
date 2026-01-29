/*
* Created by: Luther
* Date: 13 August 2001
*
* File: /d/Cirath/tyr/arm/d_shirt.c
* Comments: Dales shirt, a prisoner in Tyr's jail.
*/
 

inherit "/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
  set_name("shirt");
  set_pname("shirts");
  set_short("ragtag shirt");
  set_adj("ragtag");
  set_long("A ragtag shirt made of scrapt material.");

  set_ac(5);
  set_am(({0, 0, 0}));
  set_at(A_BODY);

  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME,  350);
}

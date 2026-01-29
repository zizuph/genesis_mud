/*
 * SM guard leggings
 * Tapakah, 04-05/2021
 */

#pragma strict_types

#include <wa_types.h>

#include "../defs.h"

inherit SM_ARMOUR;

void
create_armour ()
{
  set_name("leggings");
  set_pname("leggings");
  
  set_adj("plain");
  set_adj("steel");
  
  set_short("plain steel leggings");
  set_pshort("plain steel leggings");
  
  set_long("These leggings is made of plain steel links that seem to hold "+
           "together pretty well. Not too heavy and not too stiff, they "+
           "provides a decent defense for their bearer.\n");
  set_ac(20);
  set_at(A_LEGS);
  set_am(({0,0,0}));
}

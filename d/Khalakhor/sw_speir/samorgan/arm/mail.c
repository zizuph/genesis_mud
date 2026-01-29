/**********************************************************************
 * - mail.c                                                         - *
 * - Created by Damaris 7/2005                                      - *
 * - optimized by Tapakah, 5/2021                                   - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit SM_ARMOUR;

void
create_armour()
{
  set_name("chainmail");
  add_name("mail");
  set_adj(({"steel","chain"}));
  set_short("steel chainmail");
  set_long("This is a finely crafted piece of chainmail. It "+
           "is made with strong steel links.\n");
  set_ac(20);
  set_at(A_BODY);
  set_am(({-1,2,1}));
}

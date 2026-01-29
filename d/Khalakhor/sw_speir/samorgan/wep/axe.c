/*********************************************************************
 * - axe.c                                                         - *
 * - Created by Damaris 7/2005                                     - *
 * - Optimized a bit by Tapakah, 05/2021                            - *
 *********************************************************************/
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit SM_WEAPON;

void
create_weapon()
{
  set_name(({"axe"}));
  set_pname(({"axes"}));
  set_short("steel axe");
  set_pshort("steel axes");
  set_adj(({"steel"}));
  set_long("This is a " + short() + " that has a fine edged "+
           "blade.\n");
  set_default_weapon(24, 35, W_AXE, W_SLASH | W_IMPALE, W_BOTH);
  set_wf(TO);
  set_likely_dull(5);
  set_likely_break(5);
}


/**********************************************************************
 * - pole.c                                                         - *
 * - Created by Damaris 7/2005                                      - *
 * - Optimized a bit by Tapakah, 05/2021                            - *
 * - moved to partisan.c as well                                    - *
 **********************************************************************/
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit SM_WEAPON;

void
create_weapon()
{
  set_name(({"partisan"}));
  set_pname(({"partisans"}));
  add_name(({"polearm","lethal partisan"}));
  set_short("lethal partisan");
  set_pshort("lethal partisans");
  set_adj(({"lethal", "steel"}));
  set_long("This is a "+ short() +". It gives off a lethal appearance. "+
           "It has a narrow spearhead with two exceptional "+
           "blades projecting out at the base of the spearhead. It is "+
           "lightweight and maneuverable.\n");
  set_default_weapon(24, 35, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);
  set_wf(TO);
  set_likely_dull(5);
  set_likely_break(5);
  
}

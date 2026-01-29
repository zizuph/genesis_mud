/**********************************************************************
 * - helm.c                                                         - *
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
  set_name("helm");
  add_name("helmet");
  set_adj(({"steel","plate"}));
  set_short("steel helm");
  set_long("This is a finely crafted piece of steel plates "+
           "molded into a fine helm.\n");
  set_ac(20);
  set_at(A_HEAD);
  set_am(({1, -2, 1}));
}

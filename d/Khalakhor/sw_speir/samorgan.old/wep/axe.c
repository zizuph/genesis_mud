/*********************************************************************
 * - axe.c                                                         - *
 * - Created by Damaris 7/2005                                     - *
 *********************************************************************/
#pragma strict_types
inherit "/std/weapon.c";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/basic.h"

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


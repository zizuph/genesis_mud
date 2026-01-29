/*********************************************************************
 * - axe.c                                                         - *
 * - Created by Damaris 3/2003                                     - *
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
    set_short("silvery axe");
    set_pshort("silvery axes");
    set_adj(({"silvery"}));
    set_long("This is a " + short() + " that has a fine edged "+
      "blade. The weight of the weapon suggests it was perhaps "+
      "crafted by a dwaven smith.\n");
    set_default_weapon(24, 35, W_AXE, W_SLASH | W_IMPALE, W_BOTH);
    set_wf(TO);
    set_likely_dull(5);
    set_likely_break(5);
   
}


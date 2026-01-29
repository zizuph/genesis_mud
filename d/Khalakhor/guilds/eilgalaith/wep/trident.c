/*********************************************************************
 * - trident.c                                                     - *
 * - A trident for Dromadus                                        - *
 * - Created by Damaris 4/2002                                     - *
 *********************************************************************/
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/basic.h"
inherit "/std/weapon";
void
create_weapon()
{
    set_name(({"trident"}));
    set_short("silver and gold trident");
    set_adj(({"silver", "gold"}));
    set_long("This is a " + short() + ".\n");
    set_default_weapon(24, 35, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);
    set_wf(TO);
    set_likely_dull(5);
    set_likely_break(5);

}

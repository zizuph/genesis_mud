/**********************************************************************
 * - pole.c                                                         - *
 * - Created by Damaris 7/2005                                      - *
 **********************************************************************/
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
    set_default_weapon(24, 35, W_POLEARM, W_SLASH | W_IMPALE, W_ANYH);
    set_wf(TO);
    set_likely_dull(5);
    set_likely_break(5);

}

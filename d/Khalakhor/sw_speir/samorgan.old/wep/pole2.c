/**********************************************************************
 * - pole2.c                                                        - *
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
    add_name(({"polearm","treacherous partisan"}));
    set_short("treacherous partisan");
    set_pshort("treacherous partisans");
    set_adj(({"treacherous", "steel"}));
    set_long("This is a "+ short() +". It gives an almost luminous "+
      "treacherous appearance. It has a broad spearhead with two "+
      "exceptional blades projecting out at the base of the "+
      "spearhead. It is lightweight, fast and quite flexible.\n");
    set_default_weapon(24, 35, W_POLEARM, W_SLASH | W_IMPALE, W_ANYH);
    set_wf(TO);
    set_likely_dull(5);
    set_likely_break(5);

}

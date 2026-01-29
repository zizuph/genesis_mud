/**********************************************************************
 * - pole.c                                                         - *
 * - Created by Damaris 3/2003                                      - *
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
    add_name(({"polearm","deadly partisan"}));
    set_short("deadly partisan");
    set_pshort("deadly partisans");
    set_adj(({"deadly", "steel"}));
    set_long("This is a "+ short() +". It gives off a deadly appearance. "+
      "It has a narrow spearhead with two exceptional "+
      "blades projecting out at the base of the spearhead. It is "+
      "lightweight and maneuverable.\n");
    set_default_weapon(24, 35, W_POLEARM, W_SLASH | W_IMPALE, W_ANYH);
    set_wf(TO);
    set_likely_dull(5);
    set_likely_break(5);

}

/*********************************************************************
 * - rapier.c                                                      - *
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
    set_name(({"sword"}));
    add_name("rapier");
    set_pname(({"swords"}));
    set_short("classic rapier");
    set_adj(({"classic", "steady"}));
    set_long("The blade is slender with the traditional "+
      "diamond cross-section. The pommel counterbalances the blade "+
      "superbly, giving it a feeling of speed and lightness.\n");
    set_default_weapon(24, 35, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    set_wf(TO);
    set_likely_dull(5);
    set_likely_break(5);

}

/**********************************************************************
 * - helm.c                                                         - *
 * - Created by Damaris 3/2003                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/
#pragma strict_types

inherit "/std/armour";
#include "/d/Khalakhor/sys/basic.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
void
create_armour()
{
    set_name("helm");
    add_name("helmet");
    set_adj(({"steel","plate"}));
    set_short("steel helm");
    set_long("This is a finely crafted piece of steel plate mail "+
      "molded into a fine helm.\n");
    set_ac(20);
    set_at(A_HEAD);
    set_am(({3, 3, 2}));
    set_af(this_object());
}

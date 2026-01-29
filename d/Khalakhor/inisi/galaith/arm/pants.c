/**********************************************************************
 * - mpants.c                                                       - *
 * - Created by Damaris 3/2003                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/

#pragma strict_type
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/basic.h"

inherit "/std/armour";

void
create_armour()
{
    set_short("pair of emerald silk pants");
    set_pshort("pairs of emerald silk pants");
    set_name("pants");
    add_adj(({"emerald", "silk", "pair"}));
    set_long("This is a "+ short() +".\n");

    set_ac(0);
    add_prop(OBJ_I_VALUE, 100);
    set_at(A_LEGS);
    set_am( ({-1,3,-2 }) );
    set_af(this_object());
}




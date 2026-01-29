/**********************************************************************
 * - slippers.c                                                     - *
 * - Created by Damaris 3/2003                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/basic.h"

void
create_armour()
{
    set_short("pair of tan slippers");
    set_pshort("pairs of tan slippers");
    set_name("slippers");
    add_adj(({"pair", "tan"}));
    set_long("This is a "+ short() +".\n");

    set_ac(0);
    add_prop(OBJ_I_VALUE, 100);
    set_at(A_FEET);
    set_am( ({-1,3,-2 }) );
    set_af(this_object());
}




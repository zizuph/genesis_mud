/**********************************************************************
 * - boots.c                                                        - *
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
 
    set_name("boots");
    set_adj(({"black", "leather"}));
    set_short("pair of black leather boots");
    set_pshort("pairs of black leather boots");
    set_long("These "+ short() + " are made from blackened leather.\n");
    add_item(({"blackened ties", "leather ties", "ties"}),
      "These are blackened leather ties used for fastening "+
      "the "+ short() +" in place.\n");
    set_ac(20);
    set_at(A_FEET);
    set_am(({-1,2,0}));
    set_af(this_object());
}

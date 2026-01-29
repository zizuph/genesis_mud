/**********************************************************************
 * - gloves.c                                                       - *
 * - Created by Damaris 7/2005                                      - *
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
 
    set_name("gloves");
    set_adj(({"steel", "chain", "mail"}));
    set_short("pair of mail gloves");
    set_pshort("pairs of mail gloves");
    set_long("These "+ short() + " are made from chain mail steel. They "+
      "have clean steel appearance and fit comfortablly on "+
      "the hands.\n");
    set_ac(20);
    set_at(A_HANDS);
    set_am(({-1,2,0}));
    set_af(this_object());
}

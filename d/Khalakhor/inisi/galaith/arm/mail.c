/**********************************************************************
 * - mail.c                                                         - *
 * - Created by Damaris 2/2003                                      - *
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
    set_name("chainmail");
    add_name("mail");
    set_adj(({"steel","chain"}));
    set_short("steel chainmail");
    set_long("This is a finely crafted piece of chainmail. It "+
      "is made from the finest steel links.\n");
   set_ac(36);
    set_at(A_BODY);
    set_am(({3, 3, 2}));
    set_af(this_object());
}

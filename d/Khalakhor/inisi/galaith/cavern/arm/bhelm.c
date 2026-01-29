/**********************************************************************
 * - bhelm.c                                                        - *
 * - Found on NPC's Galaith Isle, cavern                            - *
 * - Created by Damaris 6/15/2002                                   - *
 **********************************************************************/
#pragma strict_types

inherit "/std/armour";
#include "/d/Raumdor/sys/basic.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
void
create_armour()
{
    set_name("helm");
    add_name("helmet");
    set_adj(({"dingy", "black", "steel","plate"}));
    set_short("dingy black helm");
    set_long("This "+ short() + " is a finely crafted piece of plate mail. "+
      "It is made from the finest steel but is a bit dingy from use.\n");
    set_ac(20);
    set_at(A_HEAD);
    set_am(({3, 3, 2}));
    set_af(this_object());
}

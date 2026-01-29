/**********************************************************************
 * - bbracers.c                                                     - *
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
 
    set_name("bracers");
    set_adj(({"black"}));
    set_short("pair of dingy black bracers");
    set_pshort("pairs of dingy black bracers");
    set_long("These "+ short() + " are made from black steel. They "+
      "are a bit dingy from use but fit comfortablly on the forearms.\n");
    add_item(({"blackened ties", "leather ties", "ties"}),
      "These are blackened leather ties used for fastening "+
      "the "+ short() +" in place on the forearms.\n");
    set_ac(20);
    set_at(A_ARMS);
    set_am(({-1,2,0}));
    set_af(this_object());
}

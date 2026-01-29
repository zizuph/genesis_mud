/**********************************************************************
 * - bshield.c                                                      - *
 * - Found on NPC's Galaith Isle, cavern                            - *
 * - Created by Damaris 6/15/2002                                   - *
 **********************************************************************/
#pragma strict_types

inherit "/std/armour";
#include "/d/Raumdor/sys/basic.h"
#include <stdproperstraps.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
void
create_armour()
{
    set_name("shield");
    set_adj(({"dingy", "black", "steel"}));
    set_short("dingy black steel shield");
    set_pshort("dingy black steel shields");
    set_long("This is a "+ short() +" that has been forged with the "+
      "finest of steel but is a bit dingy from use.\n");
    add_item(({"blackened straps", "leather straps", "straps"}),
      "These are blackened leather straps used for fastening "+
      "the "+ short() +" in place on the forearm.\n");
    set_ac(30);
    set_at(A_SHIELD);
    set_am(({3, 3, 2}));
    set_af(this_object());
}

public int
query_shield_slots()
{
   return ::query_shield_slots() + ({ A_BODY });
}

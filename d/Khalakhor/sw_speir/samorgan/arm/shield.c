/**********************************************************************
 * - shield.c                                                       - *
 * - Created by Damaris 7/2005                                      - *
 * - optimized by Tapakah, 5/2021                                   - *
 **********************************************************************/
#pragma strict_types

#include <wa_types.h>

#include "../defs.h"

inherit SM_ARMOUR;

void
create_armour()
{
  set_name("shield");
  set_adj(({"steel"}));
  set_short("steel shield");
  set_pshort("steel shields");
  set_long("This "+ short() +" has been well crafted using a "+
           "special technique only known to smiths in the southwest "+
           "speir of Khalakhor. The molding and fittings are secured "+
           "with expertise that allows for ease of use and adjustments "+
           "for the wearer.\n");
  add_item(({"blackened ties", "leather ties", "ties"}),
           "These are blackened leather ties used for fastening "+
           "the "+ short() +" in place on the forearm.\n");
  set_ac(20);
  set_at(A_SHIELD);
  set_am(({0,0,0}));
}

public int
query_shield_slots()
{
  return ::query_shield_slots() + ({ A_BODY });
}
